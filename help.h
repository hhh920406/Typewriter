#ifndef HELP_H
#define HELP_H

#include <QImage>
#include <QPainter>
#include "defination.h"

class Help
{
public:
    Help();
    ~Help();
    void draw(QPainter *painter);
private:
    QImage *helpImage;
};

#endif
