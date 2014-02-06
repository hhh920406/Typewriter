#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QImage>
#include <QPainter>
#include "gamewidget.h"

class GameButton : public GameWidget
{
public:
    GameButton(const char* imagePath);
    GameButton(const char* imagePath, qint32 x, qint32 y);
    GameButton(const char* imagePath, qint32 x, qint32 y, qint32 width, qint32 height);
    ~GameButton();
    void setImage(const char* imagePath);
    void draw(QPainter *painter);
    bool inArea(qint32 x, qint32 y);
    void setMousePosition(qint32 x, qint32 y);
    bool enabled;
private:
    QImage *buttonImage;
    qint32 mouseX;
    qint32 mouseY;
    qint32 targetX;
};

#endif
