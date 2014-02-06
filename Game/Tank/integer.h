#ifndef INTEGER_H
#define INTEGER_H

#include <QImage>
#include <QPainter>
#include "number.h"
#include "defination.h"

class Integer
{
public:
    Integer();
    ~Integer();
    void setFillZero(bool value);
    void setAlign(qint32 value);
    void setIntegerLength(qint32 value);
    void setValue(qint32 value);
    void draw(QPainter *painter, qint32 x, qint32 y);
private:
    Number *number;
    bool fillZero;
    qint32 align;
    qint32 integerLength;
    qint32 value;
    qint32 getCurrentLength();
};

#endif
