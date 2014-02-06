#ifndef SNAKE_H
#define SNAKE_H

#include <QImage>
#include <QPainter>
#include <QKeyEvent>
#include <cmath>
#include "defination.h"

#define MaxSnakeNumber 300
#define MaxAccSpeed 40
#define QueueLength 500000

class Snake
{
public:
    Snake();
    ~Snake();
    void initialSnake();
    void draw(QPainter *painter);
    void move();
    void speedUp();
    void speedDown();
    void turnLeft();
    void turnRight();
    bool hitTest(qint32 x, qint32 y, qint32 width, qint32 height);
    bool hitTestSelf();
    bool isTail(qint32 id);
    bool onPath(qint32 px, qint32 py, qint32 x1, qint32 y1, qint32 x2, qint32 y2);
    void deathJudge();
    void grow();
    bool dead;
private:
    qint32 baseSpeed;
    qint32 accSpeed;
    qint32 length;
    double angle;
    qint32 front;
    qint32 *recordX;
    qint32 *recordY;
    qint32 *position;
    QImage *body;
};

#endif
