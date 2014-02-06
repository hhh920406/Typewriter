#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rtt_config.h"

#define RTT_INTERVAL_DEFAULT 10000
#define RTT_ALPHA_DEFAULT 0.9
#define RTT_CONN_SERVER_TIME_DEFAULT 10
#define RTT_CONN_SERVER_INTERVAL_DEFAULT 10000

PRTT_Location rtt_createLocation(const char *ip, const int port)
{
    PRTT_Location location = (PRTT_Location)malloc(sizeof(RTT_Location));
    strcpy(location->ip, ip);
    location->port = port;
    return location;
}

void rtt_releaseLocation(PRTT_Location *location)
{
    free(*location);
}

PRTT_Config rtt_createPingConfig(const char *clientName, const char *pingAddress,
                                 const char *serverIp, const int serverPort)
{
    PRTT_Config config = (PRTT_Config)malloc(sizeof(RTT_Config));
    strcpy(config->clientName, clientName);
    config->time = RTT_TIME_INFINITY;
    config->interval = RTT_INTERVAL_DEFAULT;
    config->alpha = RTT_ALPHA_DEFAULT;
    config->connServerTime = RTT_CONN_SERVER_TIME_DEFAULT;
    config->connServerInterval = RTT_CONN_SERVER_INTERVAL_DEFAULT;
    config->detectType = RTT_D_TYPE_PING;
    strcpy(config->pingAddress, pingAddress);
    config->server = rtt_createLocation(serverIp, serverPort);
    #ifdef RTT_DEBUG
    config->debugMode = RTT_DEBUG_MODE_OFF;
    #endif // RTT_DEBUG
    return config;
}

PRTT_Config rtt_createTcpConfig(const char *clientName,
                                const char *detectIp, const int detectPort,
                                const char *serverIp, const int serverPort)
{
    PRTT_Config config = (PRTT_Config)malloc(sizeof(RTT_Config));
    strcpy(config->clientName, clientName);
    config->time = RTT_TIME_INFINITY;
    config->interval = RTT_INTERVAL_DEFAULT;
    config->alpha = RTT_ALPHA_DEFAULT;
    config->connServerTime = RTT_CONN_SERVER_TIME_DEFAULT;
    config->connServerInterval = RTT_CONN_SERVER_INTERVAL_DEFAULT;
    config->detectType = RTT_D_TYPE_TCP;
    config->detect = rtt_createLocation(detectIp, detectPort);
    config->server = rtt_createLocation(serverIp, serverPort);
    #ifdef RTT_DEBUG
    config->debugMode = RTT_DEBUG_MODE_OFF;
    #endif // RTT_DEBUG
    return config;
}

PRTT_Config rtt_createUdpConfig(const char *clientName,
                                const char *detectIp, const int detectPort,
                                const char *serverIp, const int serverPort)
{
    PRTT_Config config = (PRTT_Config)malloc(sizeof(RTT_Config));
    strcpy(config->clientName, clientName);
    config->time = RTT_TIME_INFINITY;
    config->interval = RTT_INTERVAL_DEFAULT;
    config->alpha = RTT_ALPHA_DEFAULT;
    config->connServerTime = RTT_CONN_SERVER_TIME_DEFAULT;
    config->connServerInterval = RTT_CONN_SERVER_INTERVAL_DEFAULT;
    config->detectType = RTT_D_TYPE_UDP;
    config->detect = rtt_createLocation(detectIp, detectPort);
    config->server = rtt_createLocation(serverIp, serverPort);
    #ifdef RTT_DEBUG
    config->debugMode = RTT_DEBUG_MODE_OFF;
    #endif // RTT_DEBUG
    return config;
}


void rtt_setConfigTime(PRTT_Config config, const int time)
{
    config->time = time;
}

void rtt_setConfigInterval(PRTT_Config config, const int interval)
{
    config->interval = interval;
}

void rtt_setConfigAlpha(PRTT_Config config, const float alpha)
{
    config->alpha = alpha;
}

void rtt_setConfigConnServerTime(PRTT_Config config, const int connServerTime)
{
    config->connServerTime = connServerTime;
}

void rtt_setConfigConnServerInterval(PRTT_Config config, const int connServerInterval)
{
    config->connServerInterval = connServerInterval;
}

#ifdef RTT_DEBUG
void rtt_setConfigDebugMode(PRTT_Config config, const int debug)
{
    config->debugMode = debug;
    if (RTT_DEBUG_MODE_ON == config->debugMode)
    {
        printf("Debug On\n");
        printf("RTT Config Information: \n");
        printf("\tClient Name: %s\n", config->clientName);
        printf("\tDetect Address: %s\n", config->pingAddress);
        printf("\tServer Address: %s:%d\n", config->server->ip, config->server->port);
        printf("\tConnect Server Retry: %d Interval: %d\n", config->connServerTime, config->connServerInterval);
        if (RTT_TIME_INFINITY == config->time)
        {
            printf("\tDetect Time: INF Interval: %d\n", config->interval);
        }
        else
        {
            printf("\tDetect Time: %d Interval: %d\n", config->time, config->interval);
        }
        printf("\tRTT Alpha: %lf\n", config->alpha);
    }
}
#endif // RTT_DEBUG

void rtt_releaseConfig(PRTT_Config *config)
{
    rtt_releaseLocation(&(*config)->server);
    free(*config);
}
