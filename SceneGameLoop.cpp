#include "SceneGameLoop.h"
#include "Framework.h"

SceneGameLoop::SceneGameLoop() : Scene()
{
}

void SceneGameLoop::load()
{
    Scene::load();
    Framework *framework = Framework::getInstance();
    this->setLayerNum(GAME_LAYER_NUM);

    Sprite2D *player = new Sprite2D(RES_SIZE_PLAYER_W, RES_SIZE_PLAYER_H);
    framework->spriteController()->initSprite(player,
                                              RES_IMAGE_LIVING,
                                              RES_POS_PLAYER_X,
                                              RES_POS_PLAYER_Y,
                                              RES_POS_PLAYER_W,
                                              RES_POS_PLAYER_H,
                                              RES_IMAGE_PATH_LIVING_W,
                                              RES_IMAGE_PATH_LIVING_H);
    player->translateTo(50 + 500 / 2, 50 + 500 / 2 + 200);
    this->addSprite(player, GAME_LAYER_ALIVE);

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
