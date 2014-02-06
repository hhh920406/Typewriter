#include "moveobject.h"

MoveObject::MoveObject()
{
    this->stay = true;
    this->speed = 4;
    this->moveDirection = Defination::DIRECTION_UP;
}

bool MoveObject::move(Environment *environment)
{
    if(!stay)
    {
        switch(moveDirection)
        {
        case Defination::DIRECTION_UP:
            y -= speed;
            healthShow->y -= speed;
            if(!outJudge() || environment->hitTestType(this->x, this->y, this->width, this->height, this->type))
            {
                y += speed;
                healthShow->y += speed;
                return true;
            }
            break;
        case Defination::DIRECTION_RIGHT:
            x += speed;
            healthShow->x += speed;
            if(!outJudge() || environment->hitTestType(this->x, this->y, this->width, this->height, this->type))
            {
                x -= speed;
                healthShow->x -= speed;
                return true;
            }
            break;
        case Defination::DIRECTION_DOWN:
            y += speed;
            healthShow->y += speed;
            if(!outJudge() || environment->hitTestType(this->x, this->y, this->width, this->height, this->type))
            {
                y -= speed;
                healthShow->y -= speed;
                return true;
            }
            break;
        case Defination::DIRECTION_LEFT:
            x -= speed;
            healthShow->x -= speed;
            if(!outJudge() || environment->hitTestType(this->x, this->y, this->width, this->height, this->type))
            {
                x += speed;
                healthShow->x += speed;
                return true;
            }
            break;
        }
    }
    return false;
}

bool MoveObject::outJudge()
{
    return x>=60 && x<=540-width && y>=60 && y<=540-height;
}
