#ifndef TESTSPRITE2D_H
#define TESTSPRITE2D_H

#include "Sprite2D.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "Rect2D.h"

class TestSprite2D : public Sprite2D
{
public:
    TestSprite2D(const float width, const float height);
    void setPosition(const float x, const float y);
    void setSpeed(const float x, const float y);
    void setBounding(const float left, const float right, const float top, const float bottom);
    void act();

private:
    Point2D _pos;
    Vector2D _speed;
    Rect2D _bounding;
};

#endif // TESTSPRITE2D_H
