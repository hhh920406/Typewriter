#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QObject>

class GameWidget
{
public:
    GameWidget();
    qint32 x;
    qint32 y;
    qint32 width;
    qint32 height;
    void setPosition(qint32 x, qint32 y);
    void setSize(qint32 width, qint32 height);
};

#endif
