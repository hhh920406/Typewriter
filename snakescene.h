#ifndef SNAKESCENE_H
#define SNAKESCENE_H

#include <QPainter>
#include <QImage>
#include <QKeyEvent>
#include "defination.h"
#include "config.h"
#include "snake.h"

class SnakeScene
{
public:
    SnakeScene();
    ~SnakeScene();
    void initialStage();
    void bindConfig(Config *config);
    qint32 draw(QPainter *painter);
    void keyDownEvent(QKeyEvent *event);
    qint32 keyReleaseEvent(QKeyEvent *event);
    void setFood();
private:
    QImage *background;
    QImage *food;
    bool left;
    bool right;
    bool accelerate;
    bool decelerate;
    qint32 foodX;
    qint32 foodY;
    qint32 stayTime;
    Snake *snake;
    Config *config;
};

#endif
