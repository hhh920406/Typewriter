#ifndef UDPSERVER_H
#define UDPSERVER_H
/**
 * The UDP server.
 * @author ZHG <CyberZHG@gmail.com
 */
#include <QtNetwork>

class ClientInfo;
class ClientManager;

class UdpServer : public QObject
{
    Q_OBJECT
public:
    UdpServer(ClientManager *manager);
    virtual ~UdpServer();
    bool listen(qint32 port);

    static qint64 readInt64(QByteArray &bytes, qint32 &index);
    static void writeInt64(QByteArray &bytes, qint64 value);

private:
    ClientManager *_manager;
    QUdpSocket *_socket;

signals:
    void updateClient(qint32 magic);
    void closeClient(qint32 magic);

private slots:
    void readMessage();
};

#endif // UDPSERVER_H
