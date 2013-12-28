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
                                    int textureX, int textureY,
                                    int textureW, int textureH,
                                    int textureWidth, int textureHeight)
{
    VertexBuffer2D *vertexBuffer = this->_vertexBufferController->getVertexBuffer(textureX, textureY, (textureX + textureW), (textureY + textureH), textureWidth, textureHeight);
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
