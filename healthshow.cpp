#include "healthshow.h"

HealthShow::HealthShow()
{
    this->stay = false;
    this->show = 0;
    this->currentValue = 100;
    this->maxValue = 100;
    this->x = 0;
    this->y = 0;
    this->width = 32;
    this->height = 5;
    this->colorDivide = 100;
}

void HealthShow::setValue(qint32 value)
{
    this->show = 50;
    if(value>this->maxValue)
    {
        this->currentValue = this->maxValue;
    }
    else if(value < 0)
    {
        this->currentValue = 0;
    }
    else
    {
        this->currentValue = value;
    }
}

void HealthShow::draw(QPainter *painter)
{
    if((stay || show) && currentValue)
    {
        QLinearGradient *line = new QLinearGradient(this->x, this->y, this->x+this->width, this->y+this->height);
        painter->setPen(Qt::white);
        int temp = this->currentValue / this->colorDivide;
        switch(temp)
        {
        case 0:
            line->setColorAt(0.0, QColor(0,0,0));
            line->setColorAt(1.0, QColor(0,0,0));
            break;
        case 1:
            line->setColorAt(0.0, QColor(255,0,0));
            line->setColorAt(1.0, QColor(219,0,0));
            break;
        case 2:
            line->setColorAt(0.0, QColor(255,151,49));
            line->setColorAt(1.0, QColor(221,123,46));
            break;
        case 3:
            line->setColorAt(0.0, QColor(246,255,76));
            line->setColorAt(1.0, QColor(243,206,33));
            break;
        case 4:
            line->setColorAt(0.0, QColor(96,93,255));
            line->setColorAt(1.0, QColor(27,41,177));
            break;
        default:
            line->setColorAt(0.0, QColor(208,109,255));
            line->setColorAt(1.0, QColor(177,43,161));
            break;
        }
        painter->setBrush(*line);
        painter->drawRect(x,y,width,height);
        switch(temp)
        {
        case 0:
            line->setColorAt(0.0, QColor(255,0,0));
            line->setColorAt(1.0, QColor(219,0,0));
            break;
        case 1:
            line->setColorAt(0.0, QColor(255,151,49));
            line->setColorAt(1.0, QColor(221,123,46));
            break;
        case 2:
            line->setColorAt(0.0, QColor(246,255,76));
            line->setColorAt(1.0, QColor(243,206,33));
            break;
        case 3:
            line->setColorAt(0.0, QColor(96,93,255));
            line->setColorAt(1.0, QColor(27,41,177));
            break;
        case 4:
            line->setColorAt(0.0, QColor(208,109,255));
            line->setColorAt(1.0, QColor(177,43,161));
            break;
        default:
            line->setColorAt(0.0, QColor(255,255,255));
            line->setColorAt(1.0, QColor(255,255,255));
            break;
        }
        painter->setBrush(*line);
        if(temp>5)
        {
            temp = 5;
        }
        int tempWidth = this->currentValue - temp * this->colorDivide;
        if(tempWidth > this->colorDivide)
        {
            tempWidth = this->colorDivide;
        }
        painter->drawRect(x,y,tempWidth * this->width / this->colorDivide, this->height);
        if(show)
        {
            show--;
        }
        delete line;
    }
}
