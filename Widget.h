#ifndef WIDGET_H
#define WIDGET_H

class Texture2D;
class WidgetBuffer2D;

class Widget
{
public:
    Widget();
    virtual ~Widget();
    void setVertexBuffer(WidgetBuffer2D* buffer);
    WidgetBuffer2D* vertexBuffer() const;
    void setTexture(Texture2D *texture);
    Texture2D* texture() const;
    virtual void act(int milliseconds);
    virtual void render();

protected:
    WidgetBuffer2D *_vertexBuffer;
    Texture2D *_texture;
};

#endif
