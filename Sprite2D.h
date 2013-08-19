#ifndef SPRITE2D_H
#define SPRITE2D_H
/**
 * 基本的2D图形，以矩形中心作为中心。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "Framework.h"
#include "Vector2D.h"
#include "Rect2D.h"

class Sprite2D
{
public:
    Sprite2D(const float width, const float height, const float tu[4], const float tv[4]);
    virtual ~Sprite2D();
    Rect2D shape() const;
    unsigned int vertexSize() const;
    void render();
    void testMoveTo(float x, float y);
    void testRotateTo(float angle);
    void testScaleTo(float x, float y);

protected:
    bool createShape();

private:
    Rect2D _shape;
    Vector2D _move;
    Point2D _scale;
    float _rotate;
    float _tu[4];
    float _tv[4];
    LPDIRECT3DVERTEXBUFFER9 _vertexBuffer;
};

#endif // SPRITE2D_H
