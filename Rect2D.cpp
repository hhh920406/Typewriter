#include "Rect2D.h"

Rect2D::Rect2D() : Point2D()
{
    this->setSize(0.0f, 0.0f);
}

Rect2D::Rect2D(const Point2D pos, const Point2D size) : Point2D(pos)
{
    this->setSize(size);
}

Rect2D::Rect2D(const float x, const float y, const float width, const float height) : Point2D(x, y)
{
    this->setSize(width, height);
}

Rect2D::~Rect2D()
{
}

float Rect2D::width() const
{
    return this->_width;
}

float Rect2D::height() const
{
    return this->_height;
}

void Rect2D::setWidth(const float width)
{
    this->_width = width;
}

void Rect2D::setHeight(const float height)
{
    this->_height = height;
}

void Rect2D::setSize(const Point2D &size)
{
    this->setSize(size.x(), size.y());
}

void Rect2D::setSize(const float width, const float height)
{
    this->_width = width;
    this->_height = height;
}
