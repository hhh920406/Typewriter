#ifndef FRAMEWORK_H
#define FRAMEWORK_H
/**
 * 基本的游戏框架。
 * 在程序中只能出现唯一的实例。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "KeyState.h"
#include "MouseState.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define main zmain
int zmain();

class Scene;
class SceneController;
class Sprite2DController;
class WidgetController;

class Framework
{
public:
    static Framework* getInstance();
    virtual ~Framework();
    LPDIRECT3D9 d3d() const;
    LPDIRECT3DDEVICE9 device() const;
    void init(const char *title, int width, int height, bool fullScreen);
    void render();
    void messageLoop();
    bool isFullscreen() const;
    int windowWidth() const;
    int windowHeight() const;
    int windowHalfWidth() const;
    int windowHalfHeight() const;

    Sprite2DController* spriteController() const;
    WidgetController* widgetController() const;
    SceneController* sceneController() const;

    KeyState* keyState() const;
    MouseState* mouseState() const;
    void keyPressEvent(const KeyState::Key key);
    void keyReleaseEvent(const KeyState::Key key);
    void mousePressEvent(const MouseState::Key key, int x, int y);
    void mouseReleaseEvent(const MouseState::Key key, int x, int y);
    void mouseMoveEvent(int x, int y);

private:
    static Framework* _instance;
    WNDCLASSEX _window;
    LPDIRECT3D9 _d3d;
    LPDIRECT3DDEVICE9 _device;
    bool _isFullscreen;
    int _windowWidth;
    int _windowHeight;
    Sprite2DController *_spriteController;
    WidgetController *_widgetController;
    SceneController *_sceneController;
    KeyState *_keyState;
    MouseState *_mouseState;

    Framework();
    bool initD3D(HWND hWnd);
};

#endif // FRAMEWORK_H
