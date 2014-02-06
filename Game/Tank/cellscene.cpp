#include "cellscene.h"

CellScene::CellScene()
{
    this->celluar = new Cellular(80, 60);
    this->celluar->setSide(10);
    this->running = false;
    this->time = 0;
    this->lastX = -1;
    this->lastY = -1;
    this->mouseDown = false;
    this->showLine = true;
}

CellScene::~CellScene()
{
    delete this->celluar;
}

void CellScene::draw(QPainter *painter)
{
    if(this->running)
    {
        this->time ++;
        if(this->time % 10)
        {
            this->celluar->nextGeneration();
        }
    }
    this->celluar->draw(painter);
}

void CellScene::mouseDownEvent(QMouseEvent *event)
{
    if(!this->running)
    {
        this->mouseDown = true;
        this->lastX = event->y() / this->celluar->side;
        this->lastY = event->x() / this->celluar->side;
        this->celluar->opposite(lastX, lastY);
    }
}

void CellScene::mouseMoveEvnet(QMouseEvent *event)
{
    if(this->mouseDown)
    {
        qint32 tempX = event->y() / this->celluar->side;
        qint32 tempY = event->x() / this->celluar->side;
        if(tempX != this->lastX && tempY != this->lastY)
        {
            this->lastX = tempX;
            this->lastY = tempY;
            this->celluar->opposite(this->lastX, this->lastY);
        }
    }
}

void CellScene::mouseReleaseEvent(QMouseEvent *event)
{
    this->lastX = -1;
    this->lastY = -1;
    this->mouseDown = false;
}

qint32 CellScene::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        return Defination::SCENE_MAIN;
    case Qt::Key_C:
        this->celluar->clear();
        this->running = false;
        break;
    case Qt::Key_S:
        this->running = true;
        break;
    case Qt::Key_R:
        this->running = false;
        this->celluar->randomInitial();
        break;
    case Qt::Key_L:
        this->showLine ^= 1;
        if(this->showLine)
        {
            this->celluar->lineColor->setAlpha(200);
        }
        else
        {
            this->celluar->lineColor->setAlpha(0);
        }
        break;
    case Qt::Key_T:
        this->celluar->showGenerationNumber ^= 1;
        break;
    }
    return Defination::SCENE_CELL;
}
