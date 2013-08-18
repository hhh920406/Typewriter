#include <cstring>
#include <windows.h>
#include "Sprite2D.h"
#include "Framework.h"

struct stD3DVertex
{
    float x, y, z;
    unsigned long color;
};

Sprite2D::Sprite2D(const float width, const float height)
{
    this->_vertexBuffer = NULL;
    this->_shape.setPos(- width * 0.5f, - height * 0.5f);
    this->_shape.setSize(width, height);
    this->_move.setPos(0.0f, 0.0f);
    this->_scale.setPos(1.0f, 1.0f);
    this->_rotate = 0.0f;
    this->createShape();
}

Sprite2D::~Sprite2D()
{
}

Rect2D Sprite2D::shape() const
{
    return this->_shape;
}

bool Sprite2D::createShape()
{
    stD3DVertex data[] =
    {
        {this->_shape.width(), this->_shape.y(), 0.5f, D3DCOLOR_XRGB(255, 255, 255),},
        {this->_shape.width(), this->_shape.height(), 0.5f, D3DCOLOR_XRGB(255, 255, 255),},
        {this->_shape.x(), this->_shape.y(), 0.5f, D3DCOLOR_XRGB(255, 255, 255),},
        {this->_shape.x(), this->_shape.height(), 0.5f, D3DCOLOR_XRGB(255, 255, 255),},
    };
    LPDIRECT3DDEVICE9 device = Framework::getInstance()->device();
    if (FAILED(device->CreateVertexBuffer(sizeof(data), 0,
                                          D3DFVF_XYZ | D3DFVF_DIFFUSE,
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

void Sprite2D::render()
{
    LPDIRECT3DDEVICE9 device = Framework::getInstance()->device();
    D3DXMATRIX worldMatrix;
    D3DXMATRIX scale;
    D3DXMATRIX rotate;
    D3DXMATRIX translation;
    D3DXMatrixScaling(&scale, this->_scale.x(), this->_scale.y(), 1.0f);
    D3DXMatrixRotationZ(&rotate, this->_rotate);
    D3DXMatrixTranslation(&translation, this->_move.x(), this->_move.y(), 0.0f);
    D3DXMatrixMultiply(&worldMatrix, &scale, &rotate);
    D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translation);
    device->SetTransform(D3DTS_WORLD, &worldMatrix);
    device->SetStreamSource(0, this->_vertexBuffer, 0, sizeof(stD3DVertex));
    device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
    device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void Sprite2D::testRotateTo(float angle)
{
    this->_rotate = angle;
}

void Sprite2D::testMoveTo(float x, float y)
{
    this->_move.setPos(x, y);
}
