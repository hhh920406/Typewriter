#ifndef SPRITE2D_H
#define SPRITE2D_H
/**
 * 基本的2D图形，以矩形中心作为中心。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "d3d9.h"
#include "Rect2D.h"

class Sprite2D
{
public:
    Sprite2D(const float width = 0, const float height = 0);
    virtual ~Sprite2D();
    Rect2D shape() const;
    Point2D centerPos() const;
    unsigned int vertexSize() const;
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer() const;

protected:
    bool createShape();

private:
    Rect2D _shape;
    Point2D _centerPos;
    LPDIRECT3DVERTEXBUFFER9 _vertexBuffer;
    struct stD3DVertex
    {
        float x, y, z, rhw;
        unsigned long color;
    };
};

#endif // SPRITE2D_H
