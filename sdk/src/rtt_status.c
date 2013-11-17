#include <stdlib.h>
#include "rtt_status.h"

PRTT_Status rtt_createStatus()
{
    PRTT_Status status = (PRTT_Status)malloc(sizeof(RTT_Status));
    status->status = RTT_STATUS_PENDING;
    status->thread = -1;
    status->magic = 0;
    status->connServerTime = 0;
    status->lastConnServerTime = 0;
    status->detectNum = 0;
    status->lastDetectTime = 0;
    status->rtt = 0;
    status->rttLast = 0;
    status->terminate = 0;
    return status;
}

void rtt_releaseStatus(PRTT_Status *status)
{
    free(*status);
}
