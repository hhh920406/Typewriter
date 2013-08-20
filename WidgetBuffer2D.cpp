#include "WidgetBuffer2D.h"

struct stD3DVertex
{
    float x, y, z, w;
    unsigned long color;
    float tu, tv;
};

WidgetBuffer2D::WidgetBuffer2D(const float width, const float height) : VertexBuffer2D(width, height)
{
}

WidgetBuffer2D::WidgetBuffer2D(const float width, const float height, const float tu[4], const float tv[4]) :
    VertexBuffer2D(width, height, tu, tv)
{

}

unsigned int WidgetBuffer2D::vertexSize() const
{
    return sizeof(stD3DVertex);
}

int WidgetBuffer2D::getFVF() const
{
    return (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
}

bool WidgetBuffer2D::createShape()
{
    stD3DVertex data[] =
    {
        {this->_shape.x(), -this->_shape.y(), 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), this->_tu[3], this->_tv[3]},
        {this->_shape.x(), this->_shape.y(), 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), this->_tu[1], this->_tv[1]},
        {-this->_shape.x(), -this->_shape.y(), 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), this->_tu[2], this->_tv[2]},
        {-this->_shape.x(), this->_shape.y(), 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), this->_tu[0], this->_tv[0]},
    };
    LPDIRECT3DDEVICE9 device = Framework::getInstance()->device();
    if (FAILED(device->CreateVertexBuffer(sizeof(data), 0,
                                          this->getFVF(),
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
