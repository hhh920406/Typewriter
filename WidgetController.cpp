#include <algorithm>
#include "Widget.h"
#include "WidgetBuffer2D.h"
#include "Texture2DController.h"
#include "WidgetController.h"
using namespace std;

WidgetController::WidgetController()
{
    this->_textureController = new Texture2DController();
}

WidgetController::~WidgetController()
{
    delete this->_textureController;
}

void WidgetController::setTextureLocation(int index, const char *location)
{
    this->_textureController->setLocation(index, location);
}

void WidgetController::initWidget(Widget* widget,
                                  int textureIndex,
                                  int x, int y,
                                  int width, int height,
                                  int textureX, int textureY,
                                  int textureW, int textureH,
                                  int textureWidth, int textureHeight)
{
    float tu[4];
    float tv[4];
    tu[0] = tu[2] = 1.0f * textureX / textureWidth;
    tu[1] = tu[3] = 1.0f * (textureX + textureW) / textureWidth;
    tv[0] = tv[1] = 1.0f * textureY / textureHeight;
    tv[2] = tv[3] = 1.0f * (textureY + textureH) / textureHeight;
    WidgetBuffer2D *widgetBuffer = new WidgetBuffer2D(x, y, width, height, tu, tv);
    Texture2D *texture = this->_textureController->getTexture(textureIndex);
    widget->setVertexBuffer(widgetBuffer);
    widget->setTexture(texture);
}

Texture2DController* WidgetController::textureController() const
{
    return this->_textureController;
}

WidgetBuffer2DController* WidgetController::widgetBufferController() const
{
    return this->_widgetBufferController;
}
