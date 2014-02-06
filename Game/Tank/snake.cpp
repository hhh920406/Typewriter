#include "snake.h"

Snake::Snake()
{
    this->recordX = new qint32[QueueLength];
    this->recordY = new qint32[QueueLength];
    this->position = new qint32[MaxSnakeNumber];
    this->body = new QImage(":/images/catTeacherw.png");
    this->initialSnake();
}

Snake::~Snake()
{
    delete this->recordX;
    delete this->recordY;
    delete this->position;
    delete this->body;
}

void Snake::initialSnake()
{
    this->baseSpeed = 4;
    this->accSpeed = 0;
    this->length = 3;
    this->front = 0;
    for(qint32 i=200;i<=280;i++)
    {
        this->recordX[this->front] = i;
        this->recordY[this->front] = 240;
        this->front ++;
    }
    this->position[0] = 80;
    this->position[1] = 40;
    this->position[2] = 0;
    this->angle = 0;
    this->dead = false;
}

void Snake::draw(QPainter *painter)
{
    for(qint32 i=0;i<this->length;i++)
    {
        painter->drawImage(QRect(this->recordX[this->position[i]], this->recordY[this->position[i]], 40, 40), *this->body);
    }
}

void Snake::speedUp()
{
    if(this->accSpeed < MaxAccSpeed)
    {
        this->accSpeed ++;
    }
}

void Snake::speedDown()
{
    if(this->accSpeed > 0)
    {
        this->accSpeed --;
    }
}

bool Snake::isTail(qint32 id)
{
    return id == length - 1;
}

void Snake::turnLeft()
{
    this->angle -= 0.1;
}

void Snake::turnRight()
{
    this->angle += 0.1;
}

void Snake::move()
{
    qint32 tempSpeed = this->baseSpeed + this->accSpeed / 10;
    for(int i=1;i<=tempSpeed;i++)
    {
        this->recordX[this->front] = this->recordX[this->position[0]] + i * cos(this->angle);
        this->recordY[this->front] = this->recordY[this->position[0]] + i * sin(this->angle);
        this->front ++;
        if(this->front == QueueLength)
        {
            this->front = 0;
        }
    }
    for(qint32 i=0;i<this->length;i++)
    {
        this->position[i] += tempSpeed;
        if(this->position[i] >= QueueLength)
        {
            this->position[i] -= QueueLength;
        }
    }
}

bool Snake::hitTestSelf()
{
    for(qint32 i=3;i<this->length;i++)
    {
        if((this->recordX[this->position[i]] - this->recordX[this->position[0]]) *
           (this->recordX[this->position[i]] - this->recordX[this->position[0]]) +
           (this->recordY[this->position[i]] - this->recordY[this->position[0]]) *
           (this->recordY[this->position[i]] - this->recordY[this->position[0]]) < 1000)
        {
            return true;
        }
    }
    return false;
}

bool Snake::hitTest(qint32 x, qint32 y, qint32 width, qint32 height)
{
    return this->recordX[this->position[0]] + 40 > x && this->recordY[this->position[0]] + 40 > y &&
            x + width > this->recordX[this->position[0]] && y + height > this->recordY[this->position[0]];
}

bool Snake::onPath(qint32 px, qint32 py, qint32 x1, qint32 y1, qint32 x2, qint32 y2)
{
    return (px-x1) * (y2-y1) == (py-y1) * (x2-x1) && px >= x1 && px <=x2;
}

void Snake::deathJudge()
{
    if(!this->dead)
    {
        if(this->hitTestSelf())
        {
            this->dead = true;
        }
        else
        {
            if(this->recordX[this->position[0]] < 0 || this->recordX[this->position[0]] + 40 > Defination::WINDOW_WIDTH)
            {
                this->dead = true;
            }
            else if(this->recordY[this->position[0]] < 0 || this->recordY[this->position[0]] + 40 > Defination::WINDOW_HEIGHT)
            {
                this->dead = true;
            }
        }
    }
}

void Snake::grow()
{
    this->position[this->length] = this->position[this->length - 1] - 40;
    if(this->position[this->length]<0)
    {
        this->position += QueueLength;
    }
    this->length ++;
}
