#include "Framework.h"

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
        return 0;
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

void Framework::init()
{
    this->_window =
    {
        sizeof(WNDCLASSEX), CS_CLASSDC, messageProcess, 0L, 0L,
        GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
        "ZSTG", NULL
    };
    RegisterClassEx(&this->_window);
    HWND hWnd = CreateWindow("ZSTG", "ZSTG",
                             WS_OVERLAPPEDWINDOW, 100, 100, 960, 720,
                             NULL, NULL, this->_window.hInstance, NULL);
    if (SUCCEEDED(this->initD3D(hWnd)))
    {
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);
    }
}

HRESULT Framework::initD3D(HWND hWnd)
{
    if (NULL == (this->_d3d = Direct3DCreate9(D3D_SDK_VERSION)))
    {
        return E_FAIL;
    }
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    if (FAILED(this->_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                         &d3dpp, &this->_device)))
    {
        return E_FAIL;
    }
    return S_OK;
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
        this->_device->EndScene();
    }
    this->_device->Present(NULL, NULL, NULL, NULL);
}

void Framework::messageLoop()
{
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnregisterClass("ZSTG", this->_window.hInstance);
}
