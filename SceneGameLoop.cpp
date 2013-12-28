#include "SceneGameLoop.h"
#include "Framework.h"
#include "Widget.h"
#include "WidgetController.h"

SceneGameLoop::SceneGameLoop() : Scene()
{
}
#include <cstdio>
void SceneGameLoop::load()
{
    Scene::load();
    Framework *framework = Framework::getInstance();
    this->setLayerNum(GAME_LAYER_NUM);
    // Load outer background.
    Widget *widget;
    widget = new Widget();
    framework->widgetController()->initWidget(widget,
                                              RES_IMAGE_GAME_BACKGROUND,
                                              RES_POS_GAME_BACKGROUND_LEFT_X,
                                              RES_POS_GAME_BACKGROUND_LEFT_Y,
                                              RES_POS_GAME_BACKGROUND_LEFT_W,
                                              RES_POS_GAME_BACKGROUND_LEFT_H,
                                              RES_POS_GAME_BACKGROUND_LEFT_X,
                                              RES_POS_GAME_BACKGROUND_LEFT_Y,
                                              RES_POS_GAME_BACKGROUND_LEFT_W,
                                              RES_POS_GAME_BACKGROUND_LEFT_H,
                                              RES_IMAGE_SIZE_GAME_BACKGROUND_W,
                                              RES_IMAGE_SIZE_GAME_BACKGROUND_H);
    this->addWidget(widget);
    widget = new Widget();
    framework->widgetController()->initWidget(widget,
                                              RES_IMAGE_GAME_BACKGROUND,
                                              RES_POS_GAME_BACKGROUND_RIGHT_X,
                                              RES_POS_GAME_BACKGROUND_RIGHT_Y,
                                              RES_POS_GAME_BACKGROUND_RIGHT_W,
                                              RES_POS_GAME_BACKGROUND_RIGHT_H,
                                              RES_POS_GAME_BACKGROUND_RIGHT_X,
                                              RES_POS_GAME_BACKGROUND_RIGHT_Y,
                                              RES_POS_GAME_BACKGROUND_RIGHT_W,
                                              RES_POS_GAME_BACKGROUND_RIGHT_H,
                                              RES_IMAGE_SIZE_GAME_BACKGROUND_W,
                                              RES_IMAGE_SIZE_GAME_BACKGROUND_H);
    this->addWidget(widget);
    widget = new Widget();
    framework->widgetController()->initWidget(widget,
                                              RES_IMAGE_GAME_BACKGROUND,
                                              RES_POS_GAME_BACKGROUND_TOP_X,
                                              RES_POS_GAME_BACKGROUND_TOP_Y,
                                              RES_POS_GAME_BACKGROUND_TOP_W,
                                              RES_POS_GAME_BACKGROUND_TOP_H,
                                              RES_POS_GAME_BACKGROUND_TOP_X,
                                              RES_POS_GAME_BACKGROUND_TOP_Y,
                                              RES_POS_GAME_BACKGROUND_TOP_W,
                                              RES_POS_GAME_BACKGROUND_TOP_H,
                                              RES_IMAGE_SIZE_GAME_BACKGROUND_W,
                                              RES_IMAGE_SIZE_GAME_BACKGROUND_H);
    this->addWidget(widget);
    widget = new Widget();
    framework->widgetController()->initWidget(widget,
                                              RES_IMAGE_GAME_BACKGROUND,
                                              RES_POS_GAME_BACKGROUND_BOTTOM_X,
                                              RES_POS_GAME_BACKGROUND_BOTTOM_Y,
                                              RES_POS_GAME_BACKGROUND_BOTTOM_W,
                                              RES_POS_GAME_BACKGROUND_BOTTOM_H,
                                              RES_POS_GAME_BACKGROUND_BOTTOM_X,
                                              RES_POS_GAME_BACKGROUND_BOTTOM_Y,
                                              RES_POS_GAME_BACKGROUND_BOTTOM_W,
                                              RES_POS_GAME_BACKGROUND_BOTTOM_H,
                                              RES_IMAGE_SIZE_GAME_BACKGROUND_W,
                                              RES_IMAGE_SIZE_GAME_BACKGROUND_H);
    this->addWidget(widget);
}
