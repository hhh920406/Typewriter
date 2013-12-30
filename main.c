#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>

#define D3DFVF D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1

const char* WINDOW_CLASS_NAME = "Ant";
const char* WINDOW_CAPTION = "Ant";
const int WINDOW_POSITION_X = 50;
const int WINDOW_POSITION_Y = 50;
const int WINDOW_SIZE_WIDTH = 800;
const int WINDOW_SIZE_HEIGHT = 600;
const int RECT_LENGTH = 5;

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;

struct stD3DVertex {
    float x, y, z;
    unsigned long color;
    float tu, tv;
};

int totalFood;
int totalRed;
int totalBlue;

LPDIRECT3DVERTEXBUFFER9 createRect(int r, int g, int b) {
    void *ptr;
    struct stD3DVertex data[] = {
        {RECT_LENGTH, -RECT_LENGTH, 0.5f, D3DCOLOR_XRGB(r, g, b), 1.0f, 0.0f},
        {RECT_LENGTH, RECT_LENGTH, 0.5f, D3DCOLOR_XRGB(r, g, b), 1.0f, 1.0f},
        {-RECT_LENGTH, -RECT_LENGTH, 0.5f, D3DCOLOR_XRGB(r, g, b), 0.0f, 0.0f},
        {-RECT_LENGTH, RECT_LENGTH, 0.5f, D3DCOLOR_XRGB(r, g, b), 0.0f, 1.0f},
    };
    LPDIRECT3DVERTEXBUFFER9 rect;
    IDirect3DDevice9_CreateVertexBuffer(g_pd3dDevice, sizeof(data), 0, D3DFVF, D3DPOOL_DEFAULT, &rect, NULL);
    IDirect3DVertexBuffer9_Lock(rect, 0, sizeof(data), (void**)&ptr, 0);
    memcpy(ptr, data, sizeof(data));
    IDirect3DVertexBuffer9_Unlock(rect);
    return rect;
}

LPDIRECT3DVERTEXBUFFER9 bufferRedAnt;
LPDIRECT3DVERTEXBUFFER9 bufferBlueAnt;
LPDIRECT3DVERTEXBUFFER9 bufferFood;

struct Position {
    int x, y;
};

int shiftX(struct Position pos) {
    return pos.x - (WINDOW_SIZE_WIDTH >> 1);
}

int shiftY(struct Position pos) {
    return pos.y - (WINDOW_SIZE_HEIGHT >> 1);
}

struct Food {
    struct Position pos;
    int age;
};

struct Food createFood() {
    struct Food food;
    ++totalFood;
    food.pos.x = rand() % WINDOW_SIZE_WIDTH;
    food.pos.y = rand() % WINDOW_SIZE_HEIGHT;
    food.age = 0;
    return food;
}

enum Dir {
    UP, RIGHT, DOWN, LEFT
};

struct Ant {
    struct Position pos;
    int hunger;
    enum Dir dir;
};

struct Ant createAnt() {
    struct Ant ant;
    ant.pos.x = rand() % WINDOW_SIZE_WIDTH;
    ant.pos.y = rand() % WINDOW_SIZE_HEIGHT;
    ant.hunger = 0;
    ant.dir = rand() % 4;
    return ant;
}

#define MAX_FOOD 2038
#define MAX_ANT 2038
struct Food food[MAX_FOOD + 10];
struct Ant redAnt[MAX_ANT + 10];
struct Ant blueAnt[MAX_ANT + 10];
int foodNum;
int redAntNum;
int blueAntNum;

void initAnt() {
    int i;
    for (i = 0; i < 100; ++i) {
        food[i] = createFood();
    }
    for (i = 0; i < 10; ++i) {
        redAnt[i] = createAnt();
        blueAnt[i] = createAnt();
    }
    foodNum = 100;
    redAntNum = blueAntNum = 10;
}

void foodMove(struct Food *food) {
    ++food->age;
    if (food->age > 50) {
        if (rand() < 100) {
            if (foodNum < MAX_FOOD) {
                food[foodNum] = createFood();
                food[foodNum].pos.x = food->pos.x + (rand() % 400) - 200;
                food[foodNum].pos.y = food->pos.y + (rand() % 400) - 200;
                if (food[foodNum].pos.x < 0) {
                    food[foodNum].pos.x = 0;
                } else if (food[foodNum].pos.x > WINDOW_SIZE_WIDTH) {
                    food[foodNum].pos.x = WINDOW_SIZE_WIDTH;
                }
                if (food[foodNum].pos.y < 0) {
                    food[foodNum].pos.y = 0;
                } else if (food[foodNum].pos.y > WINDOW_SIZE_HEIGHT) {
                    food[foodNum].pos.y = WINDOW_SIZE_HEIGHT;
                }
                ++foodNum;
                food->age = 0;
            }
        }
    }
}

const int MOVE_SPEED = 1;

void randomWalk(struct Ant *ant) {
    switch (rand() % 50) {
    case 0:
        ant->dir = (ant->dir + 1) % 4;
        break;
    case 1:
        ant->dir = (ant->dir + 3) % 4;
        break;
    }
    switch (ant->dir) {
    case UP:
        ant->pos.y += MOVE_SPEED;
        break;
    case DOWN:
        ant->pos.y -= MOVE_SPEED;
        break;
    case LEFT:
        ant->pos.x -= MOVE_SPEED;
        break;
    case RIGHT:
        ant->pos.x += MOVE_SPEED;
        break;
    }
    if (ant->pos.x < 0) {
        ant->pos.x = 0;
    } else if (ant->pos.x > WINDOW_SIZE_WIDTH) {
        ant->pos.x = WINDOW_SIZE_WIDTH;
    }
    if (ant->pos.y < 0) {
        ant->pos.y = 0;
    } else if (ant->pos.y > WINDOW_SIZE_HEIGHT) {
        ant->pos.y = WINDOW_SIZE_HEIGHT;
    }
    ++ant->hunger;
}

void deleteFood(int i) {
    if (foodNum > 0) {
        food[i] = food[foodNum--];
    }
}

void deleteRedAnt(int i) {
    if (redAntNum > 0) {
        redAnt[i] = redAnt[redAntNum--];
    }
}

void deleteBlueAnt(int i) {
    if (blueAntNum > 0) {
        blueAnt[i] = blueAnt[blueAntNum--];
    }
}

int dist(struct Position a, struct Position b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void findFood(struct Ant *ant) {
    int i;
    for (i = 0; i < foodNum; ++i) {
        if (dist(ant->pos, food[i].pos) < RECT_LENGTH * RECT_LENGTH) {
            ant->hunger -= 1100;
            deleteFood(i);
            break;
        }
    }
}

int redAntMove(struct Ant *ant) {
    randomWalk(ant);
    findFood(ant);
    if (ant->hunger > 2000) {
        if (rand() < 100) {
            return -1;
        }
    }
    if (ant->hunger < -300) {
        if (redAntNum < MAX_ANT) {
            redAnt[redAntNum] = createAnt();
            ++totalRed;
            redAnt[redAntNum].pos.x = ant->pos.x;
            redAnt[redAntNum].pos.y = ant->pos.y;
            ++redAntNum;
            if (redAntNum > 100) {
                ant->hunger += 100;
            } else {
                ant->hunger += 5;
            }
        }
    }
    return 0;
}

int blueAntMove(struct Ant *ant) {
    randomWalk(ant);
    findFood(ant);
    if (ant->hunger > 2000) {
        if (rand() < 100) {
            return -1;
        }
    }
    if (ant->hunger < -300) {
        if (blueAntNum < MAX_ANT) {
            blueAnt[blueAntNum] = createAnt();
            ++totalBlue;
            blueAnt[blueAntNum].pos.x = ant->pos.x;
            blueAnt[blueAntNum].pos.y = ant->pos.y;
            ++blueAntNum;
            if (blueAntNum > 100) {
                ant->hunger += 100;
            } else {
                ant->hunger += 5;
            }
        }
    }
    return 0;
}

void fight() {
    int i, j;
    for (i = 0; i < redAntNum; ++i) {
        for (j = 0; j < blueAntNum; ++j) {
            if (dist(redAnt[i].pos, blueAnt[j].pos) < RECT_LENGTH * RECT_LENGTH) {
                redAnt[i].hunger += 20;
                blueAnt[i].hunger += 20;
            }
        }
    }
}

void initPixel() {
    bufferRedAnt = createRect(255, 0, 0);
    bufferBlueAnt = createRect(0, 0, 255);
    bufferFood = createRect(255, 255, 0);
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

void render() {
    int i;
    D3DXMATRIX translate;
    int currentTime = timeGetTime();
    if ((currentTime - lastTime) * 60 < 1000) {
        return;
    }
    IDirect3DDevice9_Clear(g_pd3dDevice, 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    IDirect3DDevice9_BeginScene(g_pd3dDevice);
    for (i = foodNum - 1; i >= 0; --i) {
        foodMove(&food[i]);
        D3DXMatrixTranslation(&translate, shiftX(food[i].pos), shiftY(food[i].pos), 1.0f);
        IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_WORLD, &translate);
        IDirect3DDevice9_SetStreamSource(g_pd3dDevice, 0, bufferFood, 0, sizeof(struct stD3DVertex));
        IDirect3DDevice9_SetFVF(g_pd3dDevice, D3DFVF);
        IDirect3DDevice9_DrawPrimitive(g_pd3dDevice, D3DPT_TRIANGLESTRIP, 0, 2);
    }
    fight();
    for (i = blueAntNum - 1; i >= 0; --i) {
        if (blueAntMove(&blueAnt[i])) {
            if (rand() % 3 == 0 && foodNum < MAX_FOOD) {
                food[foodNum] = createFood();
                food[foodNum].pos.x = blueAnt[i].pos.x;
                food[foodNum].pos.y = blueAnt[i].pos.y;
                ++foodNum;
            }
            deleteBlueAnt(i);
            continue;
        }
        D3DXMatrixTranslation(&translate, shiftX(blueAnt[i].pos), shiftY(blueAnt[i].pos), 1.0f);
        IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_WORLD, &translate);
        IDirect3DDevice9_SetStreamSource(g_pd3dDevice, 0, bufferBlueAnt, 0, sizeof(struct stD3DVertex));
        IDirect3DDevice9_SetFVF(g_pd3dDevice, D3DFVF);
        IDirect3DDevice9_DrawPrimitive(g_pd3dDevice, D3DPT_TRIANGLESTRIP, 0, 2);
    }
    for (i = redAntNum - 1; i >= 0; --i) {
        if (redAntMove(&redAnt[i])) {
            if (rand() % 3 == 0 && foodNum < MAX_FOOD) {
                food[foodNum] = createFood();
                food[foodNum].pos.x = redAnt[i].pos.x;
                food[foodNum].pos.y = redAnt[i].pos.y;
                ++foodNum;
            }
            deleteRedAnt(i);
            continue;
        }
        D3DXMatrixTranslation(&translate, shiftX(redAnt[i].pos), shiftY(redAnt[i].pos), 1.0f);
        IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_WORLD, &translate);
        IDirect3DDevice9_SetStreamSource(g_pd3dDevice, 0, bufferRedAnt, 0, sizeof(struct stD3DVertex));
        IDirect3DDevice9_SetFVF(g_pd3dDevice, D3DFVF);
        IDirect3DDevice9_DrawPrimitive(g_pd3dDevice, D3DPT_TRIANGLESTRIP, 0, 2);
    }
    printf("Food: %d Red: %d Blue: %d\t", foodNum, redAntNum, blueAntNum);
    printf("Food: %d Red: %d Blue: %d\n", totalFood, totalRed, totalBlue);
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
    initAnt();
    messageLoop();
    return 0;
}
