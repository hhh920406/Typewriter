#include <QtGui/QApplication>
#include <QTranslator>
#include "tankform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("Lang_CH.qm");
    a.installTranslator(&translator);

    TankForm w;
    w.show();

    return a.exec();
}
