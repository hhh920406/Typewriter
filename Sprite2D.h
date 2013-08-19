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

#include "Point2D.h"
#include "Vector2D.h"

class Texture2D;
class VertexBuffer2D;

class Sprite2D
{
public:
    Sprite2D(const float width, const float height);
    virtual ~Sprite2D();
    void setTexture(Texture2D *texture);
    void setVertexBuffer(VertexBuffer2D *vertex);
    void setVertexBufferKeepScale(VertexBuffer2D *vertex);
    virtual void act();
    void render();
    float width() const;
    float height() const;
    float halfWidth() const;
    float halfHeight() const;
    void scaleTo(float x, float y);
    void rotateTo(float angle);
    void translateTo(float x, float y);
    void deleteLater();
    bool isDeleteLater();

private:
    Texture2D *_texture;        /**纹理。*/
    VertexBuffer2D *_vertex;    /**顶点缓存。*/
    Point2D _size;              /**尺寸的一半。*/
    Point2D _scale;             /**当前的缩放量。*/
    Vector2D _translate;        /**当前的平移量。*/
    float _rotate;              /**当前的旋转量，逆时针为正方向。*/
    bool _deleteLater;          /**是否删除。*/
};

#endif // SPRITE2D_H
