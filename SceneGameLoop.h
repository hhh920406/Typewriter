#ifndef SCENEGAMELOOP_H
#define SCENEGAMELOOP_H
/**
 * 游戏的主场景。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "Scene.h"
#include "defination.h"
#include "resource.h"

class SceneGameLoop : public Scene
{
public:
    SceneGameLoop();
    virtual void load();
protected:
private:
};

#endif // SCENEGAMELOOP_H
