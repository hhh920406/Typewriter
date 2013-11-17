#include <QFile>
#include <QTextCodec>
#include <QTextStream>
#include "ClientInfo.h"

ClientInfo::ClientInfo()
{
    this->setMagic(-1);
    this->setAlertThreshold(-1);
    this->setStatus(STATUS_STOPPED);
    this->setAlert(true);
}

ClientInfo::~ClientInfo()
{
}

const QString ClientInfo::name() const
{
    return this->_name;
}

void ClientInfo::setName(const QString &name)
{
    this->_name = name;
}

qint32 ClientInfo::magic() const
{
    return this->_magic;
}

void ClientInfo::setMagic(const qint32 magic)
{
    this->_magic = magic;
}

const IPAddress ClientInfo::clientAddr() const
{
    return this->_clientAddr;
}

void ClientInfo::setClientAddr(const IPAddress addr)
{
    this->_clientAddr = addr;
}

const QString ClientInfo::detectAddr() const
{
    return this->_detectAddr;
}

void ClientInfo::setDetectAddr(const QString &addr)
{
    this->_detectAddr = addr;
}

qint32 ClientInfo::alertThreshold() const
{
    return this->_alertThreshold;
}

void ClientInfo::setAlertThreshold(const qint32 threshold)
{
    this->_alertThreshold = threshold;
}

QColor ClientInfo::color() const
{
    return this->_color;
}

void ClientInfo::setColor(const QColor &color)
{
    this->_color = color;
}

QString ClientInfo::lastActivity() const
{
    return this->_lastActivity.toString("yyyy-MM-dd hh:mm:ss");
}

void ClientInfo::activate()
{
    this->_lastActivity = QDateTime::currentDateTime();
}

ClientInfo::ClientStatus ClientInfo::status() const
{
    return this->_status;
}

void ClientInfo::setStatus(const ClientInfo::ClientStatus status)
{
    this->_status = status;
}

QVector<qint32>* ClientInfo::getRTTs()
{
    return &this->_rtts;
}

void ClientInfo::addRTT(const qint64 time, const qint32 rtt)
{
    this->_times.append(time);
    this->_rtts.append(rtt);
    if (this->_rtts.size() > 1024)
    {
        this->_times.pop_front();
        this->_rtts.pop_front();
    }
}

QVector<qint64>* ClientInfo::times()
{
    return &this->_times;
}

QVector<qint32>* ClientInfo::rtts()
{
    return &this->_rtts;
}

bool ClientInfo::show() const
{
    return this->_show;
}

void ClientInfo::setShow(const bool value)
{
    this->_show = value;
}

bool ClientInfo::alert() const
{
    return this->_alert;
}

void ClientInfo::setAlert(const bool value)
{
    this->_alert = value;
}

bool operator ==(const ClientInfo &a, const ClientInfo &b)
{
    return a.name() == b.name() &&
            a.clientAddr().ip() == b.clientAddr().ip() &&
            a.detectAddr() == b.detectAddr();
}

bool ClientInfo::save(const QString &filePath) const
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out.setCodec(QTextCodec::codecForName("UTF-8"));
        out << this->name() << endl;
        out << this->magic() << endl;
        out << this->clientAddr().ip() << endl;
        out << this->clientAddr().port() << endl;
        out << this->detectAddr() << endl;
        out << this->alertThreshold() << endl;
        out << this->color().red() << endl;
        out << this->color().green() << endl;
        out << this->color().blue() << endl;
        out << this->lastActivity() << endl;
        file.flush();
        file.close();
        return true;
    }
    return false;
}

bool ClientInfo::load(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in.setCodec(QTextCodec::codecForName("UTF-8"));
        this->setName(in.readLine());
        this->setMagic(in.readLine().toInt());
        QString ip = in.readLine();
        qint32 port = in.readLine().toInt();
        this->setClientAddr(IPAddress(ip, port));
        this->setDetectAddr(in.readLine());
        this->setAlertThreshold(in.readLine().toInt());
        int r = in.readLine().toInt();
        int g = in.readLine().toInt();
        int b = in.readLine().toInt();
        this->setColor(QColor::fromRgb(r, g, b));
        this->_lastActivity = QDateTime::fromString(in.readLine(), "yyyy-MM-dd hh:mm:ss");
        file.close();
        return true;
    }
    return false;
}
