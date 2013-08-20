#ifndef SPRITE2DCONTROLLER_H
#define SPRITE2DCONTROLLER_H
/**
 * 管理基本的2D图形。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <vector>

class Sprite2D;
class Texture2DController;
class VertexBuffer2DController;

class Sprite2DController
{
public:
    Sprite2DController();
    virtual ~Sprite2DController();
    void setTextureLocation(int index, const char *location);
    void initSprite(Sprite2D* sprite,
                    int textureIndex,
                    int textureX1, int textureY1,
                    int textureX2, int textureY2,
                    int textureWidth, int textureHeight);
    void act();
    void render();
    Texture2DController* textureController() const;
    VertexBuffer2DController* vertexBufferController() const;

private:
    Texture2DController *_textureController;
    VertexBuffer2DController *_vertexBufferController;
    std::vector<Sprite2D*> *_currentSprites;
    std::vector<Sprite2D*> *_nextSprites;
};

#endif // SPRITE2DCONTROLLER_H
