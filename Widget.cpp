#include "Widget.h"

Widget::Widget()
{
    this->_vertexBuffer = 0L;
    this->_texture = 0L;
}

Widget::~Widget()
{
}

void Widget::setVertexBuffer(WidgetBuffer2D* buffer)
{
    this->_vertexBuffer = buffer;
}

WidgetBuffer2D* Widget::vertexBuffer() const
{
    return this->_vertexBuffer;
}

void Widget::setTexture(Texture2D *texture)
{
    this->_texture = texture;
}

Texture2D* Widget::texture() const
{
    return this->_texture;
}
