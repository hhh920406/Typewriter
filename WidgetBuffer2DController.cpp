#include "WidgetBuffer2DController.h"
#include "WidgetBuffer2D.h"

WidgetBuffer2DController::WidgetBuffer2DController() : VertexBuffer2DController()
{
}

VertexBuffer2D* WidgetBuffer2DController::createVertexBuffer(float width, float height, float tu[4], float tv[4])
{
    return new WidgetBuffer2D(width, height, tu, tv);
}
