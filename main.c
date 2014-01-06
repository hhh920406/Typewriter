#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>

#define D3DFVF D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1

const char* WINDOW_CLASS_NAME = "Stars";
const char* WINDOW_CAPTION = "Stars";
const int WINDOW_POSITION_X = 50;
const int WINDOW_POSITION_Y = 50;
#define WINDOW_SIZE_WIDTH 1024
#define WINDOW_SIZE_HEIGHT 768
const int RECT_LENGTH = 5;
#define MAX_STAR_NUM 100

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;

struct stD3DVertex {
    float x, y, z;
    unsigned long color;
    float tu, tv;
};

LPDIRECT3DVERTEXBUFFER9 createRect(int r, int g, int b) {
    int i;
    void *ptr;
    struct stD3DVertex data[38];
    double PI = acos(-1.0);
    for (i = 0; i <= 37; ++i) {
        if (i) {
            data[i].x = RECT_LENGTH * cos(PI / 18 * i);
            data[i].y = RECT_LENGTH * sin(PI / 18 * i);
        } else {
            data[i].x = 0.0f;
            data[i].y = 0.0f;
        }
        data[i].z = 0.5f;
        data[i].color = D3DCOLOR_XRGB(r, g, b);
        data[i].tu = 0.0f;
        data[i].tv = 0.0f;
    }
    LPDIRECT3DVERTEXBUFFER9 rect;
    IDirect3DDevice9_CreateVertexBuffer(g_pd3dDevice, sizeof(data), 0, D3DFVF, D3DPOOL_DEFAULT, &rect, NULL);
    IDirect3DVertexBuffer9_Lock(rect, 0, sizeof(data), (void**)&ptr, 0);
    memcpy(ptr, data, sizeof(data));
    IDirect3DVertexBuffer9_Unlock(rect);
    return rect;
}

struct Position {
    double x, y;
};

double shiftX(struct Position pos) {
    return pos.x - (WINDOW_SIZE_WIDTH >> 1);
}

double shiftY(struct Position pos) {
    return pos.y - (WINDOW_SIZE_HEIGHT >> 1);
}

double dist(struct Position a, struct Position b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

LPDIRECT3DVERTEXBUFFER9 starBuffer;

void initPixel() {
    starBuffer = createRect(249, 249, 249);
}

void initD3D(HWND hWnd) {
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    IDirect3D9_CreateDevice(g_pD3D, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice);
    D3DXMATRIX projection;
    D3DXMatrixOrthoLH(&projection, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, 0.1f, 1000.0f);
    IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_PROJECTION, &projection);
    IDirect3DDevice9_SetRenderState(g_pd3dDevice, D3DRS_LIGHTING, FALSE);
    IDirect3DDevice9_SetRenderState(g_pd3dDevice, D3DRS_CULLMODE, D3DCULL_NONE);
    IDirect3DDevice9_SetRenderState(g_pd3dDevice, D3DRS_ALPHABLENDENABLE, TRUE);
    IDirect3DDevice9_SetRenderState(g_pd3dDevice, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    IDirect3DDevice9_SetRenderState(g_pd3dDevice, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    IDirect3DDevice9_SetSamplerState(g_pd3dDevice, 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    IDirect3DDevice9_SetSamplerState(g_pd3dDevice, 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

int lastTime;

int starNum;
struct Position starPos[MAX_STAR_NUM];
struct Position starSpeed[MAX_STAR_NUM];
double mass[MAX_STAR_NUM];
double radius[MAX_STAR_NUM];

void deleteStar(int pos) {
    --starNum;
    starPos[pos] = starPos[starNum];
    starSpeed[pos] = starSpeed[starNum];
    mass[pos] = mass[starNum];
    radius[pos] = radius[starNum];
}

void render() {
    int i, j;
    double force;
    double forceX;
    double forceY;
    double angle;
    double dist2;
    double PI = acos(-1.0);
    D3DXMATRIX world;
    D3DXMATRIX translation;
    D3DXMATRIX scaling;
    int currentTime = timeGetTime();
    if ((currentTime - lastTime) * 60 < 1000) {
        return;
    }
    IDirect3DDevice9_Clear(g_pd3dDevice, 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    IDirect3DDevice9_BeginScene(g_pd3dDevice);

    for (i = 0; i < starNum; ++i) {
        radius[i] = sqrt(mass[i]) * RECT_LENGTH;
    }

    for (i = starNum - 1; i >= 0; --i) {
        for (j = starNum - 1; j > i; --j) {
            if (dist(starPos[i], starPos[j]) < 10.0 + (radius[i] - radius[j]) * (radius[i] - radius[j])) {
                if (mass[i] > mass[j]) {
                    mass[i] += mass[j];
                    starSpeed[i].x = (starSpeed[i].x * mass[i] + starSpeed[j].x * mass[j]) / (mass[i] + mass[j]);
                    starSpeed[i].y = (starSpeed[i].y * mass[i] + starSpeed[j].y * mass[j]) / (mass[i] + mass[j]);
                    deleteStar(j);
                    break;
                } else {
                    mass[j] += mass[i];
                    starSpeed[j].x = (starSpeed[i].x * mass[i] + starSpeed[j].x * mass[j]) / (mass[i] + mass[j]);
                    starSpeed[j].y = (starSpeed[i].y * mass[i] + starSpeed[j].y * mass[j]) / (mass[i] + mass[j]);
                    deleteStar(i);
                    --i;
                    break;
                }
            }
        }
    }

    for (i = 0; i < starNum; ++i) {
        forceX = forceY = 0.0;
        for (j = 0; j < starNum; ++j) {
            if (i != j) {
                dist2 = dist(starPos[i], starPos[j]);
                angle = atan2(starPos[j].y - starPos[i].y, starPos[j].x - starPos[i].x);
                force = mass[j] / (dist2 + 0.01);
                forceX += force * cos(angle);
                forceY += force * sin(angle);
            }
        }
        starSpeed[i].x += forceX / mass[i];
        starSpeed[i].y += forceY / mass[i];
        starPos[i].x += starSpeed[i].x;
        starPos[i].y += starSpeed[i].y;
    }

    for (i = 0; i < starNum; ++i) {
        D3DXMatrixTranslation(&translation, shiftX(starPos[i]), shiftY(starPos[i]), 1.0f);
        D3DXMatrixScaling(&scaling, sqrt(mass[i]), sqrt(mass[i]), 1.0f);
        D3DXMatrixMultiply(&world, &scaling, &translation);
        IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_WORLD, &world);
        IDirect3DDevice9_SetStreamSource(g_pd3dDevice, 0, starBuffer, 0, sizeof(struct stD3DVertex));
        IDirect3DDevice9_SetFVF(g_pd3dDevice, D3DFVF);
        IDirect3DDevice9_DrawPrimitive(g_pd3dDevice, D3DPT_TRIANGLEFAN, 0, 36);
    }

    IDirect3DDevice9_EndScene(g_pd3dDevice);
    IDirect3DDevice9_Present(g_pd3dDevice, NULL, NULL, NULL, NULL);
}

void restart() {
    int i;
    for (i = 0; i < MAX_STAR_NUM; ++i) {
        starPos[i].x = rand() % WINDOW_SIZE_WIDTH;
        starPos[i].y = rand() % WINDOW_SIZE_HEIGHT;
        starSpeed[i].x = 0.0;
        starSpeed[i].y = 0.0;
        mass[i] = 3.0;
    }
    starNum = MAX_STAR_NUM;
}

LRESULT WINAPI messageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_PAINT:
        render();
        ValidateRect(hWnd, NULL);
        break;
    case WM_KEYUP:
        restart();
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
    MSG message;
    lastTime = timeGetTime();
    while (message.message != WM_QUIT) {
        if (PeekMessage(&message, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        } else {
            render();
        }
    }
}

int main() {
    srand(time(NULL));
    createWindow();
    initPixel();
    messageLoop();
    return 0;
}
