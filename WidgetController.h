#ifndef WIDGETCONTROLLER_H
#define WIDGETCONTROLLER_H

#include <vector>

class Widget;
class Texture2DController;
class WidgetBuffer2DController;

class WidgetController
{
public:
    WidgetController();
    virtual ~WidgetController();
    void setTextureLocation(int index, const char *location);
    void initWidget(Widget* widget,
                    int textureIndex,
                    int x, int y,
                    int width, int height,
                    int textureX, int textureY,
                    int textureW, int textureH,
                    int textureWidth, int textureHeight);
    Texture2DController* textureController() const;
    WidgetBuffer2DController* widgetBufferController() const;

private:
    Texture2DController *_textureController;
    WidgetBuffer2DController *_widgetBufferController;
};

#endif