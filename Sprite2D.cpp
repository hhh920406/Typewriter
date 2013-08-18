#include <cstring>
#include <windows.h>
#include "Sprite2D.h"
#include "Framework.h"

Sprite2D::Sprite2D(const float width, const float height)
{
    this->_shape.setPos(- width * 0.5f, - height * 0.5f);
    this->_shape.setSize(width, height);
    this->_centerPos.setPos(0, 0);
    this->createShape();
}

Sprite2D::~Sprite2D()
{
}

Rect2D Sprite2D::shape() const
{
    return this->_shape;
}

Point2D Sprite2D::centerPos() const
{
    return this->_centerPos;
}

LPDIRECT3DVERTEXBUFFER9 Sprite2D::vertexBuffer() const
{
    return this->_vertexBuffer;
}

bool Sprite2D::createShape()
{
    struct stD3DVertex
    {
        float x, y, z, rhw;
        unsigned long color;
    };
    stD3DVertex data[] =
    {
        {this->_shape.x(), this->_shape.y(), 0.5f, 1, D3DCOLOR_XRGB(255, 255, 255),},
        {this->_shape.x(), this->_shape.height(), 0.5f, 1, D3DCOLOR_XRGB(255, 255, 255),},
        {this->_shape.width(), this->_shape.y(), 0.5f, 1, D3DCOLOR_XRGB(255, 255, 255),},
        {this->_shape.width(), this->_shape.height(), 0.5f, 1, D3DCOLOR_XRGB(255, 255, 255),},
    };
    LPDIRECT3DDEVICE9 device = Framework::getInstance()->device();
    if (FAILED(device->CreateVertexBuffer(sizeof(data), 0,
                                          D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
                                          D3DPOOL_DEFAULT,
                                          &this->_vertexBuffer, NULL)))
    {
        return false;
    }
    void *ptr;
    if (FAILED(this->_vertexBuffer->Lock(0, sizeof(data), (void**)&ptr, 0)))
    {
        return false;
    }
    memcpy(ptr, data, sizeof(data));
    this->_vertexBuffer->Unlock();
    return true;
}
