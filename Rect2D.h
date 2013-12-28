#ifndef RECT2D_H
#define RECT2D_H

#include "Point2D.h"

class Rect2D : public Point2D
{
public:
    Rect2D();
    Rect2D(const Point2D pos, const Point2D size);
    Rect2D(const float x, const float y, const float width, const float height);
    virtual ~Rect2D();
    float width() const;
    float height() const;
    void setWidth(const float width);
    void setHeight(const float height);
    void setSize(const Point2D &size);
    void setSize(const float width, const float height);

protected:
    float _width;
    float _height;
};

#endif
