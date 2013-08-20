#ifndef TESTSPRITE2D_H
#define TESTSPRITE2D_H
/**
 * 测试用的图形，在撞击两次边界后要求销毁自身。
 * @author ZHG <CyberZHG@gmail.com>
 */
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
    void setBirth(int num);
    void act();
    void render();

private:
    Point2D _pos;
    Vector2D _speed;
    Rect2D _bounding;
    int _birthCount;
    int _kickTime;
    float _a;
    float _ax, _ay;
};

#endif // TESTSPRITE2D_H
