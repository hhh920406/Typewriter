#ifndef SCENE_H
#define SCENE_H
/**
 * 基本的场景，管理图形和处理交互。
 * @author ZHG <CyberZHG@gmail.com>
 */

#include <vector>
#include "KeyState.h"
#include "MouseState.h"
#include "Sprite2D.h"

class Scene
{
public:
    Scene();
    virtual ~Scene();

    int sceneIndex() const;
    void setSceneIndex(const int index);

    void addSprite(Sprite2D *sprite);

    virtual void load();
    virtual void release();

    virtual int act();
    virtual int render();
    virtual int keyPressEvent(KeyState::Key);
    virtual int keyReleaseEvent(KeyState::Key);
    virtual int mousePressEvent(MouseState::Key, int x, int y);
    virtual int mouseReleaseEvent(MouseState::Key, int x, int y);
    virtual int mouseMoveEvent(int x, int y);

protected:
    int _sceneIndex;
    std::vector<Sprite2D*> *_currentSprites;
    std::vector<Sprite2D*> *_nextSprites;
};

#endif // SCENE_H
