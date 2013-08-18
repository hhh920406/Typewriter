#include "Point2D.h"

Point2D::Point2D()
{
    this->setPos(0.0f, 0.0f);
}

Point2D::Point2D(const Point2D &point)
{
    this->setPos(point.x(), point.y());
}

Point2D::Point2D(const float x, const float y)
{
    this->setPos(x, y);
}

Point2D::~Point2D()
{
}

float Point2D::x() const
{
    return this->_x;
}

float Point2D::y() const
{
    return this->_y;
}

void Point2D::setX(const float x)
{
    this->_x = x;
}

void Point2D::setY(const float y)
{
    this->_y = y;
}

void Point2D::setPos(const float x, const float y)
{
    this->_x = x;
    this->_y = y;
}
