#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

LPDIRECT3D9         g_pD3D = NULL;
LPDIRECT3DDEVICE9   g_pd3dDevice = NULL;

int initD3D(HWND hWnd) {
    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) {
        return -1;
    }
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    if (FAILED(IDirect3D9_CreateDevice(g_pD3D, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                       D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                       &d3dpp, &g_pd3dDevice))) {
        return -1;
    }
    return 0;
}

void cleanUp() {
    if (g_pd3dDevice != NULL) {
        IDirect3DDevice9_Release(g_pd3dDevice);
    }
    if (g_pD3D != NULL) {
        IDirect3D9_Release(g_pD3D);
    }
}

void render() {
    if (NULL == g_pd3dDevice) {
        return;
    }
    IDirect3DDevice9_Clear(g_pd3dDevice, 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0);
    if (SUCCEEDED(IDirect3DDevice9_BeginScene(g_pd3dDevice))) {
        IDirect3DDevice9_EndScene(g_pd3dDevice);
    }
    IDirect3DDevice9_Present(g_pd3dDevice, NULL, NULL, NULL, NULL);
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch( msg ) {
    case WM_DESTROY:
        cleanUp();
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        render();
        ValidateRect(hWnd, NULL);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) {
    WNDCLASSEX wc = {
        sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
        "ZSTG", NULL
    };
    RegisterClassEx(&wc);
    HWND hWnd = CreateWindow("ZSTG", "ZSTG 1",
                             WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
                             NULL, NULL, wc.hInstance, NULL );
    if (SUCCEEDED(initD3D(hWnd))) {
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    UnregisterClass("STG", wc.hInstance);
    return 0;
}
