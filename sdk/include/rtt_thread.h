#ifndef RTT_THREAD_H_INCLUDED
#define RTT_THREAD_H_INCLUDED
/**
 * The thread to detect RTT.
 * @author ZHG <CyberZHG@gmail.com>
 */

#include "rtt_config.h"
#include "rtt_status.h"

/**
 * Create a RTT detection thread.
 */
int rtt_createThread(PRTT_Config config, PRTT_Status status);
/**
 * Release a RTT detection thread.
 */
void rtt_releaseThread(PRTT_Config config, PRTT_Status status);

/**
 * The following functions are used for single-thread programs.
 */

/**
 * Get the current milliseconds from a certain time point.
 */
long long rtt_getCurrentMilliseconds();
/**
 * Read an integer from string.
 * @return The integer.
 */
int rtt_readIntFromStr(const char *buf);
/**
 * Write an integer to string.
 */
void rtt_writeIntToStr(char *buf, int num);
/**
 * Read long long value from string.
 */
long long rtt_readLongLongFromStr(const char *buf);
/**
 * Write long long value to string.
 */
void rtt_writeLongLongToStr(char *buf, long long num);

/**
 * Detect RTT using Ping protocol.
 * @return The RTT if succeed, otherwise -1.
 */
int rtt_pingLocation(PRTT_Config config, PRTT_Status status);
/**
 * Detect RTT using TCP protocol.
 * @return The RTT if succeed, otherwise -1.
 */
int rtt_tcpDetect(PRTT_Config config, PRTT_Status status);
/**
 * Detect RTT using UDP protocol.
 * @return The RTT if succeed, otherwise -1.
 */
int rtt_udpDetect(PRTT_Config config, PRTT_Status status);

/**
 * Connect to server.
 */
void rtt_connectServer(PRTT_Config config, PRTT_Status status);
/**
 * Send RTT message to server.
 */
void rtt_sendToServer(PRTT_Config config, PRTT_Status status);
/**
 * Send close message to server.
 */
void rtt_sendCloseToServer(PRTT_Config config, PRTT_Status status);
/**
 * Detect RTT.
 */
void rtt_detectRTT(PRTT_Config config, PRTT_Status status);

#endif // RTT_THREAD_H_INCLUDED
