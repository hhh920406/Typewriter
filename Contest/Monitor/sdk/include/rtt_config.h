#ifndef RTT_CONFIG_H_INCLUDED
#define RTT_CONFIG_H_INCLUDED
/**
 * The configuration structure for RTT detection.
 * @author ZHG <CyberZHG@gmail.com>
 */

typedef struct RTT_Location
{
    char ip[16];
    int port;
} RTT_Location;
typedef RTT_Location* PRTT_Location;

#define RTT_TIME_INFINITY -1

#ifdef RTT_DEBUG
#define RTT_DEBUG_MODE_OFF 0
#define RTT_DEBUG_MODE_ON 1
#endif // RTT_DEBUG

/**
 * The method of detection.
 * The value was set automatically by creation function.
 * Users could ignore the defination.
 */
enum RTT_Detect_Type
{
    RTT_D_TYPE_PING,
    RTT_D_TYPE_TCP,
    RTT_D_TYPE_UDP
};

typedef struct RTT_Config
{
    char clientName[128];
    int time;
    int interval;
    float alpha;
    int connServerTime;
    int connServerInterval;
    enum RTT_Detect_Type detectType;
    char pingAddress[1024];
    PRTT_Location detect;
    PRTT_Location server;
    #ifdef RTT_DEBUG
    int debugMode;
    #endif // RTT_DEBUG
} RTT_Config;
typedef RTT_Config* PRTT_Config;

/**
 * Detect with ping protocol.
 * @param clientName The name of the client, the name could be arbitrary.
 * @param pingAddress The address could be a domin name or an ip address.
 * @param serverIp The IP address of the server.
 * @param serverPort The port the server listend to.
 */
PRTT_Config rtt_createPingConfig(const char *clientName,
                                 const char *pingAddress,
                                 const char *serverIp, const int serverPort);
/**
 * Detect with TCP.
 * @param clientName The name of the client, the name could be arbitrary.
 * @param detectIp The IP address which to detect.
 * @param detectPort The port of the detection address.
 * @param serverIp The IP address of the server.
 * @param serverPort The port the server listend to.
 */
PRTT_Config rtt_createTcpConfig(const char *clientName,
                                const char *detectIp, const int detectPort,
                                const char *serverIp, const int serverPort);
/**
 * Detect with UDP.
 * @param clientName The name of the client, the name could be arbitrary.
 * @param detectIp The IP address which to detect.
 * @param detectPort The port of the detection address.
 * @param serverIp The IP address of the server.
 * @param serverPort The port the server listend to.
 */
PRTT_Config rtt_createUdpConfig(const char *clientName,
                                const char *detectIp, const int detectPort,
                                const char *serverIp, const int serverPort);
/**
 * Set the times of detection.
 * It will detect infinity times if the value was set RTT_TIME_INFINITY.
 */
void rtt_setConfigTime(PRTT_Config config, const int time);
/**
 * Set the interval between each detection.
 */
void rtt_setConfigInterval(PRTT_Config config, const int interval);
/**
 * Set the alpha of the RTT formula.
 * NewRTT = OldRTT * alpha + LastestRTT * (1.0 - alpha)
 */
void rtt_setConfigAlpha(PRTT_Config config, const float alpha);
/**
 * Set the times to connect to server when failed.
 */
void rtt_setConfigConnServerTime(PRTT_Config config, const int connServerTime);
/**
 * Set the interval between connect to server.
 */
void rtt_setConfigConnServerInterval(PRTT_Config config, const int connServerInterval);
#ifdef RTT_DEBUG
/**
 * Used for debug.
 */
void rtt_setConfigDebugMode(PRTT_Config config, const int debug);
#endif // RTT_DEBUG
/**
 * Release the memory.
 */
void rtt_releaseConfig(PRTT_Config *config);

#endif // RTT_CONFIG_H_INCLUDED
