#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H
/**
 * The management of client.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "ClientInfo.h"

class ClientManager
{
public:
    ClientManager();
    virtual ~ClientManager();
    int addClient(const ClientInfo &client);
    qint32 addConnectClient(const ClientInfo &client);
    void removeClient(const ClientInfo &client);
    QVector<ClientInfo>* clients();
    ClientInfo* client(qint32 magic);
    qint32 magic() const;

    bool save() const;
    bool load();

private:
    qint32 _magic;
    QVector<ClientInfo> _clients;
};

#endif // CLIENTMANAGER_H
