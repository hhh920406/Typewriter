#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <QImage>
#include <QPainter>
#include "gamewidget.h"

class TextArea : public GameWidget
{
public:
    TextArea();
    QString text;
    void draw(QPainter *painter);
    void setText(QString text);
    void showAll();
    bool textAll();
private:
    qint32 time;
    qint32 textPosition;
};

#endif
