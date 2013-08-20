#include "Framework.h"
#include "Texture2D.h"
#include "WidgetBuffer2D.h"
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

void Widget::act()
{
}

void Widget::render()
{
    if (NULL != this->_vertexBuffer)
    {
        LPDIRECT3DDEVICE9 device = Framework::getInstance()->device();
        if (NULL != this->_texture)
        {
            device->SetTexture(0, this->_texture->texture());
        }
        device->SetStreamSource(0, this->_vertexBuffer->vertexBuffer(), 0, this->_vertexBuffer->vertexSize());
        device->SetFVF(this->_vertexBuffer->getFVF());
        device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    }
}
