#ifndef SPRITE2D_H
#define SPRITE2D_H

#include <vector>
#include "Point2D.h"
#include "Vector2D.h"

class Texture2D;
class VertexBuffer2D;

class Sprite2D
{
public:
    Sprite2D(const float width, const float height);
    virtual ~Sprite2D();
    int textureNum() const;
    void setTextureNum(const int value);
    int textureIndex() const;
    void setTextureIndex(const int value);
    void setTexture(Texture2D *texture, int index = 0);
    void setVertexBuffer(VertexBuffer2D *vertex, int index = 0);
    void setVertexBufferKeepScale(VertexBuffer2D *vertex, int index = 0);
    virtual void act(int milliseconds);
    virtual void render();
    float width() const;
    float height() const;
    float halfWidth() const;
    float halfHeight() const;
    Point2D position() const;
    void scaleTo(float x, float y);
    void rotateTo(float angle);
    void translateTo(float x, float y);
    void deleteLater();
    bool isDeleteLater();

    const Vector2D velocity() const;
    const Vector2D accelerated() const;
    void setVelocity(const Vector2D &velocity);
    void setAccelerated(const Vector2D &accelerated);
    void move(int milliSeconds);

protected:
    int _textureNum;
    int _textureIndex;
    std::vector<Texture2D*> _texture;
    std::vector<VertexBuffer2D*> _vertex;
    Point2D _size;
    Point2D _scale;
    Vector2D _translate;
    float _rotate;
    bool _deleteLater;

    Vector2D _velocity;
    Vector2D _accelerated;
};

#endif
