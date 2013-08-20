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

VertexBuffer2D* VertexBuffer2DController::getVertexBuffer(int textureX1, int textureY1,
                                                          int textureX2, int textureY2,
                                                          int textureWidth, int textureHeight)
{
    VertexBufferInfo info;
    info.textureX1 = textureX1;
    info.textureY1 = textureY1;
    info.textureX2 = textureX2;
    info.textureY2 = textureY2;
    info.textureWidth = textureWidth;
    info.textureHeight = textureHeight;
    map<VertexBufferInfo, VertexBuffer2D*>::iterator it = this->_buffers.find(info);
    if (it != this->_buffers.end())
    {
        return it->second;
    }
    float width = textureX2 - textureX1;
    float height = textureY2 - textureY1;
    float tu[4];
    float tv[4];
    tu[0] = tu[2] = 1.0f * textureX1 / textureWidth;
    tu[1] = tu[3] = 1.0f * textureX2 / textureWidth;
    tv[0] = tv[1] = 1.0f * textureY1 / textureHeight;
    tv[2] = tv[3] = 1.0f * textureY2 / textureHeight;
    VertexBuffer2D *vertexBuffer = this->createVertexBuffer(width, height, tu, tv);
    this->_buffers[info] = vertexBuffer;
    return vertexBuffer;
}

VertexBuffer2D* VertexBuffer2DController::createVertexBuffer(float width, float height, float tu[4], float tv[4])
{
    return new VertexBuffer2D(width, height, tu, tv);
}
