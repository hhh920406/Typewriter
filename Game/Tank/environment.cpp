#include "environment.h"

Environment::Environment()
{
    this->river = new QImage(":/images/river.png");
    this->steel = new QImage(":/images/steel.png");
    this->brick = new QImage(":/images/brick.png");
    this->catStone = new QImage(":/images/catStone.png");
    for(qint32 i=0;i<MaxItemNumber;i++)
    {
        this->gameObject[i] = new GameObject();
        this->gameObject[i]->setSize(40,40);
        this->gameObject[i]->maxLife = 100;
        this->gameObject[i]->currentLife = 100;
        this->gameObject[i]->type = Defination::TYPE_NULL;
    }
    this->itemNumber = 0;
}

Environment::~Environment()
{
    delete this->river;
    delete this->steel;
    delete this->brick;
    delete this->catStone;
    for(qint32 i=0;i<MaxItemNumber;i++)
    {
        delete this->gameObject[i];
    }
}

void Environment::draw(QPainter *painter)
{
    for(qint32 i=0;i<this->itemNumber;i++)
    {
        QRect *rect = new QRect(gameObject[i]->x, gameObject[i]->y, gameObject[i]->width, gameObject[i]->height);
       switch(this->gameObject[i]->type)
       {
       case Defination::TYPE_BRICK:
           painter->drawImage(*rect, *brick);
           break;
       case Defination::TYPE_RIVER:
           painter->drawImage(*rect, *river);
           break;
        case Defination::TYPE_STEEL:
           painter->drawImage(*rect, *steel);
           break;
        case Defination::TYPE_CATSTONE:
           painter->drawImage(*rect, *catStone);
           break;
        }
        delete rect;
    }
    for(qint32 i=0;i<this->itemNumber;i++)
    {
        this->gameObject[i]->healthShow->draw(painter);
    }
}

bool Environment::hitTestType(qint32 x, qint32 y, qint32 width, qint32 height, qint32 type)
{
    if(type == Defination::TYPE_BULLET)
    {
        return this->hitTestBullet(x,y,width,height);
    }
    else
    {
        return this->hitTestMove(x,y,width,height);
    }
}

bool Environment::hitTestMove(qint32 x, qint32 y, qint32 width, qint32 height, bool cat, bool trueCat)
{
    for(qint32 i=0;i<this->itemNumber;i++)
    {
        switch(gameObject[i]->type)
        {
        case Defination::TYPE_RIVER:
        case Defination::TYPE_BRICK:
        case Defination::TYPE_STEEL:
        case Defination::TYPE_CATSTONE:
            if(gameObject[i]->hitTest(x,y,width,height))
            {
                if(cat)
                {
                    achieve->destroyUnit ++;
                    this->deleteItem(i);
                }
                return true;
            }
        }
    }
    return false;
}

bool Environment::hitTestBullet(qint32 x, qint32 y, qint32 width, qint32 height)
{
    for(qint32 i=0;i<this->itemNumber;i++)
    {
        switch(gameObject[i]->type)
        {
        case Defination::TYPE_BRICK:
        case Defination::TYPE_STEEL:
        case Defination::TYPE_CATSTONE:
            if(gameObject[i]->hitTest(x,y,width,height))
            {
                gameObject[i]->setLife(gameObject[i]->currentLife - 20);
                if(gameObject[i]->currentLife <= 0)
                {
                    this->deleteItem(i);
                    achieve->destroyUnit ++;
                }
                return true;
            }
        }
    }
    return false;
}

void Environment::initialEnvironment()
{
    this->itemNumber = 0;
}

void Environment::initialBrick(GameObject *object)
{
    object->type = Defination::TYPE_BRICK;
    object->setMaxLife(100);
    object->setLife(100);
    object->healthShow->show = 0;
}

void Environment::initialRiver(GameObject *object)
{
    object->type = Defination::TYPE_RIVER;
    object->setMaxLife(500);
    object->setLife(500);
    object->healthShow->show = 0;
}

void Environment::initialSteel(GameObject *object)
{
    object->type = Defination::TYPE_STEEL;
    object->setMaxLife(5000);
    object->setLife(5000);
    object->healthShow->show = 0;
}

void Environment::initialCatStone(GameObject *object)
{
    object->type = Defination::TYPE_CATSTONE;
    object->setMaxLife(100);
    object->setLife(100);
    object->healthShow->show = 0;
}

void Environment::bindAchieve(Achieve *achieve)
{
    this->achieve = achieve;
}

void Environment::addItem(qint32 type, qint32 i, qint32 j)
{
    if(this->itemNumber < MaxItemNumber)
    {
        this->gameObject[this->itemNumber]->setPosition(60 + 40 * j, 60 + 40 * i);
        switch(type)
        {
        case Defination::TYPE_BRICK:
            this->initialBrick(this->gameObject[this->itemNumber]);
            break;
        case Defination::TYPE_RIVER:
            this->initialRiver(this->gameObject[this->itemNumber]);
            break;
        case Defination::TYPE_STEEL:
            this->initialSteel(this->gameObject[this->itemNumber]);
            break;
        case Defination::TYPE_CATSTONE:
            this->initialCatStone(this->gameObject[this->itemNumber]);
            break;
        }
        this->itemNumber ++;
    }
}

void Environment::deleteItem(qint32 id)
{
    this->itemNumber --;
    this->gameObject[id]->type = this->gameObject[this->itemNumber]->type;
    this->gameObject[id]->setPosition(this->gameObject[this->itemNumber]->x, this->gameObject[this->itemNumber]->y);
    this->gameObject[id]->setLife(this->gameObject[this->itemNumber]->currentLife);
    this->gameObject[id]->setMaxLife(this->gameObject[this->itemNumber]->maxLife);
    this->gameObject[id]->healthShow->show = 0;

}

void Environment::initialStage(qint32 stage)
{
    this->initialEnvironment();
    this->addItem(Defination::TYPE_CATSTONE, 11, 5);
    switch(stage)
    {
    case 1:
        for(qint32 i=1;i<11;i++)
        {
            this->addItem(Defination::TYPE_BRICK, 1,i);
            this->addItem(Defination::TYPE_BRICK, 10, i);
        }
        for(qint32 i=2;i<10;i++)
        {
            this->addItem(Defination::TYPE_BRICK, i, 11-i);
        }
        break;
    default:
        for(qint32 i=1;i<11;i++)
        {
            for(qint32 j=1;j<11;j++)
            {
                if(rand()&1)
                {
                    switch(rand()%3)
                    {
                    case 0:
                        this->addItem(Defination::TYPE_BRICK, i, j);
                        break;
                    case 1:
                        this->addItem(Defination::TYPE_RIVER, i, j);
                        break;
                    case 2:
                        this->addItem(Defination::TYPE_STEEL, i, j);
                        break;
                    }
                }
            }
        }
    }
}

bool Environment::catStoneExist()
{
    return this->gameObject[0]->type == Defination::TYPE_CATSTONE && this->itemNumber;
}

void Environment::trueCatPower()
{
    for(qint32 i=0;i<this->itemNumber;i++)
    {
        if(gameObject[i]->type != Defination::TYPE_NULL && gameObject[i]->type != Defination::TYPE_CATSTONE)
         {
            gameObject[i]->setLife(gameObject[i]->currentLife - 2);
            if(this->gameObject[i]->currentLife <= 0)
            {
                this->deleteItem(i);
                achieve->destroyUnit ++;
            }
        }
    }
}
