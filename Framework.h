#ifndef FRAMEWORK_H
#define FRAMEWORK_H
/**
 * 基本的游戏框架。
 * 在程序中只能出现唯一的实例。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <d3d9.h>
#include <windows.h>

#define main zmain
int zmain();

class Framework
{
public:
    static Framework* getInstance();
    virtual ~Framework();
    LPDIRECT3D9 d3d() const;
    LPDIRECT3DDEVICE9 device() const;
    void init();
    void render();
    void messageLoop();

private:
    static Framework* _instance;
    WNDCLASSEX _window;
    LPDIRECT3D9 _d3d;
    LPDIRECT3DDEVICE9 _device;

    Framework();
    HRESULT initD3D(HWND hWnd);
};

#endif // FRAMEWORK_H
