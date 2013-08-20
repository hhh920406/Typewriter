#include "WidgetBuffer2D.h"

struct stD3DVertex
{
    float x, y, z, w;
    unsigned long color;
    float tu, tv;
};

WidgetBuffer2D::WidgetBuffer2D(const float x, const float y,
                               const float width, const float height,
                               const float tu[4], const float tv[4])
{
    this->_vertexBuffer = NULL;
    stD3DVertex data[] =
    {
        {x + width, y, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), tu[1], tv[1]},
        {x + width, y + height, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), tu[3], tv[3]},
        {x, y, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), tu[0], tv[0]},
        {x, y + height, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), tu[2], tv[2]},
    };
    LPDIRECT3DDEVICE9 device = Framework::getInstance()->device();
    if (FAILED(device->CreateVertexBuffer(sizeof(data), 0,
                                          this->getFVF(),
                                          D3DPOOL_DEFAULT,
                                          &this->_vertexBuffer, NULL)))
    {
        return;
    }
    void *ptr;
    if (FAILED(this->_vertexBuffer->Lock(0, sizeof(data), (void**)&ptr, 0)))
    {
        return;
    }
    memcpy(ptr, data, sizeof(data));
    this->_vertexBuffer->Unlock();
}

WidgetBuffer2D::~WidgetBuffer2D()
{
    this->_vertexBuffer->Release();
}

unsigned int WidgetBuffer2D::vertexSize() const
{
    return sizeof(stD3DVertex);
}

int WidgetBuffer2D::getFVF() const
{
    return (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
}

LPDIRECT3DVERTEXBUFFER9 WidgetBuffer2D::vertexBuffer() const
{
    return this->_vertexBuffer;
}
