#ifndef SPRITE2DCONTROLLER_H
#define SPRITE2DCONTROLLER_H
/**
 * 管理基本的2D图形。
 * @author ZHG <CyberZHG@gmail.com>
 */

class Sprite2D;
class Texture2DController;
class VertexBuffer2DController;

class Sprite2DController
{
public:
    Sprite2DController();
    virtual ~Sprite2DController();
    void setTextureLocation(int index, const char *location);
    Sprite2D* createSprite(int width, int height, int textureIndex,
                           int textureX1, int textureY1,
                           int textureX2, int textureY2,
                           int textureWidth, int textureHeight);

private:
    Texture2DController *_textureController;
    VertexBuffer2DController *_vertexBufferController;
};

#endif // SPRITE2DCONTROLLER_H
