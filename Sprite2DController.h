#ifndef SPRITE2DCONTROLLER_H
#define SPRITE2DCONTROLLER_H

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
                    int textureX, int textureY,
                    int textureW, int textureH,
                    int textureWidth, int textureHeight);
    Texture2DController* textureController() const;
    VertexBuffer2DController* vertexBufferController() const;

private:
    Texture2DController *_textureController;
    VertexBuffer2DController *_vertexBufferController;
};

#endif
