#include "gamebutton.h"

GameButton::GameButton(const char *imagePath)
{
    buttonImage = new QImage(imagePath);
    this->x = 0;
    this->y = 0;
    this->width = buttonImage->width();
    this->height = buttonImage->height();
    this->targetX = 0;
    enabled = true;
}

GameButton::GameButton(const char *imagePath, qint32 x, qint32 y)
{
    buttonImage = new QImage(imagePath);
    this->x = x;
    this->y = y;
    this->width = buttonImage->width();
    this->height = buttonImage->height();
    this->targetX = 0;
    enabled = true;
}

GameButton::GameButton(const char *imagePath, qint32 x, qint32 y, qint32 width, qint32 height)
{
    buttonImage = new QImage(imagePath);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->targetX = 0;
    enabled = true;
}

GameButton::~GameButton()
{
    delete buttonImage;
}

void GameButton::setImage(const char *imagePath)
{
    delete buttonImage;
    buttonImage = new QImage(imagePath);
}

void GameButton::setMousePosition(qint32 x, qint32 y)
{
    this->mouseX = x;
    this->mouseY = y;
}

void GameButton::draw(QPainter *painter)
{
    if(inArea(mouseX, mouseY) && enabled)
    {
        if(this->targetX<20)
        {
            this->targetX ++;
        }
    }
    else
    {
        if(this->targetX>0)
        {
            this->targetX --;
        }
    }
    painter->drawImage(QRect(this->x-this->targetX, this->y, this->width, this->height), *buttonImage);
}

bool GameButton::inArea(qint32 x, qint32 y)
{
    return x>this->x && y>this->y && x<this->x+this->width && y<this->y+this->height;
}
