#ifndef IPADDRESS_H
#define IPADDRESS_H
/**
 * The IPv4 address.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QString>

class IPAddress
{
public:
    IPAddress();
    IPAddress(const QString &ip, const qint32 port);
    virtual ~IPAddress();
    QString ip() const;
    void setIp(const QString &ip);
    qint32 port() const;
    void setPort(const qint32 port);
    qint32 part(const qint32 index) const;
    void setPart(const qint32 index, const qint32 num);
    const QString toString() const;

    friend bool operator <(const IPAddress &a, const IPAddress &b);
    friend bool operator >(const IPAddress &a, const IPAddress &b);
    friend bool operator ==(const IPAddress &a, const IPAddress &b);

private:
    QString _ip;
    qint32 _port;
    qint32 _part[4];
};

#endif // IPADDRESS_H
