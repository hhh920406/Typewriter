#ifndef TEST_IPADDRESS_H
#define TEST_IPADDRESS_H
/**
 * The unit test for IPAddress class.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QtTest>
#include "IPAddress.h"

class test_IPAddress : public QObject
{
    Q_OBJECT
private:
    IPAddress *_address;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testInit();
    void testInit_data();
    void testPart();
    void testPart_data();
    void testLess();
    void testLess_data();
    void testEqual();
    void testEqual_data();
};

#endif // TEST_IPADDRESS_H
