#include "IPAddress.h"

IPAddress::IPAddress()
{
    this->setIp("127.0.0.1");
    this->setPort(8080);
}

IPAddress::IPAddress(const QString &ip, const qint32 port)
{
    this->setIp(ip);
    this->setPort(port);
}

IPAddress::~IPAddress()
{
}

QString IPAddress::ip() const
{
    return this->_ip;
}

void IPAddress::setIp(const QString &ip)
{
    bool start = true;
    for (int i = 0, j = 0; i < ip.length(); ++i)
    {
        if (start)
        {
            this->_part[j] = 0;
            start = false;
        }
        if ('.' == ip[i])
        {
            start = true;
            ++j;
        }
        else
        {
            this->_part[j] *= 10;
            this->_part[j] += ip[i].toLatin1() - '0';
        }
    }
    this->_ip = QString("%1.%2.%3.%4").arg(this->_part[0])
            .arg(this->_part[1])
            .arg(this->_part[2])
            .arg(this->_part[3]);
}

qint32 IPAddress::port() const
{
    return this->_port;
}

void IPAddress::setPort(const qint32 port)
{
    this->_port = port;
}

qint32 IPAddress::part(const qint32 index) const
{
    if (index >= 0 && index < 4)
    {
        return this->_part[index];
    }
    return -1;
}

void IPAddress::setPart(const qint32 index, const qint32 num)
{
    if (index >= 0 && index < 4)
    {
        this->_part[index] = num;
        this->_ip = QString("%1.%2.%3.%4").arg(this->_part[0])
                .arg(this->_part[1])
                .arg(this->_part[2])
                .arg(this->_part[3]);
    }
}

const QString IPAddress::toString() const
{
    return this->_ip + QString(":%1").arg(this->_port);
}

bool operator <(const IPAddress &a, const IPAddress &b)
{
    for (int i = 0; i < 4; ++i)
    {
        if (a.part(i) < b.part(i))
        {
            return true;
        }
        else if (a.part(i) > b.part(i))
        {
            return false;
        }
    }
    return a.port() < b.port();
}

bool operator >(const IPAddress &a, const IPAddress &b)
{
    return b < a;
}

bool operator ==(const IPAddress &a, const IPAddress &b)
{
    for (qint32 i = 0; i < 4; ++i)
    {
        if (a.part(i) != b.part(i))
        {
            return false;
        }
    }
    return a.port() == b.port();
}
