#include "Framework.h"
#include "Sprite2D.h"

#include <cstdio>

Framework* Framework::_instance = NULL;

HINSTANCE hInst;

INT WINAPI WinMain(HINSTANCE h, HINSTANCE, LPSTR, INT)
{
    hInst = h;
    zmain();
    return 0;
}

LRESULT WINAPI messageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        Framework::getInstance()->render();
        ValidateRect(hWnd, NULL);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

Framework::Framework()
{
    this->_d3d = NULL;
    this->_device = NULL;
}

Framework::~Framework()
{
    if (this->_device != NULL)
    {
        this->_device->Release();
    }
    if (this->_d3d != NULL)
    {
        this->_d3d->Release();
    }
}

Framework* Framework::getInstance()
{
    if (NULL == Framework::_instance)
    {
        Framework::_instance = new Framework();
    }
    return Framework::_instance;
}

LPDIRECT3D9 Framework::d3d() const
{
    return this->_d3d;
}

LPDIRECT3DDEVICE9 Framework::device() const
{
    return this->_device;
}

void Framework::init(const char *title, int width, int height, bool fullScreen)
{
    this->_windowWidth = width;
    this->_windowHeight = height;
    this->_isFullscreen = fullScreen;
    this->_window =
    {
        sizeof(WNDCLASSEX), CS_CLASSDC, messageProcess, 0L, 0L,
        GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
        "ZSTG", NULL
    };
    RegisterClassEx(&this->_window);
    HWND hWnd = CreateWindow("ZSTG", title,
                             WS_OVERLAPPEDWINDOW, 100, 100, this->windowWidth(), this->windowHeight(),
                             NULL, NULL, this->_window.hInstance, NULL);
    if (this->initD3D(hWnd))
    {
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);
    }
}

bool Framework::initD3D(HWND hWnd)
{
    D3DDISPLAYMODE displayMode;
    this->_d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (NULL == this->_d3d)
    {
        return false;
    }
    if (FAILED(this->_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
    {
        return false;
    }
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    if (this->isFullscreen())
    {
        d3dpp.Windowed = FALSE;
        d3dpp.BackBufferWidth = this->windowWidth();
        d3dpp.BackBufferHeight = this->windowHeight();
    }
    else
    {
        d3dpp.Windowed = TRUE;
    }
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = displayMode.Format;
    if (FAILED(this->_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                         &d3dpp, &this->_device)))
    {
        return false;
    }
    // 测试开始
    this->_testSprite = new Sprite2D(200, 200);
    // 测试结束
    return true;
}

void Framework::render()
{
    if (NULL == this->_device)
    {
        return;
    }
    this->_device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    if (SUCCEEDED(this->_device->BeginScene()))
    {
        // 测试开始
        this->_device->SetStreamSource(0, this->_testSprite->vertexBuffer(),
                                        0, this->_testSprite->vertexSize());
        this->_device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
        this->_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
        // 测试结束
        this->_device->EndScene();
    }
    this->_device->Present(NULL, NULL, NULL, NULL);
}

void Framework::messageLoop()
{
    MSG msg;
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            this->render();
        }
    }
    UnregisterClass("ZFramework", this->_window.hInstance);
}

bool Framework::isFullscreen() const
{
    return this->_isFullscreen;
}

int Framework::windowWidth() const
{
    return this->_windowWidth;
}

int Framework::windowHeight() const
{
    return this->_windowHeight;
}
