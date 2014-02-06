#include "tank.h"

Tank::Tank()
{
    currentBulletNumber = 300;
    maximumBulletNumber = 300;
    currentMineNumber = 5;
    maximumMineNumber = 5;
    for(qint32 i=0;i<5;i++)
    {
        bullet[i] = new MoveObject();
        mine[i] = new MoveObject();
        bullet[i]->stay = false;
        bullet[i]->width = 8;
        bullet[i]->height = 8;
        bullet[i]->speed = 6;
        bullet[i]->type = Defination::TYPE_BULLET;
        mine[i]->width = 40;
        mine[i]->height = 40;
        mine[i]->type = Defination::TYPE_MINE;
    }
    bulletStatus = 0;
    mineStatus = 0;
    this->energy = 1;
    this->maxEnergy = 500;
    this->decreaseCatEnergy = 1;
    this->decreaseTrueCatEnergy = 2;
    this->catStatus = false;
    this->trueCatStatus = false;
}

Tank::~Tank()
{
    for(qint32 i=0;i<5;i++)
    {
        delete bullet[i];
        delete mine[i];
    }
}

void Tank::fire()
{
    if(currentBulletNumber)
    {
        qint32 i;
        for(i=0;i<5;i++)
        {
            if(0 == (bulletStatus & (1<<i)))
            {
                break;
            }
        }
        if(i<5)
        {
            this->currentBulletNumber --;
            bulletStatus |= (1<<i);
            switch(this->moveDirection)
            {
            case Defination::DIRECTION_UP:
                bullet[i]->x = this->x + this->width / 2;
                bullet[i]->y = this->y;
                break;
            case Defination::DIRECTION_RIGHT:
                bullet[i]->x = this->x + this->width;
                bullet[i]->y = this->y + this->height / 2;
                break;
            case Defination::DIRECTION_DOWN:
                bullet[i]->x = this->x + this->width / 2;
                bullet[i]->y = this->y + this->height;
                break;
            case Defination::DIRECTION_LEFT:
                bullet[i]->x = this->x;
                bullet[i]->y = this->y + this->height / 2;
            }
            bullet[i]->moveDirection = this->moveDirection;
        }
    }
}

void Tank::setMine()
{
    if(currentMineNumber)
    {
        qint32 i;
        for(i=0;i<5;i++)
        {
            if(0 == (mineStatus & (1<<i)))
            {
                break;
            }
        }
        if(i<5)
        {
            this->currentMineNumber --;
            mineStatus |= (1<<i);
            mine[i]->x = this->x;
            mine[i]->y = this->y;
        }
    }
}

void Tank::draw(QPainter *painter, QImage *tank[4], QImage *bullet[4], QImage *mine, Environment *environment)
{
     for(qint32 i=0;i<5;i++)
     {
        if(bulletStatus & (1<<i))
        {
            if(this->bullet[i]->move(environment))
            {
                bulletStatus -= (1<<i);
            }
            else
            {
                painter->drawImage(QRect(this->bullet[i]->x - this->bullet[i]->width / 2, this->bullet[i]->y - this->bullet[i]->height / 2, this->bullet[i]->width, this->bullet[i]->height), *bullet[this->bullet[i]->moveDirection]);
            }
        }
        if(mineStatus & (1<<i))
        {
            painter->drawImage(QRect(this->mine[i]->x, this->mine[i]->y, this->mine[i]->width, this->mine[i]->height), *mine);
        }
    }
    if(this->visiable)
    {
        this->healthShow->draw(painter);
        painter->drawImage(QRect(this->x, this->y, this->width, this->height), *tank[this->moveDirection]);
    }
}

void Tank::draw(QPainter *painter, QImage *tank, QImage *bullet[4], QImage *mine, Environment *environment)
{
     for(qint32 i=0;i<5;i++)
     {
        if(bulletStatus & (1<<i))
        {
            if(this->bullet[i]->move(environment))
            {
                bulletStatus -= (1<<i);
            }
            else
            {
                painter->drawImage(QRect(this->bullet[i]->x - this->bullet[i]->width / 2, this->bullet[i]->y - this->bullet[i]->height / 2, this->bullet[i]->width, this->bullet[i]->height), *bullet[this->bullet[i]->moveDirection]);
            }
        }
        if(mineStatus & (1<<i))
        {
            painter->drawImage(QRect(this->mine[i]->x, this->mine[i]->y, this->mine[i]->width, this->mine[i]->height), *mine);
        }
    }
    if(this->visiable)
    {
        this->healthShow->draw(painter);
        painter->drawImage(QRect(this->x, this->y, this->width, this->height), *tank);
    }
    this->catDecrease();
}

void Tank::turnLeft()
{
    this->moveDirection = (this->moveDirection + 3) % 4;
}

void Tank::turnRight()
{
    this->moveDirection = (this->moveDirection + 1) % 4;
}

void Tank::turnBack()
{
    this->moveDirection = (this->moveDirection + 2) % 4;
}

void Tank::autoMove(Environment *environment, qint32 level)
{
    switch(level)
    {
    case 0:
        autoMoveLevel0(environment);
        break;
    }
}

void Tank::autoMoveLevel0(Environment *environment)
{
    if(rand() % 5 == 0)
    {
        switch(rand() % 3)
        {
        case 0: this->turnLeft(); break;
        case 1: this->turnRight(); break;
        case 2: this->turnBack(); break;
        }
    }
    if(!this->catStatus && rand()%7==0)this->fire();
}

qint32 Tank::hitTestBullet(qint32 x, qint32 y, qint32 width, qint32 height)
{
    qint32 flag = -1;
    for(qint32 i=0;i<5;i++)
    {
        if(bulletStatus & (1<<i))
        {
            if(hitTestIn(bullet[i],x,y,width,height))
            {
                bulletStatus -= (1<<i);
                flag = i;
                break;
            }
        }
    }
    return flag;
}

bool Tank::hitTestIn(MoveObject *object, qint32 x, qint32 y, qint32 width, qint32 height)
{
    return object->x + object->width > x &&
            object->y + object->height > y &&
            x + width > object->x &&
            y + height > object->y;
}

bool Tank::inArea(qint32 tx, qint32 ty, qint32 x, qint32 y, qint32 width, qint32 height)
{
    return tx >= x && ty >=y && tx <= x + width && ty <= y + height;
}

bool Tank::move(Environment *environment, Tank *tank)
{
    if(!stay)
    {
        switch(moveDirection)
        {
        case Defination::DIRECTION_UP:
            y -= speed;
            healthShow->y -= speed;
            if(!outJudge() || environment->hitTestMove(this->x, this->y ,this->width, this->height, this->catStatus, this->trueCatStatus))
            {
                y += speed;
                healthShow->y += speed;
            }
            if(tank->hitTest(this->x, this->y, this->width, this->height))
            {
                if(this->catStatus)
                {
                    tank->setLife(0);
                }
                else
                {
                    y += speed;
                    healthShow->y += speed;
                }
            }
            break;
        case Defination::DIRECTION_RIGHT:
            x += speed;
            healthShow->x += speed;
            if(!outJudge() || environment->hitTestMove(this->x, this->y ,this->width, this->height, this->catStatus, this->trueCatStatus))
            {
                x -= speed;
                healthShow->x -= speed;
            }
            if(tank->hitTest(this->x, this->y, this->width, this->height))
            {
                if(this->catStatus)
                {
                    tank->setLife(0);
                }
                else
                {
                    x -= speed;
                    healthShow->x -= speed;
                }
            }
            break;
        case Defination::DIRECTION_DOWN:
            y += speed;
            healthShow->y += speed;
            if(!outJudge() || environment->hitTestMove(this->x, this->y ,this->width, this->height, this->catStatus, this->trueCatStatus))
            {
                y -= speed;
                healthShow->y -= speed;
            }
            if(tank->hitTest(this->x, this->y, this->width, this->height))
            {
                if(this->catStatus)
                {
                    tank->setLife(0);
                }
                else
                {
                    y -= speed;
                    healthShow->y -= speed;
                }
            }
            break;
        case Defination::DIRECTION_LEFT:
            x -= speed;
            healthShow->x -= speed;
            if(!outJudge() || environment->hitTestMove(this->x, this->y ,this->width, this->height, this->catStatus, this->trueCatStatus))
            {
                x += speed;
                healthShow->x += speed;
            }
            if(tank->hitTest(this->x, this->y, this->width, this->height))
            {
                if(this->catStatus)
                {
                    tank->setLife(0);
                }
                else
                {
                    x += speed;
                    healthShow->x += speed;
                }
            }
            break;
        }
    }
    qint32 tempBullet = tank->hitTestBullet(this->x, this->y, this->width, this->height);
    if(tempBullet != -1)
    {
        this->setLife(this->currentLife - 50);
        tank->setEnergy(tank->energy + 2);
        this->moveDirection = (tank->bullet[tempBullet]->moveDirection + 2) % 4;
        if(!this->catStatus)
        {
            this->fire();
        }
    }
    for(qint32 i=0;i<5;i++)
    {
        if(this->bulletStatus & (1<<i))
        {
            if(tank->hitTestBullet(this->bullet[i]->x, this->bullet[i]->y, this->bullet[i]->width, this->bullet[i]->height)!=-1)
            {
                tank->bulletStatus -= (1<<i);
            }
        }
        if(tank->mineStatus & (1<<i))
        {
            if(tank->mine[i]->hitTest(this->x, this->y, this->width, this->height))
            {
                tank->mineStatus -= (1<<i);
                this->setLife(this->currentLife - 200);
            }
        }
    }
    if(this->currentLife <= 0 && this->visiable)
    {
        this->visiable = false;
        this->x = 0;
        this->y = 0;
        return true;
    }
    return false;
}

bool Tank::move(Environment *environment, Tank *tank[], qint32 tankNumber)
{
    if(!stay)
    {
        switch(moveDirection)
        {
        case Defination::DIRECTION_UP:
            y -= speed;
            healthShow->y -= speed;
            if(!outJudge() || environment->hitTestMove(this->x, this->y ,this->width, this->height, this->catStatus, this->trueCatStatus))
            {
                y += speed;
                healthShow->y += speed;
            }
            else
            {
                qint32 i;
                for(i=0;i<tankNumber;i++)
                {
                    if(tank[i]->hitTest(this->x, this->y, this->width, this->height))
                    {
                        if(this->catStatus)
                        {
                            tank[i]->setLife(tank[i]->currentLife - 100);
                        }
                        break;
                    }
                }
                if(i<tankNumber)
                {
                    y += speed;
                    healthShow->y += speed;
                }
            }
            break;
        case Defination::DIRECTION_RIGHT:
            x += speed;
            healthShow->x += speed;
            if(!outJudge() || environment->hitTestMove(this->x, this->y ,this->width, this->height, this->catStatus, this->trueCatStatus))
            {
                x -= speed;
                healthShow->x -= speed;
            }
            else
            {
                qint32 i;
                for(i=0;i<tankNumber;i++)
                {
                    if(tank[i]->hitTest(this->x, this->y, this->width, this->height))
                    {
                        if(this->catStatus)
                        {
                            tank[i]->setLife(tank[i]->currentLife - 100);
                        }
                        break;
                    }
                }
                if(i<tankNumber)
                {
                    x -= speed;
                    healthShow->x -= speed;
                }
            }
            break;
        case Defination::DIRECTION_DOWN:
            y += speed;
            healthShow->y += speed;
            if(!outJudge() || environment->hitTestMove(this->x, this->y ,this->width, this->height, this->catStatus, this->trueCatStatus))
            {
                y -= speed;
                healthShow->y -= speed;
            }
            else
            {
                qint32 i;
                for(i=0;i<tankNumber;i++)
                {
                    if(tank[i]->hitTest(this->x, this->y, this->width, this->height))
                    {
                        if(this->catStatus)
                        {
                            tank[i]->setLife(tank[i]->currentLife - 100);
                        }
                        break;
                    }
                }
                if(i<tankNumber)
                {
                    y -= speed;
                    healthShow->y -= speed;
                }
            }
            break;
        case Defination::DIRECTION_LEFT:
            x -= speed;
            healthShow->x -= speed;
            if(!outJudge() || environment->hitTestMove(this->x, this->y ,this->width, this->height, this->catStatus, this->trueCatStatus))
            {
                x += speed;
                healthShow->x += speed;
            }
            else
            {
                qint32 i;
                for(i=0;i<tankNumber;i++)
                {
                    if(tank[i]->hitTest(this->x, this->y, this->width, this->height))
                    {
                        if(this->catStatus)
                        {
                            tank[i]->setLife(tank[i]->currentLife - 100);
                        }
                        break;
                    }
                }
                if(i<tankNumber)
                {
                    x += speed;
                    healthShow->x += speed;
                }
            }
            break;
        }
    }
    for(qint32 i=0;i<tankNumber;i++)
    {
        if(tank[i]->hitTestBullet(this->x, this->y, this->width, this->height) != -1)
        {
            this->setLife(this->currentLife - 50);
        }
    }
    return false;
}

void Tank::cat()
{
    if(!this->catStatus)
    {
        if(this->energy > 100)
        {
            this->catStatus = true;
        }
    }
    else
    {
        this->trueCatStatus = true;
    }
}

void Tank::catDecrease()
{
    if(this->trueCatStatus)
    {
        this->energy -= this->decreaseTrueCatEnergy;
        if(this->energy < 1)
        {
            this->energy = 1;
            this->trueCatStatus = false;
            this->catStatus = false;
        }
    }
    else if(this->catStatus)
    {
        this->energy -= this->decreaseCatEnergy;
        if(this->energy < 1)
        {
            this->energy = 1;
            this->catStatus = false;
        }
    }
}

void Tank::setEnergy(qint32 value)
{
    if(value > this->maxEnergy)
    {
        this->energy = this->maxEnergy;
    }
    else if(value < 1)
    {
        this->energy = 1;
    }
    else
    {
        this->energy = value;
    }
}
