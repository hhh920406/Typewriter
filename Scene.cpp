#include "Scene.h"
using namespace std;

Scene::Scene()
{
    this->_currentSprites = new vector<Sprite2D*>();
    this->_nextSprites = new vector<Sprite2D*>();
}

Scene::~Scene()
{
    this->release();
    delete this->_currentSprites;
    delete this->_nextSprites;
}

void Scene::load()
{
}

void Scene::release()
{
    for (int i = 0; i < this->_currentSprites->size(); ++i)
    {
        delete (*this->_currentSprites)[i];
    }
    this->_currentSprites->clear();
}

int Scene::sceneIndex() const
{
    return this->_sceneIndex;
}

void Scene::setSceneIndex(const int index)
{
    this->_sceneIndex = index;
}

void Scene::addSprite(Sprite2D *sprite)
{
    this->_currentSprites->push_back(sprite);
}

int Scene::act()
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
    return this->_sceneIndex;
}

int Scene::render()
{
    for (int i = 0; i < this->_currentSprites->size(); ++i)
    {
        (*this->_currentSprites)[i]->render();
    }
    return this->_sceneIndex;
}

int Scene::keyPressEvent(KeyState::Key)
{
    return this->_sceneIndex;
}

int Scene::keyReleaseEvent(KeyState::Key)
{
    return this->_sceneIndex;
}

int Scene::mousePressEvent(MouseState::Key, int x, int y)
{
    return this->_sceneIndex;
}

int Scene::mouseReleaseEvent(MouseState::Key, int x, int y)
{
    return this->_sceneIndex;
}

int Scene::mouseMoveEvent(int x, int y)
{
    return this->_sceneIndex;
}
