#include "choice.h"

Choice::Choice()
{
    this->background = new QImage(":/images/background.png");
    this->backButton = new GameButton(":/button/back.png", 600, 500);
    this->infinityButton = new GameButton(":/button/infinity.png", 40, 60);
    this->snakeButton = new GameButton(":/button/snake.png", 40, 120);
    this->cellButton = new GameButton(":/button/cell.png", 40, 180);
    this->aboutButton = new GameButton(":/button/about.png", 40, 240);
}

Choice::~Choice()
{
    delete this->background;
    delete this->backButton;
    delete this->infinityButton;
    delete this->snakeButton;
    delete this->cellButton;
    delete this->aboutButton;
}

void Choice::draw(QPainter *painter)
{
    painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH,Defination::WINDOW_HEIGHT), *this->background);
    this->backButton->draw(painter);
    this->infinityButton->draw(painter);
    this->snakeButton->draw(painter);
    this->cellButton->draw(painter);
    this->aboutButton->draw(painter);
}

void Choice::mouseMoveEvent(QMouseEvent *event)
{
    this->backButton->setMousePosition(event->x(), event->y());
    this->infinityButton->setMousePosition(event->x(), event->y());
    this->snakeButton->setMousePosition(event->x(), event->y());
    this->cellButton->setMousePosition(event->x(), event->y());
    this->aboutButton->setMousePosition(event->x(), event->y());
}

qint32 Choice::mouseReleaseEvent(QMouseEvent *event)
{
    if(this->backButton->inArea(event->x(), event->y()))
    {
        return Defination::SCENE_MAIN;
    }
    if(this->infinityButton->inArea(event->x(), event->y()))
    {
        return Defination::SCENE_STAGE;
    }
    if(this->snakeButton->inArea(event->x(), event->y()))
    {
        return Defination::SCENE_SNAKE;
    }
    if(this->cellButton->inArea(event->x(), event->y()))
    {
        return Defination::SCENE_CELLINTRO;
    }
    if(this->aboutButton->inArea(event->x(), event->y()))
    {
        return Defination::SCENE_ABOUT;
    }
    return Defination::SCENE_CHOICE;
}
