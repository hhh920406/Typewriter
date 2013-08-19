#include "Point2D.h"
#include "VertexBuffer2D.h"
#include "VertexBuffer2DController.h"
using namespace std;

VertexBuffer2DController::VertexBuffer2DController()
{
}

VertexBuffer2DController::~VertexBuffer2DController()
{
    for (map<VertexBufferInfo, VertexBuffer2D*>::iterator it = this->_buffers.begin(); it != this->_buffers.end(); ++it)
    {
        delete it->second;
    }
}

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

VertexBuffer2D* VertexBuffer2DController::getVertexBuffer(int width, int height, int tun[4], int tud[4], int tvn[4], int tvd[4])
{
    VertexBufferInfo info;
    info.width = width;
    info.height = height;
    for (int i = 0; i < 4; ++i)
    {
        int g;
        g = gcd(tun[i], tud[i]);
        info.tun[i] = tun[i] / g;
        info.tud[i] = tud[i] / g;
        g = gcd(tvn[i], tvd[i]);
        info.tvn[i] = tvn[i] / g;
        info.tvd[i] = tvd[i] / g;
    }
    map<VertexBufferInfo, VertexBuffer2D*>::iterator it = this->_buffers.find(info);
    if (it != this->_buffers.end())
    {
        return it->second;
    }
    float tu[4];
    float tv[4];
    for (int i = 0; i < 4; ++i)
    {
        tu[i] = 1.0f * tun[i] / tud[i];
        tv[i] = 1.0f * tvn[i] / tvd[i];
    }
    VertexBuffer2D *vertexBuffer = new VertexBuffer2D(width, height, tu, tv);
    this->_buffers[info] = vertexBuffer;
    return vertexBuffer;
}
