#include "defination.h"
#include "Framework.h"
#include "SceneController.h"
#include "SceneMainMenu.h"
#include "SceneGameLoop.h"
#include "TestScene.h"

int main()
{
    Framework *framework = Framework::getInstance();
    framework->init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, false);

    // 绑定场景。
    Scene *scene;

    scene = new SceneMainMenu();
    framework->getInstance()->sceneController()->bindScene(SCENE_MAIN_MENU, scene);
    scene = new SceneGameLoop();
    framework->getInstance()->sceneController()->bindScene(SCENE_GAME_LOOP, scene);

    framework->getInstance()->sceneController()->setFirstScene(SCENE_MAIN_MENU);

    scene = new TestScene();
    framework->getInstance()->sceneController()->bindScene(SCENE_NULL, scene);
    framework->getInstance()->sceneController()->setFirstScene(SCENE_NULL);

    framework->messageLoop();
    return 0;
}
