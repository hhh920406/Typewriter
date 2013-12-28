#ifndef TEXTURE2DCONTROLLER_H
#define TEXTURE2DCONTROLLER_H

#include <map>
#include <vector>

class Texture2D;

class Texture2DController
{
public:
    Texture2DController();
    virtual ~Texture2DController();
    void setLocation(int index, const char *location);
    void loadTextures(std::vector<int> indices);
    void loadNewTextures(std::vector<int> indices);
    Texture2D* getTexture(const int index);

protected:
    void loadTexture(const int index);

private:
    std::map<int, const char*> _locations;
    std::map<int, Texture2D*> _textures;
};

#endif
