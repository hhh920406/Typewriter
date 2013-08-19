#include "Sprite2D.h"
#include "Texture2DController.h"
#include "VertexBuffer2DController.h"
#include "Sprite2DController.h"

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

Sprite2D* Sprite2DController::createSprite(int width, int height, int textureIndex,
                                           int textureX1, int textureY1,
                                           int textureX2, int textureY2,
                                           int textureWidth, int textureHeight)
{
    Sprite2D *sprite = new Sprite2D(width, height);
    VertexBuffer2D *vertexBuffer = this->_vertexBufferController->getVertexBuffer(textureX1, textureY1, textureX2, textureY2, textureWidth, textureHeight);
    Texture2D *texture = this->_textureController->getTexture(textureIndex);
    sprite->setVertexBuffer(vertexBuffer);
    sprite->setTexture(texture);
    return sprite;
}
