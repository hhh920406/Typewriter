#ifndef PAUSE_H
#define PAUSE_H

#include <QImage>
#include <QPainter>
#include "defination.h"

class Pause
{
public:
    Pause();
    ~Pause();
    void draw(QPainter *painter);
    qint32 lastScene;
private:
    QImage *image;
};

#endif
