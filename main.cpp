#include "Framework.h"
#include "SceneIncrease.h"
#include "SceneController.h"

int main()
{
    Framework *framework = Framework::getInstance();
    framework->init("Framework", 800, 600, false);
    SceneIncrease *scene = new SceneIncrease();
    framework->getInstance()->sceneController()->bindScene(0, scene);
    framework->getInstance()->sceneController()->setFirstScene(0);
    framework->messageLoop();
    return 0;
}
