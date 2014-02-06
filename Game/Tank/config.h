#ifndef CONFIG_H
#define CONFIG_H

#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFile>
#include <QDataStream>
#include "defination.h"
#include "gamekeyedit.h"
#include "gamebutton.h"

#define GameEditNumber 8

class Config
{
public:
    Config();
    ~Config();
    GameKeyEdit *gameKeyEdit[GameEditNumber];
    qint32 mouseDown(QMouseEvent *event);
    void mouseMove(QMouseEvent *event);
    void keyDown(QKeyEvent *event);
    void draw(QPainter *painter);
    void readInfo();
    void writeInfo();
private:
    QImage *image;
    GameButton *okButton;
    GameButton *cancelButton;
};

#endif
