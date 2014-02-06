#include "fraction.h"

Fraction::Fraction()
{
    integerA = new Integer();
    integerA->setAlign(Defination::ALIGN_RIGHT);
    integerA->setFillZero(true);
    integerA->setIntegerLength(3);
    integerA->setValue(0);
    integerB = new Integer();
    integerB->setAlign(Defination::ALIGN_RIGHT);
    integerB->setFillZero(true);
    integerB->setIntegerLength(3);
    integerB->setValue(0);
    semicolon = new QImage(":/images/semicolon.png");
}

Fraction::~Fraction()
{
    delete integerA;
    delete integerB;
    delete semicolon;
}

void Fraction::setIntegerLength(qint32 value)
{
    this->integerLength = value;
    integerA->setIntegerLength(value);
    integerB->setIntegerLength(value);
}

void Fraction::setValue(qint32 value)
{
    this->value = value;
    integerA->setValue(value);
}

void Fraction::setMaxValue(qint32 value)
{
    this->maxValue = value;
    integerB->setValue(value);
}

void Fraction::draw(QPainter *painter, qint32 x, qint32 y)
{
    integerA->draw(painter,x,y);
    painter->drawImage(x + 20 * integerLength,y,*semicolon);
    integerB->draw(painter,x + 20 * (integerLength + 1),y);
}
