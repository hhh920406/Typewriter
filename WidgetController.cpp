#include <algorithm>
#include "Widget.h"
#include "Texture2DController.h"
#include "WidgetBuffer2DController.h"
#include "WidgetController.h"
using namespace std;

WidgetController::WidgetController()
{
    this->_textureController = new Texture2DController();
    this->_widgetBufferController = new WidgetBuffer2DController();
}

WidgetController::~WidgetController()
{
    delete this->_textureController;
    delete this->_widgetBufferController;
}

void WidgetController::setTextureLocation(int index, const char *location)
{
    this->_textureController->setLocation(index, location);
}

void WidgetController::initWidget(Widget* widget,
                                  int textureIndex,
                                  int textureX1, int textureY1,
                                  int textureX2, int textureY2,
                                  int textureWidth, int textureHeight)
{
    WidgetBuffer2D *widgetBuffer = (WidgetBuffer2D*)this->_widgetBufferController->getVertexBuffer(textureX1, textureY1, textureX2, textureY2, textureWidth, textureHeight);
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
