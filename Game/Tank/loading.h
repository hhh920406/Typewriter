#ifndef LOADING_H
#define LOADING_H

#include <QPainter>
#include <QImage>
#include <QColor>
#include "defination.h"

class Loading
{
public:
    Loading();
    ~Loading();
    bool draw(qint32 &time, QPainter *painter);
private:
    QImage *image;
    QImage *tempImage;
    QImage *background;
    QImage *light;
    bool maxAlpha;
    qint32 stayTime;
    qint32 lightTime;
};

#endif
