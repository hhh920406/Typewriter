#ifndef MAINMENU_H
#define MAINMENU_H

#include <QPainter>
#include <QImage>
#include "defination.h"
#include "gamebutton.h"

class MainMenu
{
public:
    MainMenu();
    ~MainMenu();
    qint32 click(qint32 x, qint32 y);
    void draw(QPainter *painter);
    void setMousePosition(qint32 x, qint32 y);
    void moveToPosition();
private:
    QImage *background;
    GameButton *startButton;
    GameButton *achieveButton;
    GameButton *helpButton;
    GameButton *configButton;
    GameButton *exitButton;
    qint32 targetX[5];
};

#endif
