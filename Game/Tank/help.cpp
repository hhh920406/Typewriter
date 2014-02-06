#include "help.h"

Help::Help()
{
    helpImage = new QImage(":/images/helpBackground.png");
}

Help::~Help()
{
    delete helpImage;
}

void Help::draw(QPainter *painter)
{
    painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH,Defination::WINDOW_HEIGHT), *helpImage);
}
