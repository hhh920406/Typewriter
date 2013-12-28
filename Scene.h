#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "KeyState.h"
#include "MouseState.h"

class Sprite2D;
class Widget;

class Scene
{
public:
    Scene();
    virtual ~Scene();

    int sceneIndex() const;
    void setSceneIndex(const int index);

    void setLayerNum(const int num);
    void addSprite(Sprite2D *sprite, int layer = 0);
    void addWidget(Widget *widget);

    virtual void load();
    virtual void release();

    virtual int act(int milliseconds);
    virtual int render();
    virtual int keyPressEvent(KeyState::Key);
    virtual int keyReleaseEvent(KeyState::Key);
    virtual int mousePressEvent(MouseState::Key, int x, int y);
    virtual int mouseReleaseEvent(MouseState::Key, int x, int y);
    virtual int mouseMoveEvent(int x, int y);

protected:
    int _sceneIndex;
    int _spriteLayerNum;
    int _currentSpriteIndex;
    std::vector< std::vector<Sprite2D*> > _sprites[2];
    std::vector<Widget*> _widgets;
};

#endif
