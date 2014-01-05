#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>

#define D3DFVF D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1

const char* WINDOW_CLASS_NAME = "Universe";
const char* WINDOW_CAPTION = "Universe";
const int WINDOW_POSITION_X = 50;
const int WINDOW_POSITION_Y = 50;
#define WINDOW_SIZE_WIDTH 800
#define WINDOW_SIZE_HEIGHT 800
const int RECT_LENGTH = 5;

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

LPDIRECT3DVERTEXBUFFER9 createDust(int r, int g, int b) {
    void *ptr;
    struct stD3DVertex data[] = {
        {1.0f, -1.0f, 0.5f, D3DCOLOR_XRGB(r, g, b), 1.0f, 0.0f},
        {1.0f, 1.0f, 0.5f, D3DCOLOR_XRGB(r, g, b), 1.0f, 1.0f},
        {-1.0f, -1.0f, 0.5f, D3DCOLOR_XRGB(r, g, b), 0.0f, 0.0f},
        {-1.0f, 1.0f, 0.5f, D3DCOLOR_XRGB(r, g, b), 0.0f, 1.0f},
    };
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

LPDIRECT3DVERTEXBUFFER9 solar;
LPDIRECT3DVERTEXBUFFER9 earth;
LPDIRECT3DVERTEXBUFFER9 moon;
LPDIRECT3DVERTEXBUFFER9 dust[4];

void initPixel() {
    solar = createRect(190, 86, 25);
    earth = createRect(20, 53, 230);
    moon = createRect(220, 255, 230);
    dust[0] = createDust(220, 200, 200);
    dust[1] = createDust(200, 220, 200);
    dust[2] = createDust(200, 200, 220);
    dust[3] = createDust(220, 220, 200);
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

double earthAngle;
double moonAngle;

struct Position solarPos = {WINDOW_SIZE_WIDTH >> 1, WINDOW_SIZE_HEIGHT >> 1};
struct Position earthPos;
struct Position moonPos;

#define MAX_DUST_NUM 10000
int dustNum;
struct Position dustPos[MAX_DUST_NUM];
struct Position dustSpeed[MAX_DUST_NUM];
int dustColor[MAX_DUST_NUM];

double solarMass = 50;
double earthMass = 10;
double moonMass = 1;

int escapeNum;
int solarNum;
int earthNum;
int moonNum;

double dustAngle;
int dustDir;

double dustSpeedInit;
int dustSpeedDir;

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
    double solarRadius;
    double earthRadius;
    double moonRadius;
    int currentTime = timeGetTime();
    if ((currentTime - lastTime) * 60 < 1000) {
        return;
    }
    IDirect3DDevice9_Clear(g_pd3dDevice, 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    IDirect3DDevice9_BeginScene(g_pd3dDevice);

    earthPos.x = solarPos.x + 250.0 * cos(earthAngle);
    earthPos.y = solarPos.y + 250.0 * sin(earthAngle);
    earthAngle -= sqrt(sqrt(solarMass)) / 300.0f;

    moonPos.x = earthPos.x + 50.0 * cos(moonAngle);
    moonPos.y = earthPos.y + 50.0 * sin(moonAngle);
    moonAngle += sqrt(sqrt(solarMass)) / 55.0f;

    solarRadius = sqrt(solarMass) / 2.0 * RECT_LENGTH;
    earthRadius = sqrt(earthMass) / 2.0 * RECT_LENGTH;
    moonRadius = sqrt(moonMass) / 2.0 * RECT_LENGTH;

    dustAngle = PI / 2 - atan2(moonPos.y, moonPos.x);
    dustSpeedInit = 3.0;
    while (dustNum < MAX_DUST_NUM) {
        if (rand() > 30000) {
            break;
        }
        if (rand() & 1) {
            if (rand() & 1) {
                dustPos[dustNum].x = - (rand() % 1000) / 30.0;
                dustPos[dustNum].y = - (rand() % 1000) / 30.0;
                dustSpeed[dustNum].x = cos(dustAngle) * dustSpeedInit + (rand() % 1000) / 5800.0;
                dustSpeed[dustNum].y = sin(dustAngle) * dustSpeedInit + (rand() % 1000) / 5800.0;
                dustColor[dustNum] = 0;
            } else {
                dustPos[dustNum].x = WINDOW_SIZE_WIDTH + (rand() % 1000) / 30.0;
                dustPos[dustNum].y = - (rand() % 1000) / 30.0;
                dustSpeed[dustNum].x = cos(PI / 2 + dustAngle) * dustSpeedInit - (rand() % 1000) / 5800.0;
                dustSpeed[dustNum].y = sin(PI / 2 + dustAngle) * dustSpeedInit + (rand() % 1000) / 5800.0;
                dustColor[dustNum] = 1;
            }
        } else {
            if (rand() & 1) {
                dustPos[dustNum].x = WINDOW_SIZE_WIDTH + (rand() % 1000) / 30.0;
                dustPos[dustNum].y = WINDOW_SIZE_HEIGHT + (rand() % 1000) / 30.0;
                dustSpeed[dustNum].x = - (cos(dustAngle) * dustSpeedInit + (rand() % 1000) / 5800.0);
                dustSpeed[dustNum].y = - (sin(dustAngle) * dustSpeedInit + (rand() % 1000) / 5800.0);
                dustColor[dustNum] = 2;
            } else {
                dustPos[dustNum].x = - (rand() % 1000) / 30.0;
                dustPos[dustNum].y = WINDOW_SIZE_HEIGHT + (rand() % 1000) / 30.0;
                dustSpeed[dustNum].x = cos(dustAngle - PI / 2) * dustSpeedInit + (rand() % 1000) / 5800.0;
                dustSpeed[dustNum].y = sin(dustAngle - PI / 2) * dustSpeedInit - (rand() % 1000) / 5800.0;
                dustColor[dustNum] = 3;
            }
        }
        ++dustNum;
    }

    for (i = dustNum - 1; i >= 0; --i) {
        if (dustPos[i].x < -200 || dustPos[i].y < - 200 ||
            dustPos[i].x > 200 + WINDOW_SIZE_WIDTH ||
            dustPos[i].y > 200 + WINDOW_SIZE_HEIGHT) {
            --dustNum;
            dustPos[i] = dustPos[dustNum];
            dustSpeed[i] = dustSpeed[dustNum];
            dustColor[i] = dustColor[dustNum];
            ++escapeNum;
            continue;
        }
        if (dist(dustPos[i], solarPos) < solarRadius * solarRadius) {
            solarMass += 0.8 / solarMass;
            --dustNum;
            dustPos[i] = dustPos[dustNum];
            dustSpeed[i] = dustSpeed[dustNum];
            dustColor[i] = dustColor[dustNum];
            ++solarNum;
            continue;
        }
        if (dist(dustPos[i], earthPos) < earthRadius * earthRadius) {
            earthMass += 0.8 / earthMass;
            --dustNum;
            dustPos[i] = dustPos[dustNum];
            dustSpeed[i] = dustSpeed[dustNum];
            dustColor[i] = dustColor[dustNum];
            ++earthNum;
            continue;
        }
        if (dist(dustPos[i], moonPos) < moonRadius * moonRadius) {
            moonMass += 0.7 / solarMass;
            --dustNum;
            dustPos[i] = dustPos[dustNum];
            dustSpeed[i] = dustSpeed[dustNum];
            dustColor[i] = dustColor[dustNum];
            ++moonNum;
            continue;
        }
        forceX = 0.0;
        forceY = 0.0;

        angle = atan2(solarPos.y - dustPos[i].y, solarPos.x - dustPos[i].x);
        dist2 = dist(solarPos, dustPos[i]);
        force = solarMass / dist2;
        forceX += force * cos(angle);
        forceY += force * sin(angle);

        angle = atan2(earthPos.y - dustPos[i].y, earthPos.x - dustPos[i].x);
        dist2 = dist(earthPos, dustPos[i]);
        force = earthMass / dist2;
        forceX += force * cos(angle);
        forceY += force * sin(angle);

        angle = atan2(moonPos.y - dustPos[i].y, moonPos.x - dustPos[i].x);
        dist2 = dist(moonPos, dustPos[i]);
        force = moonMass / dist2;
        forceX += force * cos(angle);
        forceY += force * sin(angle);

        dustSpeed[i].x += forceX * 10.0;
        dustSpeed[i].y += forceY * 10.0;
        dustPos[i].x += dustSpeed[i].x;
        dustPos[i].y += dustSpeed[i].y;
        D3DXMatrixTranslation(&translation, shiftX(dustPos[i]), shiftY(dustPos[i]), 1.0f);
        IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_WORLD, &translation);
        IDirect3DDevice9_SetStreamSource(g_pd3dDevice, 0, dust[dustColor[i]], 0, sizeof(struct stD3DVertex));
        IDirect3DDevice9_SetFVF(g_pd3dDevice, D3DFVF);
        IDirect3DDevice9_DrawPrimitive(g_pd3dDevice, D3DPT_TRIANGLESTRIP, 0, 2);
    }

    D3DXMatrixTranslation(&translation, shiftX(moonPos), shiftY(moonPos), 1.0f);
    D3DXMatrixScaling(&scaling, sqrt(moonMass) / 2.0, sqrt(moonMass) / 2.0, 1.0f);
    D3DXMatrixMultiply(&world, &scaling, &translation);
    IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_WORLD, &world);
    IDirect3DDevice9_SetStreamSource(g_pd3dDevice, 0, moon, 0, sizeof(struct stD3DVertex));
    IDirect3DDevice9_SetFVF(g_pd3dDevice, D3DFVF);
    IDirect3DDevice9_DrawPrimitive(g_pd3dDevice, D3DPT_TRIANGLEFAN, 0, 36);

    D3DXMatrixTranslation(&translation, shiftX(earthPos), shiftY(earthPos), 1.0f);
    D3DXMatrixScaling(&scaling, sqrt(earthMass) / 2.0, sqrt(earthMass) / 2.0, 1.0f);
    D3DXMatrixMultiply(&world, &scaling, &translation);
    IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_WORLD, &world);
    IDirect3DDevice9_SetStreamSource(g_pd3dDevice, 0, earth, 0, sizeof(struct stD3DVertex));
    IDirect3DDevice9_SetFVF(g_pd3dDevice, D3DFVF);
    IDirect3DDevice9_DrawPrimitive(g_pd3dDevice, D3DPT_TRIANGLEFAN, 0, 36);

    D3DXMatrixTranslation(&translation, shiftX(solarPos), shiftY(solarPos), 1.0f);
    D3DXMatrixScaling(&scaling, sqrt(solarMass) / 2.0, sqrt(solarMass) / 2.0, 1.0f);
    D3DXMatrixMultiply(&world, &scaling, &translation);
    IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_WORLD, &world);
    IDirect3DDevice9_SetStreamSource(g_pd3dDevice, 0, solar, 0, sizeof(struct stD3DVertex));
    IDirect3DDevice9_SetFVF(g_pd3dDevice, D3DFVF);
    IDirect3DDevice9_DrawPrimitive(g_pd3dDevice, D3DPT_TRIANGLEFAN, 0, 36);

    IDirect3DDevice9_EndScene(g_pd3dDevice);
    IDirect3DDevice9_Present(g_pd3dDevice, NULL, NULL, NULL, NULL);
}

LRESULT WINAPI messageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
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
