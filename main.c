#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>

const float EPS = 1e-6;
const float PI = acos(-1.0);
const char* WINDOW_CLASS_NAME = "ZSTG";
const char* WINDOW_CAPTION = "ZSTG 1";
const int WINDOW_POSITION_X = 50;
const int WINDOW_POSITION_Y = 50;
const int WINDOW_SIZE_WIDTH = 800;
const int WINDOW_SIZE_HEIGHT = 600;
const float GAME_SIZE_WIDTH = 600;
const float GAME_SIZE_HEIGHT = 400;

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;

enum ObservedKeys {
    GAME_KEY_LEFT,
    GAME_KEY_RIGHT,
    GAME_KEY_UP,
    GAME_KEY_DOWN,
    GAME_KEY_SHIFT,
    GAME_KEY_CONTROL,
    GAME_KEY_SPACE,
    GAME_KEY_Z,
    GAME_KEY_X,
    GAME_KEY_C,
    GAME_KEY_NULL,
    GAME_KEY_NUM
};
int isKeyDown[GAME_KEY_NUM];

struct Bullet {
    float x, y;
    float angle;
    float speed;
    int initTime;
    int logic;
    union extra {
        struct LinearAcceleration {
            float acceleration;
            float maxSpeed;
        };
    };
};

struct Bullet IBullet_Construct() {
    struct Bullet bullet;
    bullet.x = GAME_SIZE_WIDTH / 2;
    bullet.y = GAME_SIZE_HEIGHT / 2;
    bullet.angle = - PI / 2;
    bullet.speed = 0.02;
    bullet.initTime = 800;
    bullet.logic = 0;
    return bullet;
}

void initD3D(HWND hWnd) {
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    IDirect3D9_CreateDevice(g_pD3D, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice);
}

void render() {
    IDirect3DDevice9_Clear(g_pd3dDevice, 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    IDirect3DDevice9_BeginScene(g_pd3dDevice);
    IDirect3DDevice9_EndScene(g_pd3dDevice);
    IDirect3DDevice9_Present(g_pd3dDevice, NULL, NULL, NULL, NULL);
}

int getKey(WPARAM wParam) {
    switch (wParam) {
    case VK_LEFT:
        return GAME_KEY_LEFT;
    case VK_RIGHT:
        return GAME_KEY_RIGHT;
    case VK_UP:
        return GAME_KEY_UP;
    case VK_DOWN:
        return GAME_KEY_DOWN;
    case VK_SHIFT:
        return GAME_KEY_SHIFT;
    case VK_CONTROL:
        return GAME_KEY_CONTROL;
    case VK_RETURN:
    case VK_SPACE:
        return GAME_KEY_SPACE;
    case 'Z':
        return GAME_KEY_Z;
    case 'X':
        return GAME_KEY_X;
    case 'C':
        return GAME_KEY_C;
    }
    return GAME_KEY_NULL;
}

void keyDown(WPARAM wParam) {
    isKeyDown[getKey(wParam)] = 1;
}

void keyUp(WPARAM wParam) {
    isKeyDown[getKey(wParam)] = 0;
}

LRESULT WINAPI messageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_KEYDOWN:
        keyDown(wParam);
        break;
    case WM_KEYUP:
        keyUp(wParam);
        break;
    case WM_PAINT:
        render();
        ValidateRect(hWnd, NULL);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void createWindow() {
    WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_CLASSDC, messageProcess, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, WINDOW_CLASS_NAME, NULL};
    RegisterClassEx(&wc);
    HWND hWnd = CreateWindow(WINDOW_CLASS_NAME, WINDOW_CAPTION, WS_OVERLAPPEDWINDOW, WINDOW_POSITION_X, WINDOW_POSITION_Y, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, NULL, NULL, wc.hInstance, NULL);
    initD3D(hWnd);
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);
}

void messageLoop() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

int main() {
    createWindow();
    messageLoop();
    return 0;
}
