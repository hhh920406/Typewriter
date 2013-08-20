#ifndef WIDGETCONTROLLER_H
#define WIDGETCONTROLLER_H
/**
 * 管理基本的2D图形。
 * @author ZHG <CyberZHG@gmail.com>
 */
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
                    int textureX1, int textureY1,
                    int textureX2, int textureY2,
                    int textureWidth, int textureHeight);
    Texture2DController* textureController() const;
    WidgetBuffer2DController* widgetBufferController() const;

private:
    Texture2DController *_textureController;
    WidgetBuffer2DController *_widgetBufferController;
};

#endif // WIDGETCONTROLLER_H
