#ifndef HEALTHSHOW_H
#define HEALTHSHOW_H

#include <QImage>
#include <QPainter>
#include "defination.h"

class HealthShow
{
public:
    HealthShow();
    qint32 show;
    bool stay;
    qint32 currentValue;
    qint32 maxValue;
    qint32 x;
    qint32 y;
    qint32 width;
    qint32 height;
    qint32 colorDivide;
    void setValue(qint32 value);
    void draw(QPainter *painter);
};

#endif
