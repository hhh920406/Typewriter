#ifndef FRACTION_H
#define FRACTION_H

#include <QImage>
#include <QPainter>
#include "defination.h"
#include "integer.h"

class Fraction
{
public:
    Fraction();
    ~Fraction();
    void setIntegerLength(qint32 value);
    void setValue(qint32 value);
    void setMaxValue(qint32 value);
    void draw(QPainter *painter, qint32 x, qint32 y);
private:
    Integer *integerA;
    Integer *integerB;
    QImage *semicolon;
    qint32 integerLength;
    qint32 value;
    qint32 maxValue;
};

#endif
