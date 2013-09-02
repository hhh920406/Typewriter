#ifndef SPRITE2D_H
#define SPRITE2D_H
/**
 * 基本的2D图形，以矩形中心作为中心。
 * 坐标以左上角作为零点，向右为x轴正向，向下为y轴正向。
 * 图形必须指定宽高，改变大小由几何变换实现。
 * 想要显示图形需要指定顶点缓存和纹理，在设置了顶点缓存没设置纹理的情况下，显示的是白色矩形。
 * 基本几何变换的执行顺序是：缩放->旋转->平移。
 * @author ZHG <CyberZHG@gmail.com>
 */
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
    int _textureNum;                    /**纹理的数量。*/
    int _textureIndex;                  /**当前纹理的索引。*/
    std::vector<Texture2D*> _texture;        /**纹理。*/
    std::vector<VertexBuffer2D*> _vertex;    /**顶点缓存。*/
    Point2D _size;              /**尺寸的一半。*/
    Point2D _scale;             /**当前的缩放量。*/
    Vector2D _translate;        /**当前的平移量。*/
    float _rotate;              /**当前的旋转量，逆时针为正方向。*/
    bool _deleteLater;          /**是否删除。*/

    Vector2D _velocity;         /**移动的速度，以像素/毫秒为单位。*/
    Vector2D _accelerated;      /**移动的加速度。*/
};

#endif // SPRITE2D_H
