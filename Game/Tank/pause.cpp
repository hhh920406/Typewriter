#include "pause.h"

Pause::Pause()
{
    this->image = new QImage(":/images/pauseBackground.png");
}

Pause::~Pause()
{
    delete image;
}

void Pause::draw(QPainter *painter)
{
    painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH,Defination::WINDOW_HEIGHT), *image);
}
