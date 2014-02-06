#include <QByteArray>
#include "ClientInfo.h"
#include "ClientManager.h"
#include "TcpServer.h"

TcpServer::TcpServer(ClientManager *manager)
{
    this->_manager = manager;
    this->_server = new QTcpServer(this);
    this->_server->setMaxPendingConnections(128);
}

TcpServer::~TcpServer()
{
    delete this->_server;
}

bool TcpServer::listen(qint32 port)
{
    if (this->_server->listen(QHostAddress::Any, port))
    {
        this->connect(this->_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
        return true;
    }
    return false;
}

qint32 TcpServer::readInt32(QByteArray &bytes, qint32 &index)
{
    qint32 value = 0;
    for (qint32 i = 0; i < 4; ++i)
    {
        value <<= 8;
        value |= (unsigned char)bytes.at(index);
        ++index;
    }
    return value;
}

void TcpServer::writeInt32(QByteArray &bytes, qint32 value)
{
    for (qint32 i = 8; i <= 32; i += 8)
    {
        bytes.append((value >> (32 - i)) & ((1 << 8) - 1));
    }
}

void TcpServer::newConnection()
{
    this->_socket = this->_server->nextPendingConnection();
    this->connect(this->_socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

void TcpServer::readMessage()
{
    ClientInfo client;
    QByteArray bytes = this->_socket->readAll();
    if (bytes.length() == 0)
    {
        return;
    }
    qint32 index = 0;

    qint32 len = readInt32(bytes, index);
    QString clientName;
    for (qint32 i = 0; i < len; ++i)
    {
        clientName += bytes.at(index + i);
    }
    index += len;
    client.setName(clientName);

    len = readInt32(bytes, index);
    QString detect;
    for (qint32 i = 0; i < len; ++i)
    {
        detect += bytes.at(index + i);
    }
    index += len;
    client.setDetectAddr(detect);

    client.setClientAddr(IPAddress(this->_socket->peerAddress().toString(), this->_socket->peerPort()));

    index = this->_manager->addConnectClient(client);
    qint32 magic = this->_manager->clients()->at(index).magic();
    bytes.clear();
    writeInt32(bytes, magic);
    this->_socket->write(bytes);
    this->_server->waitForNewConnection();
    emit newClient(magic);
}
