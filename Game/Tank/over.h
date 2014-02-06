#ifndef OVER_H
#define OVER_H

#include <QImage>
#include <QPainter>
#include "defination.h"

class Over
{
public:
    Over();
    ~Over();
    bool draw(QPainter *painter, qint32 &time);
private:
    QImage *image;
};

#endif
