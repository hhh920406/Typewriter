#include "test_ClientManager.h"

void test_ClientManager::testAdd()
{
    QFETCH(QString, name);
    QFETCH(QString, clientIp);
    QFETCH(qint32, clientPort);
    QFETCH(QString, detect);
    QFETCH(qint32, size);
    ClientInfo client;
    client.setName(name);
    client.setClientAddr(IPAddress(clientIp, clientPort));
    client.setDetectAddr(detect);
    this->_manager.addClient(client);
    QCOMPARE(this->_manager.clients()->size(), size);
}

void test_ClientManager::testAdd_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("clientIp");
    QTest::addColumn<qint32>("clientPort");
    QTest::addColumn<QString>("detect");
    QTest::addColumn<qint32>("size");
    QTest::newRow("Add1") << "Client 1" << "127.0.0.1" << 19627 << "127.0.0.1" << 1;
    QTest::newRow("Add2") << "Client 1" << "127.0.0.1" << 19627 << "127.0.0.1" << 2;
    QTest::newRow("Add3") << "Client 1" << "127.0.0.1" << 19627 << "127.0.0.1" << 2;
    QTest::newRow("Add4") << "Client 1" << "127.0.0.1" << 19627 << "127.0.0.1" << 2;
    QTest::newRow("Add5") << "Client 1" << "127.0.0.1" << 19626 << "127.0.0.1" << 3;
}

void test_ClientManager::testRemove()
{
    QFETCH(QString, name);
    QFETCH(QString, clientIp);
    QFETCH(qint32, clientPort);
    QFETCH(QString, detect);
    QFETCH(qint32, size);
    ClientInfo client;
    client.setName(name);
    client.setClientAddr(IPAddress(clientIp, clientPort));
    client.setDetectAddr(detect);
    this->_manager.removeClient(client);
    QCOMPARE(this->_manager.clients()->size(), size);
}

void test_ClientManager::testRemove_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("clientIp");
    QTest::addColumn<qint32>("clientPort");
    QTest::addColumn<QString>("detect");
    QTest::addColumn<qint32>("size");
    QTest::newRow("Remove1") << "Client 1" << "127.0.0.1" << 19627 << "127.0.0.1" << 2;
    QTest::newRow("Remove2") << "Client 1" << "127.0.0.1" << 19626 << "127.0.0.1" << 2;
}

void test_ClientManager::testIO()
{
    this->_manager.save();
    ClientManager newManager;
    newManager.load();
    QCOMPARE(this->_manager.magic(), newManager.magic());
    QCOMPARE(this->_manager.clients()->size(), newManager.clients()->size());
    for (qint32 i = 0; i < this->_manager.clients()->size(); ++i)
    {
        QCOMPARE(this->_manager.clients()->at(i), newManager.clients()->at(i));
    }
}

void test_ClientManager::testIO_data()
{
}
