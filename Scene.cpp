#include "Sprite2D.h"
#include "Widget.h"
#include "Scene.h"
using namespace std;

Scene::Scene()
{
    this->_spriteLayerNum = 1;
    this->_currentSpriteIndex = 0;
    this->_sprites[0].push_back(vector<Sprite2D*>());
    this->_sprites[1].push_back(vector<Sprite2D*>());
}

Scene::~Scene()
{
    this->release();
}

void Scene::load()
{
}

void Scene::release()
{
    for (int i = 0; i < this->_sprites[this->_currentSpriteIndex].size(); ++i)
    {
        for (int j = 0; j < this->_sprites[this->_currentSpriteIndex][i].size(); ++j)
        {
            delete this->_sprites[this->_currentSpriteIndex][i][j];
        }
        this->_sprites[this->_currentSpriteIndex][i].clear();
    }
    this->_sprites[this->_currentSpriteIndex].clear();
    for (int i = 0; i < this->_widgets.size(); ++i)
    {
        delete this->_widgets[i];
    }
    this->_widgets.clear();
}

int Scene::sceneIndex() const
{
    return this->_sceneIndex;
}

void Scene::setSceneIndex(const int index)
{
    this->_sceneIndex = index;
}

void Scene::setLayerNum(const int num)
{
    while (num > this->_sprites[0].size())
    {
        this->_sprites[0].push_back(vector<Sprite2D*>());
        this->_sprites[1].push_back(vector<Sprite2D*>());
    }
    while (num < this->_sprites[0].size())
    {
        int curr = this->_currentSpriteIndex;
        int index = this->_sprites[0].size() - 1;
        for (int i = 0; i < this->_sprites[curr][index].size(); ++i)
        {
            delete this->_sprites[curr][index][i];
        }
        this->_sprites[0][index].clear();
        this->_sprites[1][index].clear();
        this->_sprites[0].pop_back();
        this->_sprites[1].pop_back();
    }
}

void Scene::addSprite(Sprite2D *sprite, int layer)
{
    if (layer < this->_sprites[this->_currentSpriteIndex].size())
    {
        this->_sprites[this->_currentSpriteIndex][layer].push_back(sprite);
    }
}

void Scene::addWidget(Widget *widget)
{
    this->_widgets.push_back(widget);
}

int Scene::act(int milliseconds)
{
    int curr = this->_currentSpriteIndex;
    int next = this->_currentSpriteIndex ^ 1;
    for (int i = 0; i < this->_sprites[curr].size(); ++i)
    {
        this->_sprites[next][i].clear();
        for (int j = 0; j < this->_sprites[curr][i].size(); ++j)
        {
            if (this->_sprites[curr][i][j]->isDeleteLater())
            {
                delete this->_sprites[curr][i][j];
                this->_sprites[curr][i][j] = NULL;
            }
            else
            {
                this->_sprites[curr][i][j]->act(milliseconds);
                this->_sprites[next][i].push_back(this->_sprites[curr][i][j]);
            }
        }
    }
    this->_currentSpriteIndex = next;

    for (int i = 0; i < this->_widgets.size(); ++i)
    {
        this->_widgets[i]->act(milliseconds);
    }
    return this->_sceneIndex;
}

int Scene::render()
{
    int curr = this->_currentSpriteIndex;
    for (int i = 0; i < this->_sprites[curr].size(); ++i)
    {
        for (int j = 0; j < this->_sprites[curr][i].size(); ++j)
        {
            this->_sprites[curr][i][j]->render();
        }
    }
    for (int i = 0; i < this->_widgets.size(); ++i)
    {
        this->_widgets[i]->render();
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
