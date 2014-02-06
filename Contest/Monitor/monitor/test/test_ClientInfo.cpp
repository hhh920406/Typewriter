#include "test_ClientInfo.h"

void test_ClientInfo::testIO()
{
    QFETCH(QString, name);
    QFETCH(qint32, magic);
    QFETCH(QString, clientIp);
    QFETCH(qint32, clientPort);
    QFETCH(QString, detect);
    QFETCH(qint32, alertThreshold);
    ClientInfo saveClient, loadClient;
    saveClient.setName(name);
    saveClient.setMagic(magic);
    saveClient.setClientAddr(IPAddress(clientIp, clientPort));
    saveClient.setDetectAddr(detect);
    saveClient.setAlertThreshold(alertThreshold);
    saveClient.save("test_ClientInfo.io");
    loadClient.load("test_ClientInfo.io");
    QCOMPARE(loadClient.name(), name);
    QCOMPARE(loadClient.magic(), magic);
    QCOMPARE(loadClient.clientAddr().ip(), clientIp);
    QCOMPARE(loadClient.clientAddr().port(), clientPort);
    QCOMPARE(loadClient.detectAddr(), detect);
    QCOMPARE(loadClient.alertThreshold(), alertThreshold);
}

void test_ClientInfo::testIO_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<qint32>("magic");
    QTest::addColumn<QString>("clientIp");
    QTest::addColumn<qint32>("clientPort");
    QTest::addColumn<QString>("detect");
    QTest::addColumn<qint32>("alertThreshold");
    QTest::newRow("IO") << "IO Test" << 19627 << "202.118.98.163" << 4824 << 9534 << 1000;
}
