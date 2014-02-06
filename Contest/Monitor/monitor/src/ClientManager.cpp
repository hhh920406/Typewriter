#include <ctime>
#include <cstdlib>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "ClientManager.h"

ClientManager::ClientManager()
{
    this->_magic = 0;
}

ClientManager::~ClientManager()
{
}

int ClientManager::addClient(const ClientInfo &client)
{
    for (qint32 i = 0; i < this->_clients.size(); ++i)
    {
        if (client == this->_clients[i])
        {
            return i;
        }
    }
    ClientInfo newClient = client;
    newClient.setMagic(++this->_magic);
    srand(time(NULL));
    newClient.setColor(QColor::fromRgb(rand() % 256, rand() % 256, rand() % 256));
    newClient.setShow(false);
    newClient.setAlert(false);
    newClient.setAlertThreshold(1000);
    newClient.activate();
    this->_clients.append(newClient);
    this->save();
    return this->_clients.size() - 1;
}

qint32 ClientManager::addConnectClient(const ClientInfo &client)
{
    qint32 index = addClient(client);
    this->_clients[index].setShow(true);
    this->_clients[index].setAlert(true);
    this->_clients[index].setStatus(ClientInfo::STATUS_MONITORING);
    return index;
}

void ClientManager::removeClient(const ClientInfo &client)
{
    for (qint32 i = 0; i < this->_clients.size(); ++i)
    {
        if (client == this->_clients[i])
        {
            this->_clients.remove(i);
            break;
        }
    }
}

QVector<ClientInfo>* ClientManager::clients()
{
    return &this->_clients;
}

ClientInfo* ClientManager::client(qint32 magic)
{
    for (qint32 i = 0; i < this->_clients.size(); ++i)
    {
        if (this->_clients[i].magic() == magic)
        {
            return &this->_clients[i];
        }
    }
    return 0L;
}

qint32 ClientManager::magic() const
{
    return this->_magic;
}

bool ClientManager::save() const
{
    QDir dir("data");
    if (!dir.exists())
    {
        dir.mkpath(".");
    }
    QFile file("data/clients.info");
    bool flag = true;
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << this->_magic << endl;
        out << this->_clients.size() << endl;
        for (qint32 i = 0; i < this->_clients.size(); ++i)
        {
            out << this->_clients[i].magic() << endl;
        }
        file.flush();
        file.close();
        for (int i = 0; i < this->_clients.size(); ++i)
        {
            if (!this->_clients[i].save(QString("data/%1.client").arg(this->_clients[i].magic())))
            {
                flag = false;
            }
        }
    }
    else
    {
        flag = false;
    }
    return flag;
}

bool ClientManager::load()
{
    QDir dir("data");
    if (!dir.exists())
    {
        dir.mkpath(".");
    }
    bool flag = true;
    QFile file("data/clients.info");
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            this->_magic = in.readLine().toInt();
            int num = in.readLine().toInt();
            this->_clients.clear();
            for (qint32 i = 0; i < num; ++i)
            {
                ClientInfo newClient;
                if (newClient.load(QString("data/%1.client").arg(in.readLine().toInt())))
                {
                    this->_clients.append(newClient);
                }
                else
                {
                    flag = false;
                }
            }
            file.close();
        }
        else
        {
            flag = false;
        }
    }
    else
    {
        flag = false;
    }
    return flag;
}
