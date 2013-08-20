#ifndef WIDGETBUFFER2D_H
#define WIDGETBUFFER2D_H
/**
 * 不可进行几何变换的顶点缓存。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "Point2D.h"
#include "Framework.h"
#include "VertexBuffer2D.h"

class WidgetBuffer2D : public VertexBuffer2D
{
public:
    WidgetBuffer2D(const float width, const float height);
    WidgetBuffer2D(const float width, const float height, const float tu[4], const float tv[4]);
    virtual unsigned int vertexSize() const;
    virtual int getFVF() const;

protected:
    virtual bool createShape();
};

#endif // WIDGETBUFFER2D_H
