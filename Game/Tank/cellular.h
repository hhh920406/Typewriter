#ifndef CELLULAR_H
#define CELLULAR_H

#include <QPainter>
#include <QColor>
#include <QMouseEvent>
#include <cmath>
#include <stdio.h>

class Cellular
{
public:
    Cellular(qint32 widthNumber, qint32 heightNumber);
    ~Cellular();
    void setPosition(qint32 x, qint32 y);
    void setSide(qint32 side);
    void draw(QPainter *painter);
    void nextGeneration();
    void opposite(qint32 x, qint32 y);
    void clear();
    void randomInitial();
    void linearInitial();
    qint32 x;
    qint32 y;
    qint32 side;
    QColor *liveColor;
    QColor *deadColor;
    QColor *lineColor;
    bool showGenerationNumber;
private:
    bool **cellArea;
    qint32 **cellCount;
    qint32 widthNumber;
    qint32 heightNumber;
    qint32 generationNumber;
};

#endif
