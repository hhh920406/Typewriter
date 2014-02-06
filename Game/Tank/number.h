#ifndef NUMBER_H
#define NUMBER_H

#include <QImage>
#include <QPainter>

class Number
{
public:
    Number();
    ~Number();
    void draw(QPainter *painter, qint32 x, qint32 y, qint32 number);
private:
    QImage *numImage[10];
};

#endif
