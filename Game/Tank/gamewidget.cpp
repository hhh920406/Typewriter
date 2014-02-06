#include "gamewidget.h"

GameWidget::GameWidget()
{
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
}

void GameWidget::setPosition(qint32 x, qint32 y)
{
    this->x = x;
    this->y = y;
}

void GameWidget::setSize(qint32 width, qint32 height)
{
    this->width = width;
    this->height = height;
}
