#ifndef TEST_CLIENTMANAGER_H
#define TEST_CLIENTMANAGER_H
/**
 * The unit test for ClientManager class.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QtTest>
#include "ClientManager.h"

class test_ClientManager : public QObject
{
    Q_OBJECT
private:
    ClientManager _manager;

private slots:
    void testAdd();
    void testAdd_data();
    void testRemove();
    void testRemove_data();
    void testIO();
    void testIO_data();
};

#endif // TEST_CLIENTMANAGER_H
