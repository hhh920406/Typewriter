#ifndef GAMEKEYEDIT_H
#define GAMEKEYEDIT_H

#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include "defination.h"
#include "gamewidget.h"

class GameKeyEdit : public GameWidget
{
public:
    GameKeyEdit();
    GameKeyEdit(qint32 x, qint32 y);
    GameKeyEdit(qint32 x, qint32 y, qint32 width, qint32 height);
    qint32 currentKeyValue;
    void setEdit(QMouseEvent *event);
    void draw(QPainter *painter);
    void keyDown(QKeyEvent *event);
    void mouseMove(QMouseEvent *event);
    bool inArea();
private:
    bool edit;
    qint32 mouseX;
    qint32 mouseY;
    qint32 color;
};

#endif
