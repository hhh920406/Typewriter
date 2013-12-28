#include "defination.h"
#include "resource.h"
#include "Framework.h"
#include "SceneController.h"
#include "Sprite2DController.h"
#include "WidgetController.h"
#include "SceneMainMenu.h"
#include "SceneGameLoop.h"

int main()
{
    Framework *framework = Framework::getInstance();
    framework->init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FULLSCREEN);
    framework->spriteController()->setTextureLocation(RES_IMAGE_BULLET, RES_IMAGE_PATH_BULLET);
    framework->spriteController()->setTextureLocation(RES_IMAGE_LIVING, RES_IMAGE_PATH_LIVING);
    framework->widgetController()->setTextureLocation(RES_IMAGE_GAME_BACKGROUND, RES_IMAGE_PATH_GAME_BACKGROUND);
    framework->getInstance()->sceneController()->bindScene(SCENE_MAIN_MENU, new SceneMainMenu());
    framework->getInstance()->sceneController()->bindScene(SCENE_GAME_LOOP, new SceneGameLoop());
    framework->getInstance()->sceneController()->setFirstScene(SCENE_GAME_LOOP);
    framework->messageLoop();
    return 0;
}
