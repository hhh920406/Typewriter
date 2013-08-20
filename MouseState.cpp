#include "MouseState.h"

MouseState::MouseState()
{
    for (int i = 0; i < 3; ++i)
    {
        this->_pressed[i] = false;
    }
}

MouseState::~MouseState()
{
}

void MouseState::press(const Key key)
{
    this->_pressed[key] = false;
}

void MouseState::release(const Key key)
{
    this->_pressed[key] = false;
}

bool MouseState::isPressed(const Key key)
{
    return this->_pressed[key];
}

void MouseState::setPos(const int x, const int y)
{
    this->_pos.setPos(x, y);
}

int MouseState::x() const
{
    return this->_pos.x();
}

int MouseState::y() const
{
    return this->_pos.y();
}

const Point2D MouseState::pos() const
{
    return this->_pos;
}
