#ifndef ABOUTUS_H
#define ABOUTUS_H

#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFont>
#include <QString>
#include "defination.h"
#include "textarea.h"

#define MaxRoleNumber 2

class AboutUs
{
public:
    AboutUs();
    ~AboutUs();
    void draw(QPainter *painter);
    qint32 mouseReleaseEvent();
    qint32 keyReleaseEvent(QKeyEvent *event);
    bool nextText();
private:
    qint32 currentRole;
    qint32 talkPosition;
    bool *showRole;
    QImage *background;
    QImage *role[MaxRoleNumber];
    QImage *talkBox;
    TextArea *textArea;
};

#endif
