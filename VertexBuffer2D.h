#ifndef VERTEXBUFFER2D_H
#define VERTEXBUFFER2D_H
/**
 * 顶点缓存。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "Point2D.h"
#include "Framework.h"

class VertexBuffer2D
{
public:
    VertexBuffer2D(const float width, const float height);
    VertexBuffer2D(const float width, const float height, const float tu[4], const float tv[4]);
    virtual ~VertexBuffer2D();
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer() const;
    float width() const;
    float height() const;
    float halfWidth() const;
    float halfHeight() const;
    virtual unsigned int vertexSize() const;
    virtual int getFVF() const;

protected:
    Point2D _shape;
    float _tu[4];
    float _tv[4];
    LPDIRECT3DVERTEXBUFFER9 _vertexBuffer;

    virtual bool createShape();
};

#endif // VERTEXBUFFER2D_H
