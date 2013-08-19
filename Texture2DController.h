#ifndef TEXTURE2DCONTROLLER_H
#define TEXTURE2DCONTROLLER_H
/**
 * 对纹理进行管理。
 * @author ZHG <CyberZHG@gmail.com>
 */
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
    std::map<int, const char*> _locations;     /**纹理下标和纹理所在位置的对应关系。*/
    std::map<int, Texture2D*> _textures;        /**纹理下标和纹理的对应关系。*/
};

#endif // TEXTURE2DCONTROLLER_H
