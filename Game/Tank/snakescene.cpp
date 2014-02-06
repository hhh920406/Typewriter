#include "snakescene.h"

SnakeScene::SnakeScene()
{
    this->background = new QImage(":/images/snakeBackground.png");
    this->food = new QImage(":/images/catTeacherb.png");
    this->snake = new Snake();
    this->initialStage();
}

SnakeScene::~SnakeScene()
{
    delete this->background;
    delete this->food;
    delete this->snake;
}

void SnakeScene::initialStage()
{
    this->left = false;
    this->right = false;
    this->accelerate = false;
    this->decelerate = false;
    this->snake->initialSnake();
    this->stayTime = 0;
    this->setFood();
}

void SnakeScene::setFood()
{
    this->foodX = rand() % (Defination::WINDOW_WIDTH - 100) + 50;
    this->foodY = rand() % (Defination::WINDOW_HEIGHT - 100) + 50;
}

void SnakeScene::bindConfig(Config *config)
{
    this->config = config;
}

qint32 SnakeScene::draw(QPainter *painter)
{
    painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH, Defination::WINDOW_HEIGHT), *this->background);
    painter->drawImage(QRect(this->foodX, this->foodY, 40, 40), *this->food);
    this->snake->draw(painter);
    if(this->snake->dead)
    {
        if(this->stayTime < 50)
        {
            this->stayTime ++;
        }
        else
        {
            return Defination::SCENE_OVER;
        }
    }
    else
    {
        if(this->left)
        {
            this->snake->turnLeft();
        }
        if(this->right)
        {
            this->snake->turnRight();
        }
        if(this->accelerate)
        {
            this->snake->speedUp();
        }
        if(this->decelerate)
        {
            this->snake->speedDown();
        }
        this->snake->move();
        this->snake->deathJudge();
        if(snake->hitTest(this->foodX, this->foodY, 40, 40))
        {
            this->snake->grow();
            this->setFood();
        }
    }
    return Defination::SCENE_SNAKE;
}

void SnakeScene::keyDownEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        if(event->key() == this->config->gameKeyEdit[Defination::GAMEKEY_LEFT]->currentKeyValue)
        {
            this->left = true;
        }
        else if(event->key() == this->config->gameKeyEdit[Defination::GAMEKEY_RIGHT]->currentKeyValue)
        {
            this->right = true;
        }
        else if(event->key() == this->config->gameKeyEdit[Defination::GAMEKEY_UP]->currentKeyValue)
        {
            this->accelerate = true;
        }
        else if(event->key() == this->config->gameKeyEdit[Defination::GAMEKEY_DOWN]->currentKeyValue)
        {
            this->decelerate = true;
        }
    }
}

qint32 SnakeScene::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        if(event->key() == this->config->gameKeyEdit[Defination::GAMEKEY_LEFT]->currentKeyValue)
        {
            this->left = false;
        }
        else if(event->key() == this->config->gameKeyEdit[Defination::GAMEKEY_RIGHT]->currentKeyValue)
        {
            this->right = false;
        }
        else if(event->key() == this->config->gameKeyEdit[Defination::GAMEKEY_UP]->currentKeyValue)
        {
            this->accelerate = false;
        }
        else if(event->key() == this->config->gameKeyEdit[Defination::GAMEKEY_DOWN]->currentKeyValue)
        {
            this->decelerate = false;
        }
        else if(event->key() == this->config->gameKeyEdit[Defination::GAMEKEY_PAUSE]->currentKeyValue)
        {
            return Defination::SCENE_PAUSE;
        }
    }
    return Defination::SCENE_SNAKE;
}
