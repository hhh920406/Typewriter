#include "stage.h"

Stage::Stage()
{
    this->image = new QImage(":/images/stageBackground.png");
    this->currentStage = new Integer();
}

Stage::~Stage()
{
    delete this->image;
    delete this->currentStage;
}

bool Stage::draw(QPainter *painter, qint32 value, qint32 &time)
{
    painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH,Defination::WINDOW_HEIGHT), *image);
    currentStage->setValue(value);
    currentStage->draw(painter, 440, 280);
    time --;
    return time<=0;
}
