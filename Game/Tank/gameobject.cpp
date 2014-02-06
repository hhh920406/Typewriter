#include "gameobject.h"

GameObject::GameObject()
{
    type = Defination::TYPE_NULL;
    destroyable = false;
    movable = false;
    visiable = true;
    walkable = false;
    enabled = true;
    currentLife = 19627;
    maxLife = 19627;
    x = 0;
    y = 0;
    width = 32;
    height = 32;
    healthShow = new HealthShow();
}

GameObject::~GameObject()
{
    delete healthShow;
}

void GameObject::setLife(qint32 value)
{
    if(value > this->maxLife)
    {
        this->currentLife = maxLife;
    }
    else if(value <= 0)
    {
        this->currentLife = 0;
        this->enabled = false;
    }
    else
    {
        this->currentLife = value;
    }
    healthShow->setValue(value);
}

void GameObject::setMaxLife(qint32 value)
{
    this->maxLife = value;
    healthShow->maxValue = value;
}

void GameObject::setPosition(qint32 x, qint32 y)
{
    this->x = x;
    this->y = y;
    healthShow->x = x;
    healthShow->y = y - 7;
}

void GameObject::setSize(qint32 width, qint32 height)
{
    this->width = width;
    this->height = height;
    healthShow->width = width;
    healthShow->height = 4;
}

bool GameObject::hitTest(qint32 x, qint32 y, qint32 width, qint32 height)
{
    return this->x + this->width > x &&
            this->y + this->height > y &&
            x + width > this->x &&
            y + height > this->y;
}

bool GameObject::inArea(qint32 vx, qint32 vy)
{
    return vx >= x && vy >= y && vx <= x + width && vy <= y + height;
}

void GameObject::draw(QPainter *painter, QImage *image)
{
    painter->drawImage(QRect(this->x, this->y, this->width, this->height), *image);
}
