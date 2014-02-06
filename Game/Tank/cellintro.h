#ifndef CELLINTRO_H
#define CELLINTRO_H

#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include "defination.h"
#include "textarea.h"
#include "cellular.h"

#define MaxRoleNumber 2

class CellIntro
{
public:
    CellIntro();
    ~CellIntro();
    void draw(QPainter *painter);
    qint32 mouseReleaseEvent();
    qint32 keyReleaseEvent(QKeyEvent *event);
    bool nextText();
private:
    qint32 currentRole;
    qint32 talkPosition;
    Cellular *cellular;
    bool *showRole;
    QImage *role[MaxRoleNumber];
    QImage *talkBox;
    TextArea *textArea;
};

#endif
