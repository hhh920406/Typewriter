#ifndef CLIENTINFO_H
#define CLIENTINFO_H
/**
 * The information of the client.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QColor>
#include <QVector>
#include <QString>
#include <QDateTime>
#include "IPAddress.h"

class ClientInfo
{
public:
    enum ClientStatus
    {
        STATUS_STOPPED,
        STATUS_MONITORING,
        STATUS_SUSPENDING
    };

    ClientInfo();
    virtual ~ClientInfo();
    const QString name() const;
    void setName(const QString &name);
    qint32 magic() const;
    void setMagic(const qint32 magic);
    const IPAddress clientAddr() const;
    void setClientAddr(const IPAddress addr);
    const QString detectAddr() const;
    void setDetectAddr(const QString &addr);
    qint32 alertThreshold() const;
    void setAlertThreshold(const qint32 threshold);
    QColor color() const;
    void setColor(const QColor &color);
    QString lastActivity() const;
    void activate();

    ClientStatus status() const;
    void setStatus(const ClientStatus status);
    QVector<qint32>* getRTTs();
    void addRTT(const qint64 time, const qint32 rtt);
    QVector<qint64>* times();
    QVector<qint32>* rtts();
    bool show() const;
    void setShow(const bool value);
    bool alert() const;
    void setAlert(const bool value);

    bool save(const QString &filePath) const;
    bool load(const QString &filePath);

    friend bool operator ==(const ClientInfo &a, const ClientInfo &b);

private:
    QString _name;
    qint32 _magic;
    IPAddress _clientAddr;
    QString _detectAddr;
    qint32 _alertThreshold;
    QColor _color;
    QDateTime _lastActivity;

    ClientStatus _status;
    QVector<qint64> _times;
    QVector<qint32> _rtts;
    bool _show;
    bool _alert;
};

#endif // CLIENTINFO_H
