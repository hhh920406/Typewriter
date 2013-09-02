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
        TestSprite2D *sprite = new TestSprite2D(40, 40);
        framework->spriteController()->initSprite(sprite, 0, 320, 0, 384, 64, 1024, 1024);
        sprite->translateTo(50 + 500 / 2, 50 + 500 / 2);
        float speed = 2.0f;
        if ((rand() % 1000) == 1)
        {
            flag = -flag;
        }
        angle += flag;
        sprite->setVelocity(Vector2D(0.1 * cos(PI * 2 * (i / 4) / 100.0 + (i % 4) * PI / 2),
                                     0.1 * sin(PI * 2 * (i / 4) / 100.0 + (i % 4) * PI / 2)));
        sprite->setAccelerated(Vector2D(0.005 * cos(PI * 2 * (i / 4) / 100.0 + (i % 4) * PI / 2),
                                        0.005 * sin(PI * 2 * (i / 4) / 100.0 + (i % 4) * PI / 2)));
        sprite->setJerk(Vector2D(- 0.0002 * cos(PI * 2 * (i / 4) / 100.0 + (i % 4) * PI / 2),
                                 - 0.0002 * sin(PI * 2 * (i / 4) / 100.0 + (i % 4) * PI / 2)));
        sprite->setBirth(i / 4);
        sprite->setBounding(50, 550, 50, 550);
        this->addSprite(sprite);
    }
    framework->widgetController()->setTextureLocation(1, "back.png");
    Widget *widget;
    widget = new Widget();
    framework->widgetController()->initWidget(widget, 1,
                                              0, 0, 50, 600,
                                              0, 0, 50, 600,
                                              800, 600);
    this->addWidget(widget);
    widget = new Widget();
    framework->widgetController()->initWidget(widget, 1,
                                              50, 0, 550, 50,
                                              50, 0, 600, 50,
                                              800, 600);
    this->addWidget(widget);
    widget = new Widget();
    framework->widgetController()->initWidget(widget, 1,
                                              50, 550, 550, 50,
                                              50, 550, 600, 600,
                                              800, 600);
    this->addWidget(widget);
    widget = new Widget();
    framework->widgetController()->initWidget(widget, 1,
                                              550, 0, 250, 600,
                                              550, 0, 800, 600,
                                              800, 600);
    this->addWidget(widget);
}
