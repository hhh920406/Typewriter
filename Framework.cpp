#include <cmath>
#include "Framework.h"
#include "Sprite2D.h"
#include "Sprite2DController.h"
#include "Scene.h"
#include "SceneController.h"
#include "WidgetController.h"

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
    case WM_KEYDOWN:
        Framework::getInstance()->keyPressEvent(KeyState::convertKey(wParam));
        break;
    case WM_KEYUP:
        Framework::getInstance()->keyReleaseEvent(KeyState::convertKey(wParam));
        break;
    case WM_LBUTTONDOWN:
        Framework::getInstance()->mousePressEvent(MouseState::KEY_LEFT, LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_RBUTTONDOWN:
        Framework::getInstance()->mousePressEvent(MouseState::KEY_RIGHT, LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_MBUTTONDOWN:
        Framework::getInstance()->mousePressEvent(MouseState::KEY_MIDDLE, LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_LBUTTONUP:
        Framework::getInstance()->mouseReleaseEvent(MouseState::KEY_LEFT, LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_RBUTTONUP:
        Framework::getInstance()->mouseReleaseEvent(MouseState::KEY_RIGHT, LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_MBUTTONUP:
        Framework::getInstance()->mouseReleaseEvent(MouseState::KEY_MIDDLE, LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_MOUSEMOVE:
        Framework::getInstance()->mouseMoveEvent(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_MOUSEWHEEL:
        break;
    case WM_MOUSELEAVE:
        break;
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
    this->_spriteController = new Sprite2DController();
    this->_widgetController = new WidgetController();
    this->_sceneController = new SceneController();
    this->_keyState = new KeyState();
    this->_mouseState = new MouseState();
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
    delete this->_spriteController;
    delete this->_widgetController;
    delete this->_sceneController;
    delete this->_keyState;
    delete this->_mouseState;
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
        "ZFramework", NULL
    };
    RegisterClassEx(&this->_window);
    RECT rect = {0, 0, width, height};
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    HWND hWnd;
    if (fullScreen)
    {
        hWnd = CreateWindow("ZFramework", title,
                            WS_EX_TOPMOST | WS_POPUP, 100, 10, rect.right - rect.left, rect.bottom - rect.top,
                            NULL, NULL, this->_window.hInstance, NULL);
    }
    else
    {
        hWnd = CreateWindow("ZFramework", title,
                            WS_OVERLAPPEDWINDOW, 100, 10, rect.right - rect.left, rect.bottom - rect.top,
                            NULL, NULL, this->_window.hInstance, NULL);
    }
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
    d3dpp.BackBufferFormat = displayMode.Format;
    if (this->isFullscreen())
    {
        d3dpp.Windowed = FALSE;
        d3dpp.BackBufferWidth = this->windowWidth();
        d3dpp.BackBufferHeight = this->windowHeight();
        ShowCursor(FALSE);
    }
    else
    {
        d3dpp.Windowed = TRUE;
    }
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    if (FAILED(this->_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                         &d3dpp, &this->_device)))
    {
        return false;
    }
    D3DXMATRIX projection;
    D3DXMatrixOrthoLH(&projection, this->windowWidth(), this->windowHeight(), 0.1f, 1000.0f);
    this->_device->SetTransform(D3DTS_PROJECTION, &projection);
    this->_device->SetRenderState(D3DRS_LIGHTING, FALSE);
    this->_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    this->_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    this->_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    this->_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    this->_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    this->_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    return true;
}

void Framework::render()
{
    this->_currentTime = timeGetTime();
    if ((this->_currentTime - this->_lastTime) * 61 > 1000)
    {
        int past = this->_currentTime - this->_lastTime;
        if (NULL == this->_device)
        {
            return;
        }
        this->_device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
        if (SUCCEEDED(this->_device->BeginScene()))
        {
            this->sceneController()->act(past);
            this->sceneController()->render();
            this->_device->EndScene();
        }
        this->_device->Present(NULL, NULL, NULL, NULL);
        ++this->_frameCount;
        if (this->_currentTime - this->_lastSecondTime > 1000)
        {
            this->_fps = 1000.0f * this->_frameCount / (this->_currentTime - this->_lastSecondTime);
            this->_lastSecondTime = this->_currentTime;
            this->_frameCount = 0;
        }
        this->_lastTime = this->_currentTime;
    }
}

void Framework::messageLoop()
{
    MSG msg;
    this->_lastTime = timeGetTime();
    this->_lastSecondTime = this->_lastTime;
    this->_frameCount = 0;
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

int Framework::windowHalfWidth() const
{
    return this->_windowWidth >> 1;
}

int Framework::windowHalfHeight() const
{
    return this->_windowHeight >> 1;
}

Sprite2DController* Framework::spriteController() const
{
    return this->_spriteController;
}

WidgetController* Framework::widgetController() const
{
    return this->_widgetController;
}

SceneController* Framework::sceneController() const
{
    return this->_sceneController;
}

KeyState* Framework::keyState() const
{
    return this->_keyState;
}

MouseState* Framework::mouseState() const
{
    return this->_mouseState;
}

void Framework::keyPressEvent(const KeyState::Key key)
{
    this->_keyState->press(key);
    this->_sceneController->keyPressEvent(key);
}

void Framework::keyReleaseEvent(const KeyState::Key key)
{
    this->_keyState->release(key);
    this->_sceneController->keyReleaseEvent(key);
}

void Framework::mousePressEvent(const MouseState::Key key, int x, int y)
{
    this->_mouseState->press(key);
    this->_mouseState->setPos(x, y);
    this->_sceneController->mousePressEvent(key, x, y);
}

void Framework::mouseReleaseEvent(const MouseState::Key key, int x, int y)
{
    this->_mouseState->release(key);
    this->_mouseState->setPos(x, y);
    this->_sceneController->mouseReleaseEvent(key, x, y);
}

void Framework::mouseMoveEvent(int x, int y)
{
    this->_mouseState->setPos(x, y);
    this->_sceneController->mouseMoveEvent(x, y);
}

float Framework::fps() const
{
    return this->_fps;
}
