#ifndef CHOICE_H
#define CHOICE_H

#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include "gamebutton.h"
#include "defination.h"

class Choice
{
public:
    Choice();
    ~Choice();
    void draw(QPainter *painter);
    qint32 mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QImage *background;
    GameButton *backButton;
    GameButton *infinityButton;
    GameButton *snakeButton;
    GameButton *cellButton;
    GameButton *aboutButton;
};

#endif
