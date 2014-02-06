#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <resolv.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include "rtt_thread.h"

typedef struct RTT_Package
{
    PRTT_Config config;
    PRTT_Status status;
} RTT_Package;
typedef RTT_Package* PRTT_Package;

long long rtt_getCurrentMilliseconds()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (long long)now.tv_sec * 1000 + now.tv_usec / 1000;
}

int rtt_readIntFromStr(const char *buf)
{
    int i, num = 0;
    for (i = 0; i < 4; ++i)
    {
        num <<= 8;
        num |= (unsigned char)buf[i];
    }
    return num;
}

void rtt_writeIntToStr(char *buf, int num)
{
    int i;
    for (i = 3; i >= 0; --i)
    {
        buf[i] = num & ((1 << 8) - 1);
        num >>= 8;
    }
}

long long rtt_readLongLongFromStr(const char *buf)
{
    int i;
    long long num = 0;
    for (i = 0; i < 8; ++i)
    {
        num <<= 8;
        num |= (unsigned char)buf[i];
    }
    return num;
}

void rtt_writeLongLongToStr(char *buf, long long num)
{
    int i;
    for (i = 7; i >= 0; --i)
    {
        buf[i] = num & ((1 << 8) - 1);
        num >>= 8;
    }
}

int rtt_getMagicNum(PRTT_Config config, PRTT_Status status)
{
    struct sockaddr_in server_addr;
    int client_sockfd, len, tLen;
    char buf[BUFSIZ];

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(config->server->ip);
    server_addr.sin_port = htons(config->server->port);

    client_sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == client_sockfd)
    {
        return -1;
    }
    if (-1 == connect(client_sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)))
    {
        return -1;
    }
    len = 0;
    tLen = strlen(config->clientName);
    rtt_writeIntToStr(buf + len, tLen);
    len += 4;
    strcpy(buf + len, config->clientName);
    len += tLen;

    tLen = strlen(config->pingAddress);
    rtt_writeIntToStr(buf + len, tLen);
    len += 4;
    strcpy(buf + len, config->pingAddress);
    len += tLen;

    len = send(client_sockfd, buf, len, 0);
    if (len < 0)
    {
        return -1;
    }

    len = recv(client_sockfd, buf, BUFSIZ, 0);
    if (4 != len)
    {
        return -1;
    }
    status->magic = rtt_readIntFromStr(buf);
    shutdown(client_sockfd, SHUT_RDWR);
    #ifdef RTT_DEBUG
    if (RTT_DEBUG_MODE_ON == config->debugMode)
    {
        printf("Succeed.\n");
        printf("\tMagic Number: %d\n", status->magic);
    }
    #endif // RTT_DEBUG
    return 0;
}

void rtt_connectServer(PRTT_Config config, PRTT_Status status)
{
    if (status->connServerTime > config->connServerTime)
    {
        status->status = RTT_STATUS_CONNECT_SERVER_FAILED;
    }
    else
    {
        if (rtt_getCurrentMilliseconds() - status->lastConnServerTime >= config->connServerInterval)
        {
            #ifdef RTT_DEBUG
            if (RTT_DEBUG_MODE_ON == config->debugMode)
            {
                printf("Connect to server... %d\n", status->connServerTime + 1);
            }
            #endif // RTT_DEBUG
            if (0 == rtt_getMagicNum(config, status))
            {
                status->status = RTT_STATUS_DETECTING;
                status->lastConnServerTime = rtt_getCurrentMilliseconds();
            }
            else
            {
                ++status->connServerTime;
            }
        }
    }
}

unsigned short checksum(void *b, int len)
{
    unsigned short *buf = b;
    unsigned int sum=0;
    unsigned short result;
    for (sum = 0; len > 1; len -= 2)
    {
        sum += *buf++;
    }
    if (len == 1)
    {
        sum += *(unsigned char*)buf;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int rtt_pingLocation(PRTT_Config config, PRTT_Status status)
{
    struct packet
    {
        struct icmphdr hdr;
        char msg[64 - sizeof(struct icmphdr)];
    };
    int pid = -1, cnt = 1;
    socklen_t len;
    struct protoent *proto=NULL;
    const int val = 255;
    int i, sd, loop, rtt;
    struct packet pckt;
    struct sockaddr_in r_addr;
    struct hostent *hname;
    struct sockaddr_in addr_ping,*addr;
    long long startTime, endTime;

    startTime = rtt_getCurrentMilliseconds();
    pid = getpid();
    proto = getprotobyname("ICMP");
    hname = gethostbyname(config->pingAddress);
    bzero(&addr_ping, sizeof(addr_ping));
    addr_ping.sin_family = hname->h_addrtype;
    addr_ping.sin_port = 0;
    addr_ping.sin_addr.s_addr = *(long*)hname->h_addr;

    addr = &addr_ping;
    sd = socket(PF_INET, SOCK_RAW, proto->p_proto);
    if (sd < 0)
    {
        return -1;
    }
    if (setsockopt(sd, SOL_IP, IP_TTL, &val, sizeof(val)) != 0)
    {
        return -1;
    }
    if (fcntl(sd, F_SETFL, O_NONBLOCK) != 0)
    {
        return -1;
    }
    for (loop = 0; loop < 1000000; ++loop)
    {
        len = sizeof(r_addr);
        if (recvfrom(sd, &pckt, sizeof(pckt), 0, (struct sockaddr*)&r_addr, &len) > 0)
        {
            endTime = rtt_getCurrentMilliseconds();
            rtt = endTime - startTime;
            return rtt;
        }
        bzero(&pckt, sizeof(pckt));
        pckt.hdr.type = ICMP_ECHO;
        pckt.hdr.un.echo.id = pid;
        for (i = 0; i < sizeof(pckt.msg)-1; ++i)
        {
            pckt.msg[i] = i + '0';
        }
        pckt.msg[i] = 0;
        pckt.hdr.un.echo.sequence = cnt++;
        pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));
        if (sendto(sd, &pckt, sizeof(pckt), 0, (struct sockaddr*)addr, sizeof(*addr)) <= 0)
        {
            return -1;
        }
        usleep(1000);
    }
    return -1;
}

int rtt_tcpDetect(PRTT_Config config, PRTT_Status status)
{
    struct sockaddr_in server_addr;
    int client_sockfd, len;
    char buf[BUFSIZ];
    long long startTime, endTime;

    startTime = rtt_getCurrentMilliseconds();
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(config->detect->ip);
    server_addr.sin_port = htons(config->detect->port);

    client_sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == client_sockfd)
    {
        return -1;
    }
    if (-1 == connect(client_sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)))
    {
        return -1;
    }
    for (len = 0; len < 1024; ++len)
    {
        buf[len] = rand() % 128;
    }

    len = send(client_sockfd, buf, len, 0);
    if (len < 0)
    {
        return -1;
    }

    len = recv(client_sockfd, buf, BUFSIZ, 0);
    if (1024 != len)
    {
        return -1;
    }
    shutdown(client_sockfd, SHUT_RDWR);
    endTime = rtt_getCurrentMilliseconds();
    return endTime - startTime;
}

int rtt_udpDetect(PRTT_Config config, PRTT_Status status)
{
    struct sockaddr_in server_addr;
    int client_sockfd, len;
    char buf[BUFSIZ];
    long long startTime, endTime;
    unsigned int size;

    size = sizeof(struct sockaddr_in);

    startTime = rtt_getCurrentMilliseconds();
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(config->server->ip);
    server_addr.sin_port = htons(config->server->port);

    client_sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (-1 == client_sockfd)
    {
        return -1;
    }

    for (len = 0; len < 1024; ++len)
    {
        buf[len] = rand() % 128;
    }
    len = sendto(client_sockfd, buf, len, 0, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in));
    if (len < 0)
    {
        return -1;
    }
    len = recvfrom(client_sockfd, buf, BUFSIZ, 0, (struct sockaddr*)&server_addr, &size);
    if (len < 0)
    {
        return -1;
    }

    shutdown(client_sockfd, SHUT_RDWR);
    endTime = rtt_getCurrentMilliseconds();
    return endTime - startTime;
}

void rtt_sendToServer(PRTT_Config config, PRTT_Status status)
{
    struct sockaddr_in server_addr;
    int client_sockfd, len;
    char buf[BUFSIZ];

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(config->server->ip);
    server_addr.sin_port = htons(config->server->port);

    client_sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (-1 == client_sockfd)
    {
        return;
    }

    rtt_writeIntToStr(buf, status->magic);
    rtt_writeLongLongToStr(buf + 4, rtt_getCurrentMilliseconds());
    rtt_writeIntToStr(buf + 12, status->rtt);
    len = sendto(client_sockfd, buf, 16, 0, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in));
    if (len < 0)
    {
        return;
    }

    shutdown(client_sockfd, SHUT_RDWR);
}

void rtt_sendCloseToServer(PRTT_Config config, PRTT_Status status)
{
    struct sockaddr_in server_addr;
    int client_sockfd, len;
    char buf[BUFSIZ];

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(config->server->ip);
    server_addr.sin_port = htons(config->server->port);

    client_sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (-1 == client_sockfd)
    {
        return;
    }

    rtt_writeIntToStr(buf, status->magic);
    rtt_writeLongLongToStr(buf + 4, rtt_getCurrentMilliseconds());
    rtt_writeIntToStr(buf + 12, -1);
    len = sendto(client_sockfd, buf, 16, 0, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in));
    if (len < 0)
    {
        return;
    }
    shutdown(client_sockfd, SHUT_RDWR);
}

void rtt_detectRTT(PRTT_Config config, PRTT_Status status)
{
    int rtt;
    if (rtt_getCurrentMilliseconds() - status->lastDetectTime >= config->interval)
    {
        switch (config->detectType)
        {
        case RTT_D_TYPE_PING:
            rtt = rtt_pingLocation(config, status);
            break;
        case RTT_D_TYPE_TCP:
            rtt = rtt_tcpDetect(config, status);
            break;
        case RTT_D_TYPE_UDP:
            rtt = rtt_udpDetect(config, status);
            break;
        }
        rtt = rtt_pingLocation(config, status);
        if (-1 != rtt)
        {
            ++status->detectNum;
            #ifdef RTT_DEBUG
            if (RTT_DEBUG_MODE_ON == config->debugMode)
            {
                printf("Send RTT message... %d\n", status->detectNum);
            }
            #endif // RTT_DEBUG
            status->rttLast = rtt;
            if (0 == status->rtt)
            {
                status->rtt = rtt;
            }
            else
            {
                status->rtt = config->alpha * status->rtt + (1.0f - config->alpha) * rtt;
            }
            rtt_sendToServer(config, status);
            if (config->time != RTT_TIME_INFINITY && status->detectNum >= config->time)
            {
                status->status = RTT_STATUS_FINISHED;
                rtt_sendCloseToServer(config, status);
            }
        }
        status->lastDetectTime = rtt_getCurrentMilliseconds();
    }
}

void* rtt_detectionLoop(void *arg)
{
    PRTT_Package package = (PRTT_Package)arg;
    PRTT_Config config = package->config;
    PRTT_Status status = package->status;
    while (!status->terminate)
    {
        switch (status->status)
        {
        case RTT_STATUS_PENDING:
            status->status = RTT_STATUS_CONNECTING_SERVER;
            break;
        case RTT_STATUS_CONNECTING_SERVER:
            rtt_connectServer(config, status);
            break;
        case RTT_STATUS_CONNECT_SERVER_FAILED:
            return NULL;
        case RTT_STATUS_DETECTING:
            rtt_detectRTT(config, status);
            break;
        case RTT_STATUS_FINISHED:
            return NULL;
        }
    }
    return NULL;
}

int rtt_createThread(PRTT_Config config, PRTT_Status status)
{
    PRTT_Package package = (PRTT_Package)malloc(sizeof(RTT_Package));
    package->config = config;
    package->status = status;
    return pthread_create(&status->thread, NULL, &rtt_detectionLoop, package) == 0;
}

void rtt_releaseThread(PRTT_Config config, PRTT_Status status)
{
    if (status->thread != -1)
    {
        status->terminate = 1;
        pthread_join(status->thread, NULL);
        rtt_releaseConfig(&config);
        rtt_releaseStatus(&status);
    }
}
