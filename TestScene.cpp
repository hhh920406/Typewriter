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
    this->setLayerNum(2);
    const double PI = acos(-1.0);
    int flag = 1;
    int angle = 0;
    for (int i = 0; i < 20000; ++i)
    {
        TestSprite2D *sprite;
        double angle = i / 100.0 * PI + rand() % 30 / 180.0 * PI + (i % 4) * PI / 2;
        double speed = 0.2 + rand() % 100 / 1000.0;
        sprite = new TestSprite2D(80, 80);
        framework->spriteController()->initSprite(sprite, 0, 192, 128, 256, 192, 1024, 1024);
        sprite->setVelocity(Vector2D(speed * cos(angle), speed * sin(angle)));
        sprite->setBirth(i);
        sprite->translateTo(50 + 500 / 2, 50 + 500 / 2);
        sprite->setBounding(50, 550, 50, 550);
        this->addSprite(sprite, 0);

        sprite = new TestSprite2D(30, 30);
        framework->spriteController()->initSprite(sprite, 0, 512, 0, 576, 64, 1024, 1024);
        sprite->setVelocity(Vector2D(speed * cos(angle), speed * sin(angle)));
        sprite->setBirth(i);
        sprite->translateTo(50 + 500 / 2, 50 + 500 / 2);
        sprite->setBounding(50, 550, 50, 550);
        this->addSprite(sprite, 1);
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
