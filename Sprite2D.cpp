#include <cstring>
#include <windows.h>
#include "Texture2D.h"
#include "VertexBuffer2D.h"
#include "Sprite2D.h"
#include "Framework.h"

Sprite2D::Sprite2D(const float width, const float height)
{
    this->setTextureNum(1);
    this->setTextureIndex(0);
    this->_size.setPos(width * 0.5f, height * 0.5f);
    this->_scale.setPos(1.0f, 1.0f);
    this->_rotate = 0.0f;
    this->_translate.setPos(0.0f, 0.0f);
    this->_deleteLater = false;

    this->_velocity.setPos(0.0f, 0.0f);
    this->_accelerated.setPos(0.0f, 0.0f);
    this->_jerk.setPos(0.0f, 0.0f);
}

Sprite2D::~Sprite2D()
{
}

int Sprite2D::textureNum() const
{
    return this->_textureNum;
}

void Sprite2D::setTextureNum(const int value)
{
    this->_textureNum = value;
    if (this->_textureIndex >= this->_textureNum)
    {
        this->_textureIndex = this->_textureNum - 1;
    }
    while (this->_texture.size() < value)
    {
        this->_texture.push_back(0L);
        this->_vertex.push_back(0L);
    }
}

int Sprite2D::textureIndex() const
{
    return this->_textureIndex;
}

void Sprite2D::setTextureIndex(const int value)
{
    this->_textureIndex = value;
    if (this->_textureIndex < 0)
    {
        this->_textureIndex = 0;
    }
    else if (this->_textureIndex >= this->_textureNum)
    {
        this->_textureIndex = this->_textureNum - 1;
    }
}

void Sprite2D::setTexture(Texture2D *texture, int index)
{
    if (index >= 0 && index < this->_textureNum)
    {
        this->_texture[index] = texture;
    }
}

/**
 * 设置顶点缓存。
 * 由于定点缓存的尺寸和当前图形的尺寸不一定相同，这里会清空以前的缩放设定。
 */
void Sprite2D::setVertexBuffer(VertexBuffer2D *vertex, int index)
{
    if (index >= 0 && index < this->_textureNum)
    {
        this->_vertex[index] = vertex;
        this->scaleTo(1.0f, 1.0f);
    }
}

/**
 * 设置顶点缓存，保留原来的缩放。
 * 当顶点缓存尺寸不变的情况下使用。
 */
void Sprite2D::setVertexBufferKeepScale(VertexBuffer2D *vertex, int index)
{
    if (index >= 0 && index < this->_textureNum)
    {
        this->_vertex[index] = vertex;
    }
}

void Sprite2D::act(int milliseconds)
{
    this->move(milliseconds);
}

void Sprite2D::render()
{
    if (0L != this->_vertex[this->_textureIndex])
    {
        LPDIRECT3DDEVICE9 device = Framework::getInstance()->device();
        D3DXMATRIX worldMatrix;
        D3DXMATRIX scale;
        D3DXMATRIX rotate;
        D3DXMATRIX translate;
        D3DXMatrixScaling(&scale, this->_scale.x(), this->_scale.y(), 1.0f);
        D3DXMatrixRotationZ(&rotate, this->_rotate);
        float x = this->_translate.x() - Framework::getInstance()->windowHalfWidth();
        float y = Framework::getInstance()->windowHalfHeight() - this->_translate.y();
        D3DXMatrixTranslation(&translate, x, y, 0.0f);
        D3DXMatrixMultiply(&worldMatrix, &scale, &rotate);
        D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translate);
        device->SetTransform(D3DTS_WORLD, &worldMatrix);
        if (0L != this->_texture[this->_textureIndex])
        {
            device->SetTexture(0, this->_texture[this->_textureIndex]->texture());
        }
        device->SetStreamSource(0, this->_vertex[this->_textureIndex]->vertexBuffer(), 0, this->_vertex[this->_textureIndex]->vertexSize());
        device->SetFVF(this->_vertex[this->_textureIndex]->getFVF());
        device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    }
}

float Sprite2D::width() const
{
    return this->_size.x() * 2.0f;
}

float Sprite2D::height() const
{
    return this->_size.y() * 2.0f;
}

float Sprite2D::halfWidth() const
{
    return this->_size.x();
}

float Sprite2D::halfHeight() const
{
    return this->_size.y();
}

Point2D Sprite2D::position() const
{
    return this->_translate;
}

/**
 * 立即改变缩放的数值。
 * 类中的_size记录的是显示时的大小，
 */
void Sprite2D::scaleTo(float x, float y)
{
    if (0L != this->_vertex[this->_textureIndex])
    {
        float sx = this->halfWidth() / this->_vertex[this->_textureIndex]->halfWidth() * x;
        float sy = this->halfHeight() / this->_vertex[this->_textureIndex]->halfHeight() * y;
        this->_scale.setPos(sx, sy);
    }
    else
    {
        this->_scale.setPos(x, y);
    }
}

/**
 * 立即改变缩放的数值。
 */
void Sprite2D::rotateTo(float angle)
{
    this->_rotate = angle;
}

/**
 * 立即改变旋转的数值。
 */
void Sprite2D::translateTo(float x, float y)
{
    this->_translate.setPos(x, y);
}

void Sprite2D::deleteLater()
{
    this->_deleteLater = true;
}

bool Sprite2D::isDeleteLater()
{
    return this->_deleteLater;
}

const Vector2D Sprite2D::velocity() const
{
    return this->_velocity;
}

const Vector2D Sprite2D::accelerated() const
{
    return this->_accelerated;
}

const Vector2D Sprite2D::jerk() const
{
    return this->_jerk;
}

void Sprite2D::setVelocity(const Vector2D &velocity)
{
    this->_velocity = velocity;
}

void Sprite2D::setAccelerated(const Vector2D &accelerated)
{
    this->_accelerated = accelerated;
}

void Sprite2D::setJerk(const Vector2D &jerk)
{
    this->_jerk = jerk;
}

void Sprite2D::move(int milliSeconds)
{
    this->_accelerated = this->_accelerated + this->_jerk;
    this->_velocity = this->_velocity + this->_accelerated;
    this->_translate = this->_translate + this->_velocity * milliSeconds;
}
