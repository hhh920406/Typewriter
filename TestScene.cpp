#include <cstdlib>
#include "TestScene.h"
#include "Framework.h"
#include "Sprite2DController.h"
#include "Widget.h"
#include "WidgetController.h"
#include "TestSprite2D.h"

TestScene::TestScene() : Scene()
{
}

void TestScene::load()
{
    Scene::load();
    Framework *framework = Framework::getInstance();
    framework->spriteController()->setTextureLocation(0, "bullet.png");
    const double PI = acos(-1.0);
    int flag = 1;
    int angle = 0;
    for (int i = 0; i < 20000; ++i)
    {
        TestSprite2D *sprite = new TestSprite2D(40, 20);
        framework->spriteController()->initSprite(sprite, 0, 320, 0, 384, 64, 1024, 1024);
        sprite->setPosition(50 + 500 / 2, 50 + 620 / 2);
        float speed = 2.0f;
        if ((rand() % 1000) == 1)
        {
            flag = -flag;
        }
        angle += flag;
        sprite->setSpeed(speed * cos(PI / 4 + 2 * PI / 13 * (angle % 13)),
                        speed * sin(PI / 4 + 2 * PI / 13 * (angle % 13)));
        sprite->setBirth(i / 13);
        sprite->setBounding(50, 550, 50, 670);
        this->addSprite(sprite);
    }
    framework->widgetController()->setTextureLocation(1, "back.png");
    Widget *widget;
    widget = new Widget();
    framework->widgetController()->initWidget(widget, 1,
                                              0, 0, 50, 720,
                                              0, 0, 50, 720,
                                              960, 720);
    this->addWidget(widget);
    widget = new Widget();
    framework->widgetController()->initWidget(widget, 1,
                                              50, 0, 550 - 50, 50,
                                              50, 0, 550, 50,
                                              960, 720);
    this->addWidget(widget);
    widget = new Widget();
    framework->widgetController()->initWidget(widget, 1,
                                              50, 670, 550 - 50, 720 - 670,
                                              50, 670, 550, 720,
                                              960, 720);
    this->addWidget(widget);
    widget = new Widget();
    framework->widgetController()->initWidget(widget, 1,
                                              550, 0, 960 - 550, 720,
                                              550, 0, 960, 720,
                                              960, 720);
    this->addWidget(widget);
}
