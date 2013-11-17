#include "test_IPAddress.h"

void test_IPAddress::initTestCase()
{
    this->_address = new IPAddress("127.0.0.1", 19627);
}

void test_IPAddress::cleanupTestCase()
{
    delete this->_address;
}

void test_IPAddress::testInit()
{
    QFETCH(QString, ip);
    QFETCH(qint32, port);
    QFETCH(QString, result);
    this->_address->setIp(ip);
    this->_address->setPort(port);
    QCOMPARE(this->_address->toString(), result);
}

void test_IPAddress::testInit_data()
{
    QTest::addColumn<QString>("ip");
    QTest::addColumn<qint32>("port");
    QTest::addColumn<QString>("result");
    QTest::newRow("Init_Normal") << "192.168.1.1" << 1234 << "192.168.1.1:1234";
    QTest::newRow("Init_Redundancy") << "127.000.000.001" << 19627 << "127.0.0.1:19627";
}

void test_IPAddress::testPart()
{
    QFETCH(QString, ip);
    QFETCH(qint32, port);
    QFETCH(qint32, index);
    QFETCH(qint32, value);
    QFETCH(QString, result);
    this->_address->setIp(ip);
    this->_address->setPort(port);
    this->_address->setPart(index, value);
    QCOMPARE(this->_address->toString(), result);
}

void test_IPAddress::testPart_data()
{
    QTest::addColumn<QString>("ip");
    QTest::addColumn<qint32>("port");
    QTest::addColumn<qint32>("index");
    QTest::addColumn<qint32>("value");
    QTest::addColumn<QString>("result");
    QTest::newRow("Part_Normal") << "192.168.1.1" << 19627 << 3 << 255 << "192.168.1.255:19627";
    QTest::newRow("Part_Low") << "192.168.001.1" << 19627 << -1 << 255 << "192.168.1.1:19627";
    QTest::newRow("Part_High") << "192.168.1.001" << 19627 << 4 << 255 << "192.168.1.1:19627";
}

void test_IPAddress::testLess()
{
    QFETCH(QString, ip1);
    QFETCH(qint32, port1);
    QFETCH(QString, ip2);
    QFETCH(qint32, port2);
    QFETCH(bool, result);
    IPAddress a(ip1, port1);
    IPAddress b(ip2, port2);
    QCOMPARE(a < b, result);
    QCOMPARE(a > b, !result);
}

void test_IPAddress::testLess_data()
{
    QTest::addColumn<QString>("ip1");
    QTest::addColumn<qint32>("port1");
    QTest::addColumn<QString>("ip2");
    QTest::addColumn<qint32>("port2");
    QTest::addColumn<bool>("result");
    QTest::newRow("Compare_Less_1") << "127.0.0.1" << 1234 << "192.168.1.1" << 19627 << true;
    QTest::newRow("Compare_Less_2") << "192.168.0.1" << 1234 << "192.168.1.1" << 19627 << true;
    QTest::newRow("Compare_Less_3") << "192.168.1.1" << 19627 << "192.168.1.1" << 1234 << false;
}

void test_IPAddress::testEqual()
{
    QFETCH(QString, ip1);
    QFETCH(qint32, port1);
    QFETCH(QString, ip2);
    QFETCH(qint32, port2);
    QFETCH(bool, result);
    IPAddress a(ip1, port1);
    IPAddress b(ip2, port2);
    QCOMPARE(a == b, result);
}

void test_IPAddress::testEqual_data()
{
    QTest::addColumn<QString>("ip1");
    QTest::addColumn<qint32>("port1");
    QTest::addColumn<QString>("ip2");
    QTest::addColumn<qint32>("port2");
    QTest::addColumn<bool>("result");
    QTest::newRow("Compare_Equal_1") << "192.168.1.1" << 19627 << "192.168.1.1" << 19627 << true;
    QTest::newRow("Compare_Equal_2") << "192.168.1.1" << 19627 << "192.168.1.1" << 1234 << false;
    QTest::newRow("Compare_Equal_3") << "192.168.0.1" << 19627 << "192.168.1.1" << 19627 << false;
}
