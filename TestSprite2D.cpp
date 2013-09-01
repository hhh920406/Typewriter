#include <cmath>
#include "TestSprite2D.h"
#include "Framework.h"
#include "VertexBuffer2DController.h"
#include "Sprite2DController.h"

TestSprite2D::TestSprite2D(const float width, const float height) : Sprite2D(width, height)
{
    this->_birthCount = 0;
    this->_bounding.setPos(-100.0f, -100.0f);
    this->_bounding.setSize(200.0f, 200.0f);
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

void TestSprite2D::act(int milliseconds)
{
    if (--this->_birthCount < 0)
    {
        this->move(milliseconds);
        if (this->_translate.x() < this->_bounding.x() - halfWidth() ||
            this->_translate.x() > this->_bounding.x() + this->_bounding.width() + halfWidth() ||
            this->_translate.y() < this->_bounding.y() - halfHeight() ||
            this->_translate.y() > this->_bounding.y() + this->_bounding.height() + halfHeight())
        {
            this->deleteLater();
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
