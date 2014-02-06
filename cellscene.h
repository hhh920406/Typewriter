#ifndef CELLSCENE_H
#define CELLSCENE_H

#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include "defination.h"
#include "cellular.h"

class CellScene
{
public:
    CellScene();
    ~CellScene();
    void draw(QPainter *painter);
    void mouseDownEvent(QMouseEvent *event);
    void mouseMoveEvnet(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    qint32 keyReleaseEvent(QKeyEvent *event);
private:
    Cellular *celluar;
    bool running;
    bool mouseDown;
    bool showLine;
    qint32 time;
    qint32 lastX;
    qint32 lastY;
};

#endif
