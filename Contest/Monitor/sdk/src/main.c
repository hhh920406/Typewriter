#include <stdio.h>
#include "rtt_thread.h"

/**
 * A simple demo.
 */
int main()
{
    PRTT_Config config = rtt_createPingConfig("Debug", "www.baidu.com",
                                              "127.0.0.1", 19627);
    rtt_setConfigDebugMode(config, RTT_DEBUG_MODE_ON);
    rtt_setConfigInterval(config, 1000);
    rtt_setConfigAlpha(config, 0.95);
    PRTT_Status status = rtt_createStatus();
    rtt_createThread(config, status);
    while (1)
    {
        if (RTT_STATUS_CONNECT_SERVER_FAILED == status->status)
        {
            printf("Final: Failed to connect to server. \n");
            rtt_releaseThread(config, status);
            break;
        }
        else if (RTT_STATUS_FINISHED == status->status)
        {
            printf("Final: Succeed. \n");
            rtt_releaseThread(config, status);
            break;
        }
    }
    return 0;
}
