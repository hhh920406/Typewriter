#include "SceneController.h"
using namespace std;

SceneController::SceneController()
{
    this->_currentScene = NULL;
}

SceneController::~SceneController()
{
    map<int, Scene*>::iterator it;
    for (it = this->_scenes.begin(); it != this->_scenes.end(); ++it)
    {
        delete it->second;
    }
}

void SceneController::bindScene(const int index, Scene *scene)
{
    this->_scenes[index] = scene;
    scene->setSceneIndex(index);
}

void SceneController::setFirstScene(const int index)
{
    this->_currentIndex = index;
    this->_currentScene = this->_scenes[index];
    this->_currentScene->load();
}

void SceneController::setScene(const int index)
{
    if (this->_currentIndex != index)
    {
        this->_currentScene->release();
        this->_currentIndex = index;
        this->_currentScene = this->_scenes[index];
        this->_currentScene->load();
    }
}

void SceneController::act()
{
    if (this->_currentScene != NULL)
    {
        this->setScene(this->_currentScene->act());
    }
}

void SceneController::render()
{
    if (this->_currentScene != NULL)
    {
        this->setScene(this->_currentScene->render());
    }
}

void SceneController::keyPressEvent(KeyState::Key key)
{
    if (this->_currentScene != NULL)
    {
        this->setScene(this->_currentScene->keyPressEvent(key));
    }
}

void SceneController::keyReleaseEvent(KeyState::Key key)
{
    if (this->_currentScene != NULL)
    {
        this->setScene(this->_currentScene->keyReleaseEvent(key));
    }
}

void SceneController::mousePressEvent(MouseState::Key key, int x, int y)
{
    if (this->_currentScene != NULL)
    {
        this->setScene(this->_currentScene->mousePressEvent(key, x, y));
    }
}

void SceneController::mouseReleaseEvent(MouseState::Key key, int x, int y)
{
    if (this->_currentScene != NULL)
    {
        this->setScene(this->_currentScene->mouseReleaseEvent(key, x, y));
    }
}

void SceneController::mouseMoveEvent(int x, int y)
{
    if (this->_currentScene != NULL)
    {
        this->setScene(this->_currentScene->mouseMoveEvent(x, y));
    }
}
