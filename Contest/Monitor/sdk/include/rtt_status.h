#ifndef RTT_STATUS_H_INCLUDED
#define RTT_STATUS_H_INCLUDED
/**
 * The defination of status.
 * @author ZHG <CyberZHG@gmail.com>
 */

enum RTT_Status_Enum
{
    RTT_STATUS_PENDING,
    RTT_STATUS_CONNECTING_SERVER,
    RTT_STATUS_CONNECT_SERVER_FAILED,
    RTT_STATUS_DETECTING,
    RTT_STATUS_FINISHED
};

typedef struct RTT_Status
{
    int status;
    unsigned long int thread;
    int magic;
    int connServerTime;
    long long lastConnServerTime;
    int detectNum;
    long long lastDetectTime;
    int rtt;
    int rttLast;
    int terminate;
} RTT_Status;

typedef RTT_Status* PRTT_Status;

PRTT_Status rtt_createStatus();
void rtt_releaseStatus(PRTT_Status *status);

#endif // RTT_STATUS_H_INCLUDED
