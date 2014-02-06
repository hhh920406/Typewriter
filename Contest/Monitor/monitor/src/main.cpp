#include "MainWindow.h"
#include <QApplication>
#include <QtTest>

//#define UNIT_TEST

#ifdef UNIT_TEST
#include "test_IPAddress.h"
#include "test_ClientInfo.h"
#include "test_ClientManager.h"
#endif

int main(int argc, char *argv[])
{
#ifdef UNIT_TEST
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    test_IPAddress ipAddress;
    test_ClientInfo clientInfo;
    test_ClientManager clientManager;
    QTest::qExec(&ipAddress);
    QTest::qExec(&clientInfo);
    QTest::qExec(&clientManager);
    return 0;
#else
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
#endif
}
