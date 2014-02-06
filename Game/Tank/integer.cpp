#include "integer.h"

Integer::Integer()
{
    this->number = new Number();
    this->fillZero = true;
    this->align = Defination::ALIGN_LEFT;
    this->value = 0;
    this->integerLength = 8;
}

Integer::~Integer()
{
    delete number;
}

void Integer::setFillZero(bool value)
{
    this->fillZero = value;
}

void Integer::setAlign(qint32 value)
{
    this->align = value;
}

void Integer::setIntegerLength(qint32 value)
{
    this->integerLength = value;
}

void Integer::setValue(qint32 value)
{
    this->value = value;
}

qint32 Integer::getCurrentLength()
{
    if(value==0)
    {
        return 1;
    }
    qint32 count = 0;
    qint32 temp = value;
    while(temp>0)
    {
        count++;
        temp/=10;
    }
    return count;
}

void Integer::draw(QPainter *painter, qint32 x, qint32 y)
{
    if(this->align == Defination::ALIGN_LEFT)
    {
        qint32 temp = value;
        for(qint32 i = getCurrentLength()-1;i>=0;i--)
        {
            number->draw(painter, x + i * 20, y, temp % 10);
            temp /= 10;
        }
    }
    else
    {
        qint32 temp = value;
        for(qint32 i = integerLength-1; i>=0; i--)
        {
            number->draw(painter, x+ i * 20, y, temp % 10);
            temp /= 10;
            if(temp == 0 && !fillZero)
            {
                break;
            }
        }
    }
}
