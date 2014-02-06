#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QImage>
#include <QPainter>
#include "defination.h"
#include "healthshow.h"

class GameObject
{
public:
    GameObject();
    ~GameObject();
    qint32 type;
    bool destroyable;
    bool movable;
    bool visiable;
    bool walkable;
    bool enabled;
    qint32 currentLife;
    qint32 maxLife;
    qint32 x;
    qint32 y;
    qint32 width;
    qint32 height;
    void setLife(qint32 value);
    void setMaxLife(qint32 value);
    void setPosition(qint32 x, qint32 y);
    void setSize(qint32 width, qint32 height);
    bool hitTest(qint32 x, qint32 y, qint32 width, qint32 height);
    bool inArea(qint32 x, qint32 y);
    void draw(QPainter *painter, QImage *image);
    HealthShow *healthShow;
};

#endif
