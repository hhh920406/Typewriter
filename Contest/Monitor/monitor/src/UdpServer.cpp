#include "ClientManager.h"
#include "TcpServer.h"
#include "UdpServer.h"

UdpServer::UdpServer(ClientManager *manager)
{
    this->_manager = manager;
    this->_socket = new QUdpSocket(this);
}

UdpServer::~UdpServer()
{
    delete this->_socket;
}

bool UdpServer::listen(qint32 port)
{
    if (this->_socket->bind(port, QUdpSocket::ShareAddress))
    {
        this->connect(this->_socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
        return true;
    }
    return false;
}

qint64 UdpServer::readInt64(QByteArray &bytes, qint32 &index)
{
    qint64 value = 0;
    for (qint32 i = 0; i < 8; ++i)
    {
        value <<= 8;
        value |= (unsigned char)bytes.at(index);
        ++index;
    }
    return value;
}

void UdpServer::writeInt64(QByteArray &bytes, qint64 value)
{
    for (qint32 i = 8; i <= 64; i += 8)
    {
        bytes.append((value >> (64 - i)) & ((1 << 8) - 1));
    }
}

void UdpServer::readMessage()
{
    QByteArray bytes;
    bytes.resize(16);
    this->_socket->readDatagram(bytes.data(), bytes.size());
    qint32 index = 0;
    qint32 magic = TcpServer::readInt32(bytes, index);
    qint64 time = UdpServer::readInt64(bytes, index);
    qint32 value = TcpServer::readInt32(bytes, index);
    ClientInfo *client = this->_manager->client(magic);
    if (0L != client)
    {
        if (value >= 0)
        {
            client->addRTT(time, value);
            client->activate();
            emit updateClient(magic);
        }
        else
        {
            client->setStatus(ClientInfo::STATUS_STOPPED);
            emit closeClient(magic);
        }
    }
}
