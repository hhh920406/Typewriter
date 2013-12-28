#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "Point2D.h"

class Vector2D : public Point2D
{
public:
    Vector2D();
    Vector2D(const float x, const float y);
    virtual ~Vector2D();

    friend const Point2D operator +(const Point2D &a, const Vector2D &b);
    friend const Point2D operator -(const Point2D &a, const Vector2D &b);

    friend const Vector2D operator +(const Vector2D &a, const Vector2D &b);
    friend const Vector2D operator -(const Vector2D &a, const Vector2D &b);
    friend const double operator *(const Vector2D &a, const Vector2D &b);
    friend const double operator ^(const Vector2D &a, const Vector2D &b);

    friend const Vector2D operator *(const Vector2D &a, const double b);
    friend const Vector2D operator /(const Vector2D &a, const double b);
};

#endif
