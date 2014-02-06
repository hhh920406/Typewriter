#ifndef TCPSERVER_H
#define TCPSERVER_H
/**
 * The TCP server.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QtNetwork>

class ClientInfo;
class ClientManager;

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(ClientManager *manager);
    virtual ~TcpServer();
    bool listen(qint32 port);

    static qint32 readInt32(QByteArray &bytes, qint32 &index);
    static void writeInt32(QByteArray &bytes, qint32 value);

private:
    ClientManager *_manager;
    QTcpServer *_server;
    QTcpSocket *_socket;

signals:
    void newClient(qint32 magic);

private slots:
    void newConnection();
    void readMessage();
};

#endif // TCPSERVER_H
