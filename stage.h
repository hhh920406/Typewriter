#ifndef STAGE_H
#define STAGE_H

#include <QImage>
#include <QPainter>
#include "defination.h"
#include "integer.h"

class Stage
{
public:
    Stage();
    ~Stage();
    bool draw(QPainter *painter, qint32 value, qint32 &time);
private:
    QImage *image;
    Integer *currentStage;
};

#endif
