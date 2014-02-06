#include "over.h"

Over::Over()
{
    image = new QImage(":/images/overBackground.png");
}

Over::~Over()
{
    delete image;
}

bool Over::draw(QPainter *painter, qint32 &time)
{
    painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH, Defination::WINDOW_HEIGHT), *image);
    time --;
    return time <= 0;
}
