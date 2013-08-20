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
    this->_currentSprites = new vector<Sprite2D*>();
    this->_nextSprites = new vector<Sprite2D*>();
}

Sprite2DController::~Sprite2DController()
{
    delete this->_textureController;
    delete this->_vertexBufferController;
    delete this->_currentSprites;
    delete this->_nextSprites;
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
    this->_currentSprites->push_back(sprite);
}
#include <cstdio>
void Sprite2DController::act()
{
    for (int i = 0; i < this->_currentSprites->size(); ++i)
    {
        if ((*this->_currentSprites)[i]->isDeleteLater())
        {
            delete (*this->_currentSprites)[i];
            (*this->_currentSprites)[i] = NULL;
        }
        else
        {
            (*this->_currentSprites)[i]->act();
            this->_nextSprites->push_back((*this->_currentSprites)[i]);
        }
    }
    swap(this->_currentSprites, this->_nextSprites);
    this->_nextSprites->clear();
    printf("%d\n", this->_currentSprites->size());
}

void Sprite2DController::render()
{
    for (int i = 0; i < this->_currentSprites->size(); ++i)
    {
        (*this->_currentSprites)[i]->render();
    }
}
