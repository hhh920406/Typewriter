#include <cmath>
#include "TestSprite2D.h"

TestSprite2D::TestSprite2D(const float width, const float height) : Sprite2D(width, height)
{
    this->_birthCount = 0;
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

void TestSprite2D::setBirth(int num)
{
    _kickTime = 0;
    this->_birthCount = num;
}

void TestSprite2D::act()
{
    --this->_birthCount;
    this->_rotate += 0.03f;
    if (fabs(this->_speed.x()) < 20.0f && fabs(this->_speed.y()) < 20.0f)
    {
        this->_speed.setX(this->_speed.x() * 1.0005);
        this->_speed.setY(this->_speed.y() * 1.0005);
    }
    if (this->_birthCount > 0)
    {
        this->translateTo(this->_pos.x(), this->_pos.y());
    }
    else
    {
        this->_pos = this->_pos + this->_speed;
        this->translateTo(this->_pos.x(), this->_pos.y());
        if (this->_birthCount <= -100000)
        {
            this->_pos.setPos(960 / 2, 720 / 2);
            this->_birthCount += 100000;
        }
        this->_pos = this->_pos + this->_speed;
        if (this->_kickTime >= 0)
        {
            if (this->_pos.x() < this->_bounding.x() + halfWidth())
            {
                this->_pos.setX((this->_bounding.x() + halfWidth()) * 2 - this->_pos.x());
                this->_speed.setX(-this->_speed.x());
                --_kickTime;
            }
            else if (this->_pos.x() > this->_bounding.x() + this->_bounding.width() - halfWidth())
            {
                this->_pos.setX((this->_bounding.x() + this->_bounding.width() - halfWidth()) * 2 - this->_pos.x());
                this->_speed.setX(-this->_speed.x());
                --_kickTime;
            }
            else if (this->_pos.y() < this->_bounding.y() + halfHeight())
            {
                this->_pos.setY((this->_bounding.y() + halfHeight()) * 2 - this->_pos.y());
                this->_speed.setY(-this->_speed.y());
                --_kickTime;
            }
            else if (this->_pos.y() > this->_bounding.y() + this->_bounding.height() - halfHeight())
            {
                this->_pos.setY((this->_bounding.y() + this->_bounding.height() - halfHeight()) * 2 - this->_pos.y());
                this->_speed.setY(-this->_speed.y());
                --_kickTime;
            }
        }
        if (this->_kickTime <= 0)
        {
            if (this->_pos.x() < this->_bounding.x() - halfWidth() ||
                this->_pos.x() > this->_bounding.x() + this->_bounding.width() + halfWidth() ||
                this->_pos.y() < this->_bounding.y() - halfHeight() ||
                this->_pos.y() > this->_bounding.y() + this->_bounding.height() + halfHeight())
            {
                this->deleteLater();
            }
        }
    }
}

void TestSprite2D::render()
{
    if (this->_birthCount > -1000 && this->_birthCount <= 0)
    {
        Sprite2D::render();
    }
}
