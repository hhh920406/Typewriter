#include "Texture2D.h"
#include "Texture2DController.h"
using namespace std;

Texture2DController::Texture2DController()
{
}

Texture2DController::~Texture2DController()
{
    map<int, Texture2D*>::iterator it;
    for (it = this->_textures.begin(); it != this->_textures.end(); ++it)
    {
        delete it->second;
    }
}

void Texture2DController::setLocation(int index, const char *location)
{
    this->_locations[index] = location;
}

void Texture2DController::loadTextures(vector<int> indices)
{
    this->loadNewTextures(indices);
    for (map<int, Texture2D*>::iterator i = this->_textures.begin(); i != this->_textures.end(); ++i)
    {
        bool found = false;
        for (vector<int>::iterator j = indices.begin(); j != indices.end(); ++j)
        {
            if (*j == i->first)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            delete i->second;
            i->second = NULL;
        }
    }
}

void Texture2DController::loadNewTextures(vector<int> indices)
{
    for (vector<int>::iterator it = indices.begin(); it != indices.end(); ++it)
    {
        if (NULL == this->getTexture(*it))
        {
            this->loadTexture(*it);
        }
    }
}

Texture2D* Texture2DController::getTexture(const int index)
{
    map<int, Texture2D*>::iterator it = this->_textures.find(index);
    if (it == this->_textures.end())
    {
        return NULL;
    }
    return it->second;
}

void Texture2DController::loadTexture(const int index)
{
    Texture2D *texture = new Texture2D();
    texture->readFromFile(this->_locations[index]);
    this->_textures[index] = texture;
}
