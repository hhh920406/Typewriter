#include "TestSprite2D.h"

TestSprite2D::TestSprite2D(const float width, const float height) : Sprite2D(width, height)
{
    this->_pos.setPos(0.0f, 0.0f);
    this->_speed.setPos(0.0f, 0.0f);
    this->_bounding.setPos(-100.0f, -100.0f);
    this->_bounding.setSize(200.0f, 200.0f);
}

void TestSprite2D::setPosition(const float x, const float y)
{
    this->_pos.setPos(x, y);
}

void TestSprite2D::setSpeed(const float x, const float y)
{
    this->_speed.setPos(x, y);
}

void TestSprite2D::setBounding(const float left, const float right, const float top, const float bottom)
{
    this->_bounding.setPos(left, top);
    this->_bounding.setSize(right - left, bottom - top);
}

void TestSprite2D::act()
{
    this->_pos = this->_pos + this->_speed;
    if (this->_pos.x() < this->_bounding.x() ||
        this->_pos.x() > this->_bounding.x() + this->_bounding.width())
    {
        this->_speed.setX(-this->_speed.x());
    }
    if (this->_pos.y() < this->_bounding.y() ||
        this->_pos.y() > this->_bounding.y() + this->_bounding.height())
    {
        this->_speed.setY(-this->_speed.y());
    }
    this->translateTo(this->_pos.x(), this->_pos.y());
}
