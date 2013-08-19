#include "VertexBuffer2D.h"

struct stD3DVertex
{
    float x, y, z;
    unsigned long color;
    float tu, tv;
};

#define D3DFVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

VertexBuffer2D::VertexBuffer2D(const float width, const float height)
{
    this->_vertexBuffer = NULL;
    this->_shape.setPos(width * 0.5f, height * 0.5f);
    this->_tu[0] = 0.0f;
    this->_tv[0] = 0.0f;
    this->_tu[1] = 0.0f;
    this->_tv[1] = 1.0f;
    this->_tu[2] = 1.0f;
    this->_tv[2] = 0.0f;
    this->_tu[3] = 1.0f;
    this->_tv[3] = 1.0f;
    this->createShape();
}

VertexBuffer2D::VertexBuffer2D(const float width, const float height, const float tu[4], const float tv[4])
{
    this->_vertexBuffer = NULL;
    this->_shape.setPos(width * 0.5f, height * 0.5f);
    for (int i = 0; i < 4; ++i)
    {
        this->_tu[i] = tu[i];
        this->_tv[i] = tv[i];
    }
    this->createShape();
}

VertexBuffer2D::~VertexBuffer2D()
{
    if (NULL != this->_vertexBuffer)
    {
        this->_vertexBuffer->Release();
    }
}

LPDIRECT3DVERTEXBUFFER9 VertexBuffer2D::vertexBuffer() const
{
    return this->_vertexBuffer;
}

float VertexBuffer2D::width() const
{
    return this->_shape.x() * 2.0f;
}

float VertexBuffer2D::height() const
{
    return this->_shape.y() * 2.0f;
}

float VertexBuffer2D::halfWidth() const
{
    return this->_shape.x();
}

float VertexBuffer2D::halfHeight() const
{
    return this->_shape.y();
}

unsigned int VertexBuffer2D::vertexSize() const
{
    return sizeof(stD3DVertex);
}

int VertexBuffer2D::getFVF() const
{
    return D3DFVF_VERTEX;
}

bool VertexBuffer2D::createShape()
{
    stD3DVertex data[] =
    {
        {this->_shape.x(), -this->_shape.y(), 0.5f, D3DCOLOR_XRGB(255, 255, 255), this->_tu[2], this->_tv[3]},
        {this->_shape.x(), this->_shape.y(), 0.5f, D3DCOLOR_XRGB(255, 255, 255), this->_tu[3], this->_tv[3]},
        {-this->_shape.x(), -this->_shape.y(), 0.5f, D3DCOLOR_XRGB(255, 255, 255), this->_tu[0], this->_tv[0]},
        {-this->_shape.x(), this->_shape.y(), 0.5f, D3DCOLOR_XRGB(255, 255, 255), this->_tu[1], this->_tv[1]},
    };
    LPDIRECT3DDEVICE9 device = Framework::getInstance()->device();
    if (FAILED(device->CreateVertexBuffer(sizeof(data), 0,
                                          D3DFVF_VERTEX,
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
