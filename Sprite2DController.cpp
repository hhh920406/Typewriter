#include <algorithm>
#include "Sprite2D.h"
#include "Texture2DController.h"
#include "VertexBuffer2DController.h"
#include "Sprite2DController.h"
using namespace std;

Sprite2DController::Sprite2DController()
{
    this->_textureController = new Texture2DController();
    this->_vertexBufferController = new VertexBuffer2DController();
}

Sprite2DController::~Sprite2DController()
{
    delete this->_textureController;
    delete this->_vertexBufferController;
}

void Sprite2DController::setTextureLocation(int index, const char *location)
{
    this->_textureController->setLocation(index, location);
}

void Sprite2DController::initSprite(Sprite2D* sprite,
                                    int textureIndex,
                                    int textureX1, int textureY1,
                                    int textureX2, int textureY2,
                                    int textureWidth, int textureHeight)
{
    VertexBuffer2D *vertexBuffer = this->_vertexBufferController->getVertexBuffer(textureX1, textureY1, textureX2, textureY2, textureWidth, textureHeight);
    Texture2D *texture = this->_textureController->getTexture(textureIndex);
    sprite->setVertexBuffer(vertexBuffer);
    sprite->setTexture(texture);
}

Texture2DController* Sprite2DController::textureController() const
{
    return this->_textureController;
}

VertexBuffer2DController* Sprite2DController::vertexBufferController() const
{
    return this->_vertexBufferController;
}
