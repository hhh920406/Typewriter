#ifndef TEST_CLIENTINFO_H
#define TEST_CLIENTINFO_H
/**
 * The unit test for ClientInfo class.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QtTest>
#include "ClientInfo.h"

class test_ClientInfo : public QObject
{
    Q_OBJECT
private slots:
    void testIO();
    void testIO_data();
};

#endif // TEST_CLIENTINFO_H
