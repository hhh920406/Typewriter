#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>

#define D3DFVF D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1

const char* WINDOW_CLASS_NAME = "Spore";
const char* WINDOW_CAPTION = "Spore";
const int WINDOW_POSITION_X = 0;
const int WINDOW_POSITION_Y = 0;
#define WINDOW_SIZE_WIDTH 1000
#define WINDOW_SIZE_HEIGHT 1000
const int RECT_LENGTH = 15;
#define MAX_SPORE_NUM 10000

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;

struct stD3DVertex {
    float x, y, z;
    unsigned long color;
    float tu, tv;
};

LPDIRECT3DVERTEXBUFFER9 createHouse(int r, int g, int b) {
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

LPDIRECT3DVERTEXBUFFER9 createCenter() {
    void *ptr;
    struct stD3DVertex data[] = {
        {RECT_LENGTH, -RECT_LENGTH, 0.5f, D3DCOLOR_XRGB(220, 10, 10), 1.0f, 0.0f},
        {RECT_LENGTH, RECT_LENGTH, 0.5f, D3DCOLOR_XRGB(10, 220, 10), 1.0f, 1.0f},
        {-RECT_LENGTH, -RECT_LENGTH, 0.5f, D3DCOLOR_XRGB(200, 200, 10), 0.0f, 0.0f},
        {-RECT_LENGTH, RECT_LENGTH, 0.5f, D3DCOLOR_XRGB(50, 50, 255), 0.0f, 1.0f},
    };
    LPDIRECT3DVERTEXBUFFER9 rect;
    IDirect3DDevice9_CreateVertexBuffer(g_pd3dDevice, sizeof(data), 0, D3DFVF, D3DPOOL_DEFAULT, &rect, NULL);
    IDirect3DVertexBuffer9_Lock(rect, 0, sizeof(data), (void**)&ptr, 0);
    memcpy(ptr, data, sizeof(data));
    IDirect3DVertexBuffer9_Unlock(rect);
    return rect;
}

LPDIRECT3DVERTEXBUFFER9 createSpore(int r, int g, int b) {
    void *ptr;
    struct stD3DVertex data[] = {
        {2.0f, -2.0f, 0.5f, D3DCOLOR_XRGB(r, g, b), 1.0f, 0.0f},
        {2.0f, 2.0f, 0.5f, D3DCOLOR_XRGB(r, g, b), 1.0f, 1.0f},
        {-2.0f, -2.0f, 0.5f, D3DCOLOR_XRGB(r, g, b), 0.0f, 0.0f},
        {-2.0f, 2.0f, 0.5f, D3DCOLOR_XRGB(r, g, b), 0.0f, 1.0f},
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

#define HOUSE_NUM 9
#define HOUSE_CAPACITY 100

struct House {
    struct Position pos;
    int capacity;
    int currentNum;
    double food;
    int sporeNum;
    int spore[MAX_SPORE_NUM];
} house[HOUSE_NUM][HOUSE_NUM];

enum SporeColor {
    SPORE_RED, SPORE_GREEN, SPORE_BLUE, SPORE_YELLOW, SPORE_NUM
};

int sporeAge[SPORE_NUM] = {200000, 190000, 220000, 200000};
int sporeCreate[SPORE_NUM] = {2000, 1900, 1800, 1700};
int sporeLife[SPORE_NUM] = {1500, 1400, 1300, 1200};
int sporeLeave[SPORE_NUM] = {11, 21, 31, 41};
double sporeSpeed[SPORE_NUM] = {1.6, 1.7, 1.8, 1.9};

struct Spore {
    struct Position pos;
    int age;
    int life;
    int isRandomWalking;
    double walkX;
    double walkY;
    int houseX;
    int houseY;
    int characterX;
    int characterY;
    double angle;
    enum SporeColor color;
} spore[MAX_SPORE_NUM];
int sporeNum;

LPDIRECT3DVERTEXBUFFER9 houseBuffer[HOUSE_NUM][HOUSE_NUM];
LPDIRECT3DVERTEXBUFFER9 sporeBuffer[SPORE_NUM];

#define INIT_FOOD 200000

void liveIn(int x, int y, int index) {
    house[x][y].spore[house[x][y].sporeNum++] = index;
    spore[index].isRandomWalking = 0;
    spore[index].houseX = x;
    spore[index].houseY = y;
}

void leave(int x, int y, int index) {
    int i;
    for (i = 0; i < house[x][y].sporeNum; ++i) {
        if (house[x][y].spore[i] == index) {
            spore[index].isRandomWalking = 1;
            house[x][y].spore[i] = house[x][y].spore[--house[x][y].sporeNum];
            break;
        }
    }
}

void breakHouse(int x, int y) {
    int i;
    for (i = house[x][y].sporeNum; i >= 0; --i) {
        spore[house[x][y].spore[i]].walkX = ((rand() * rand()) % 10000) / 10000.0 - 0.5;
        spore[house[x][y].spore[i]].walkY = ((rand() * rand()) % 10000) / 10000.0 - 0.5;
        leave(x, y, house[x][y].spore[i]);
    }
}

int isInside(int x, int y, int index) {
    return house[x][y].food > 0 && spore[index].pos.x >= house[x][y].pos.x - RECT_LENGTH && spore[index].pos.x <= house[x][y].pos.x + RECT_LENGTH && spore[index].pos.y >= house[x][y].pos.y - RECT_LENGTH && spore[index].pos.y <= house[x][y].pos.y + RECT_LENGTH;
}

void newSpore(int x, int y, enum SporeColor color) {
    if (sporeNum < MAX_SPORE_NUM) {
        spore[sporeNum].age = 0;
        spore[sporeNum].life = sporeLife[color];
        spore[sporeNum].isRandomWalking = 0;
        spore[sporeNum].walkX = 0.0;
        spore[sporeNum].walkY = 0.0;
        spore[sporeNum].houseX = x;
        spore[sporeNum].houseY = y;
        spore[sporeNum].characterX = (rand() % 10) + 1;
        spore[sporeNum].characterY = (rand() % 10) + 1;
        spore[sporeNum].angle = acos(-1.0) * ((rand() % 20000) / 10000.0);
        spore[sporeNum].color = color;
        spore[sporeNum].pos.x = house[x][y].pos.x;
        spore[sporeNum].pos.y = house[x][y].pos.y;
        liveIn(x, y, sporeNum);
        ++sporeNum;
    }
}

void deleteSpore(int index) {
    if (!spore[index].isRandomWalking) {
        leave(spore[index].houseX, spore[index].houseY, index);
        spore[index] = spore[--sporeNum];
        if (!spore[index].isRandomWalking) {
            leave(spore[index].houseX, spore[index].houseY, sporeNum);
            liveIn(spore[index].houseX, spore[index].houseY, index);
        }
    }
}

void initPixel() {
    int i, j, c, x, y;
    for (i = 0; i < HOUSE_NUM; ++i) {
        for (j = 0; j < HOUSE_NUM; ++j) {
            c = abs(i - 4) + abs(j - 4) + 10;
            house[i][j].pos.x = (i + 1) * 100;
            house[i][j].pos.y = (j + 1) * 100;
            house[i][j].capacity = HOUSE_CAPACITY;
            house[i][j].currentNum = 0;
            house[i][j].food = INIT_FOOD;
            house[i][j].sporeNum = 0;
            houseBuffer[i][j] = createHouse(255 - c * 4, 255 - c * 4, 255 - c * 4);
        }
    }
    house[4][4].capacity = MAX_SPORE_NUM;
    house[4][4].food *= 100;
    houseBuffer[4][4] = createCenter();
    for (i = 0; i < SPORE_NUM; ++i) {
        while (1) {
            x = rand() % HOUSE_NUM;
            y = rand() % HOUSE_NUM;
            if (house[x][y].sporeNum) {
                continue;
            }
            for (j = 0; j < 10; ++j) {
                newSpore(x, y, i);
            }
            break;
        }
    }
    sporeBuffer[SPORE_RED] = createSpore(220, 10, 10);
    sporeBuffer[SPORE_GREEN] = createSpore(10, 220, 10);
    sporeBuffer[SPORE_BLUE] = createSpore(50, 50, 255);
    sporeBuffer[SPORE_YELLOW] = createSpore(200, 200, 10);
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

int loadTime;
int maxLoad = 450;

int scaleTime;
int maxScale = 2000;

void render() {
    int i, j, k, l, countHouse = 0;
    double x, y, angle;
    D3DXMATRIX world;
    D3DXMATRIX translation;
    D3DXMATRIX scaling;
    D3DXMATRIX rotation;
    int currentTime = timeGetTime();
    if ((currentTime - lastTime) * 60 < 1000) {
        return;
    }
    IDirect3DDevice9_Clear(g_pd3dDevice, 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    IDirect3DDevice9_BeginScene(g_pd3dDevice);

    if (loadTime <= maxLoad) {
        D3DXMatrixScaling(&scaling, log(1.0 * maxLoad / loadTime + exp(1) - 1), log(1.0 * maxLoad / loadTime + exp(1) - 1), 1.0f);
        D3DXMatrixRotationZ(&rotation, log((maxLoad - loadTime) * 0.003 + 1));
        D3DXMatrixMultiply(&world, &scaling, &rotation);
        IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_VIEW, &world);
        ++loadTime;
    }

    for (i = 0; i < HOUSE_NUM; ++i) {
        for (j = 0; j < HOUSE_NUM; ++j) {
            countHouse += house[i][j].food > 0;
        }
    }
    if (countHouse <= 1) {
        if (scaleTime < maxScale) {
            ++scaleTime;
        }
        D3DXMatrixScaling(&scaling, 1.0 + scaleTime / 500.0, 1.0 + scaleTime / 500.0, 1.0f);
        IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_VIEW, &scaling);
    }

    for (i = 0; i < HOUSE_NUM; ++i) {
        for (j = 0; j < HOUSE_NUM; ++j) {
            D3DXMatrixTranslation(&translation, shiftX(house[i][j].pos), shiftY(house[i][j].pos), 1.0f);
            if (i == 4 && j == 4) {
                D3DXMatrixScaling(&scaling, sqrt(house[i][j].food / INIT_FOOD / 100), sqrt(house[i][j].food / INIT_FOOD / 100), 1.0f);
            } else {
                D3DXMatrixScaling(&scaling, sqrt(house[i][j].food / INIT_FOOD), sqrt(house[i][j].food / INIT_FOOD), 1.0f);
            }
            D3DXMatrixMultiply(&world, &scaling, &translation);
            IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_WORLD, &world);
            IDirect3DDevice9_SetStreamSource(g_pd3dDevice, 0, houseBuffer[i][j], 0, sizeof(struct stD3DVertex));
            IDirect3DDevice9_SetFVF(g_pd3dDevice, D3DFVF);
            IDirect3DDevice9_DrawPrimitive(g_pd3dDevice, D3DPT_TRIANGLESTRIP, 0, 2);
        }
    }

    // Kill
    for (i = 0; i < HOUSE_NUM; ++i) {
        for (j = 0; j < HOUSE_NUM; ++j) {
            if (i == 4 && j == 4) {
                continue;
            }
            for (k = 0; k < house[i][j].sporeNum; ++k) {
                for (l = k + 1; l < house[i][j].sporeNum; ++l) {
                    if (spore[house[i][j].spore[k]].color != spore[house[i][j].spore[l]].color) {
                        spore[house[i][j].spore[k]].life -= 10;
                        spore[house[i][j].spore[l]].life -= 10;
                    }
                }
            }
        }
    }

    // Dead
    for (i = sporeNum - 1; i >= 0; --i) {
        if (spore[i].life <= 0) {
            deleteSpore(i);
        } else if (spore[i].age > sporeAge[spore[i].color]) {
            if (rand() < 100) {
                deleteSpore(i);
            }
        } else if (spore[i].isRandomWalking && (spore[i].pos.x < 0 || spore[i].pos.x > WINDOW_SIZE_WIDTH || spore[i].pos.y < 0 || spore[i].pos.y > WINDOW_SIZE_HEIGHT)) {
            deleteSpore(i);
        }
    }

    // Leave
    for (i = 0; i < sporeNum; ++i) {
        if (!spore[i].isRandomWalking) {
            if (house[spore[i].houseX][spore[i].houseY].sporeNum > sporeLeave[spore[i].color]) {
                if (rand() < 200) {
                    leave(spore[i].houseX, spore[i].houseY, i);
                    spore[i].walkX = ((rand() * rand()) % 10000) / 10000.0 - 0.5;
                    spore[i].walkY = ((rand() * rand()) % 10000) / 10000.0 - 0.5;
                }
            }
        }
    }

    // Random walk
    for (i = 0; i < sporeNum; ++i) {
        if (spore[i].isRandomWalking) {
            spore[i].walkX += ((rand() % 10) - 5) / 10000.0;
            spore[i].walkY += ((rand() % 10) - 5) / 10000.0;
            spore[i].pos.x += spore[i].walkX * sporeSpeed[spore[i].color];
            spore[i].pos.y += spore[i].walkY * sporeSpeed[spore[i].color];
        }
    }

    // Live
    for (i = 0; i < sporeNum; ++i) {
        if (spore[i].isRandomWalking) {
            for (j = 0; j < HOUSE_NUM; ++j) {
                for (k = 0; k < HOUSE_NUM; ++k) {
                    if (house[j][k].sporeNum < house[j][k].capacity) {
                        if (isInside(j, k, i)) {
                            liveIn(j, k, i);
                        }
                    }
                }
            }
        }
    }

    // Birth
    for (i = sporeNum - 1; i >= 0; --i) {
        if (!spore[i].isRandomWalking) {
            if (spore[i].age > sporeCreate[spore[i].color]) {
                if (rand() < 100) {
                    newSpore(spore[i].houseX, spore[i].houseY, spore[i].color);
                }
            }
        }
    }

    // Grow
    for (i = 0; i < sporeNum; ++i) {
        ++spore[i].age;
        if (spore[i].isRandomWalking) {
            --spore[i].life;
        } else {
            if (house[spore[i].houseX][spore[i].houseY].food > 0) {
                --house[spore[i].houseX][spore[i].houseY].food;
            } else {
                breakHouse(spore[i].houseX, spore[i].houseY);
            }
        }
    }

    for (i = 0; i < sporeNum; ++i) {
        if (!spore[i].isRandomWalking) {
            x = house[spore[i].houseX][spore[i].houseY].pos.x + (RECT_LENGTH + 10) * cos(spore[i].characterX * spore[i].angle);
            y = house[spore[i].houseX][spore[i].houseY].pos.y + (RECT_LENGTH + 10) * sin(spore[i].characterY * spore[i].angle);
            if ((spore[i].pos.x - x) * (spore[i].pos.x - x) + (spore[i].pos.y - y) * (spore[i].pos.y - y) < sporeSpeed[spore[i].color] * sporeSpeed[spore[i].color]) {
                spore[i].pos.x = x;
                spore[i].pos.y = y;
                spore[i].angle += 0.005 + (rand() % 10) / 10000.0;
            } else {
                angle = atan2(y - spore[i].pos.y, x - spore[i].pos.x);
                spore[i].pos.x += sporeSpeed[spore[i].color] * cos(angle) * 0.9;
                spore[i].pos.y += sporeSpeed[spore[i].color] * sin(angle) * 0.9;
            }
        }
        D3DXMatrixTranslation(&translation, shiftX(spore[i].pos), shiftY(spore[i].pos), 1.0f);
        if (spore[i].isRandomWalking) {
            D3DXMatrixScaling(&scaling, 0.5f, 0.5f, 1.0f);
        } else if (spore[i].age >= sporeCreate[spore[i].color]) {
            D3DXMatrixScaling(&scaling, 1.3f, 1.3f, 1.0f);
        } else {
            D3DXMatrixScaling(&scaling, 1.0f, 1.0f, 1.0f);
        }
        D3DXMatrixMultiply(&world, &scaling, &translation);
        IDirect3DDevice9_SetTransform(g_pd3dDevice, D3DTS_WORLD, &world);
        IDirect3DDevice9_SetStreamSource(g_pd3dDevice, 0, sporeBuffer[spore[i].color], 0, sizeof(struct stD3DVertex));
        IDirect3DDevice9_SetFVF(g_pd3dDevice, D3DFVF);
        IDirect3DDevice9_DrawPrimitive(g_pd3dDevice, D3DPT_TRIANGLESTRIP, 0, 2);
    }

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
