#ifndef WIDGETBUFFER2D_H
#define WIDGETBUFFER2D_H

#include "Point2D.h"
#include "Framework.h"
#include "VertexBuffer2D.h"

class WidgetBuffer2D
{
public:
    WidgetBuffer2D(const float x, const float y,
                   const float width, const float height,
                   const float tu[4], const float tv[4]);
    virtual ~WidgetBuffer2D();
    unsigned int vertexSize() const;
    int getFVF() const;
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer() const;

protected:
    LPDIRECT3DVERTEXBUFFER9 _vertexBuffer;
};

#endif