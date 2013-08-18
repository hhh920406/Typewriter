#include "Vector2D.h"

Vector2D::Vector2D() : Point2D()
{
}

Vector2D::Vector2D(const float x, const float y) : Point2D(x, y)
{
}

Vector2D::~Vector2D()
{
}

/**
 * 点加上一个向量，相当于点的位移。
 */
const Point2D operator +(const Point2D &a, const Vector2D &b)
{
    Point2D c;
    c.setX(a.x() + b.x());
    c.setY(a.y() + b.y());
    return c;
}

/**
 * 点的反向位移。
 */
const Point2D operator -(const Point2D &a, const Vector2D &b)
{
    Point2D c;
    c.setX(a.x() - b.x());
    c.setY(a.y() - b.y());
    return c;
}

const Vector2D operator +(const Vector2D &a, const Vector2D &b)
{
    Vector2D c;
    c.setX(a.x() + b.x());
    c.setY(a.y() + b.y());
    return c;
}

const Vector2D operator -(const Vector2D &a, const Vector2D &b)
{
    Vector2D c;
    c.setX(a.x() - b.x());
    c.setY(a.y() - b.y());
    return c;
}

/**
 * 点乘积。
 */
const double operator *(const Vector2D &a, const Vector2D &b)
{
    return a.x() * b.x() + a.y() * b.y();
}

/**
 * 叉乘积。
 */
const double operator ^(const Vector2D &a, const Vector2D &b)
{
    return a.x() * b.y() - a.y() * b.x();
}
