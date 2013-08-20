#ifndef WIDGETBUFFER2DCONTROLLER_H
#define WIDGETBUFFER2DCONTROLLER_H
/**
 * 管理顶点缓存。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "VertexBuffer2DController.h"

class WidgetBuffer2DController : public VertexBuffer2DController
{
public:
    WidgetBuffer2DController();

protected:
    VertexBuffer2D* createVertexBuffer(float width, float height, float tu[4], float tv[4]);
};

#endif // WIDGETBUFFER2DCONTROLLER_H
