#include "gamekeyedit.h"

GameKeyEdit::GameKeyEdit()
{
    this->x = 0;
    this->y = 0;
    this->width = 50;
    this->height = 15;
    this->edit = false;
    this->currentKeyValue = 0;
    this->color = 255;
}

GameKeyEdit::GameKeyEdit(qint32 x, qint32 y)
{
    this->x = x;
    this->y = y;
    this->width = 50;
    this->height = 15;
    this->edit = false;
    this->currentKeyValue = 0;
    this->color = 255;
}

GameKeyEdit::GameKeyEdit(qint32 x, qint32 y, qint32 width, qint32 height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->edit = false;
    this->currentKeyValue = 0;
    this->color = 255;
}

void GameKeyEdit::setEdit(QMouseEvent *event)
{
    this->edit = false;
    if(event->x() > this->x && event->x() < this->x + this->width)
    {
        if(event->y() > this->y && event->y() < this->y + this->height)
        {
            this->edit = true;
        }
    }
}

void GameKeyEdit::keyDown(QKeyEvent *event)
{
    if(this->edit)
    {
        this->currentKeyValue = event->key();
    }
}

void GameKeyEdit::draw(QPainter *painter)
{
    painter->setPen(Qt::black);
    if(this->edit)
    {
        painter->setPen(Qt::red);
    }
    if(this->inArea())
    {
        if(this->color > 150)
        {
            this->color -= 2;
        }
    }
    else
    {
        if(this->color < 255)
        {
            this->color += 2;
        }
    }
    painter->setBrush(QColor(255, 255, this->color));
    painter->drawRoundRect(this->x, this->y , this->width, this->height, 10, 10);
    painter->setFont(QFont("Consolas", 12));
    painter->drawText(this->x + this->width / 2 - 4, this->y + this->height / 2 + 5, QString(this->currentKeyValue));
}

void GameKeyEdit::mouseMove(QMouseEvent *event)
{
    this->mouseX = event->x();
    this->mouseY = event->y();
}

bool GameKeyEdit::inArea()
{
    return this->mouseX > this->x && this->mouseX < this->x + this->width &&
            this->mouseY > this->y && this->mouseY < this->y + this->height;
}
