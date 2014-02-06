/**
 * Tabu Search.
 * Solved all problems.
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXV = 1005;
const int MAXE = 400000 * 2;
const int INF = 0x7fffffff;
const int NBMAX = 1000000000;
const int TABU_STEP_LEN = 10;
const int TABU_COLOR_LEN = 5;

int n, m;
struct Edge
{
    int v, next;
} edge[MAXE];
int head[MAXV], edgeNum;
int degree[MAXV], maxDegree;

int color[MAXV], colorNum;
int visit[MAXV];
int same[MAXV], sameTotal;
int adjacentColor[MAXV];

int tabuStep[TABU_STEP_LEN];
int tsFront, tsRear;
bool stepValid[MAXV];

int tabuColor[MAXV][TABU_COLOR_LEN];
int tcFront[MAXV], tcRear[MAXV];
bool colorValid[MAXV][MAXV];

void clearEdge()
{
    edgeNum = 0;
    memset(head, -1, sizeof(head));
}

inline void addEdgeSub(int u, int v)
{
    edge[edgeNum].v = v;
    edge[edgeNum].next = head[u];
    head[u] = edgeNum++;
}

inline void addEdge(int u, int v)
{
    addEdgeSub(u, v);
    addEdgeSub(v, u);
}

void initColor(int u)
{
    for (int i = 0; i < colorNum; ++i)
    {
        visit[i] = 0;
    }
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].v;
        if (color[v] != -1)
        {
            ++visit[color[v]];
        }
    }
    int minIndex = 0;
    for (int i = 0; i < colorNum; ++i)
    {
        if (visit[i] < visit[minIndex])
        {
            minIndex = i;
        }
        if (!visit[i])
        {
            break;
        }
    }
    color[u] = minIndex;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].v;
        if (color[u] == color[v])
        {
            ++same[u];
            ++same[v];
            ++sameTotal;
        }
    }
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].v;
        if (color[v] == -1)
        {
            initColor(v);
        }
    }
}

bool tabuSearch()
{
    int nbiter = NBMAX;
    memset(stepValid, true, sizeof(stepValid));
    memset(colorValid, true, sizeof(colorValid));
    while (nbiter--)
    {
        // Pick the random node u.
        int maxSame = -1;
        int u = -1;
        for (int i = 0; i < n; ++i)
        {
            if (stepValid[i])
            {
                if (maxSame == -1 || same[i] > maxSame)
                {
                    maxSame = same[i];
                    u = i;
                }
            }
        }
        // Pick the random color c.
        int minSame = INF;
        int c = -1;
        for (int i = 0; i < colorNum; ++i)
        {
            adjacentColor[i] = 0;
        }
        for (int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].v;
            ++adjacentColor[color[v]];
        }
        for (int i = 0; i < colorNum; ++i)
        {
            if (colorValid[u][i])
            {
                if (adjacentColor[i] < minSame)
                {
                    minSame = adjacentColor[i];
                    c = i;
                }
            }
        }
        // Update the function.
        sameTotal += minSame - same[u];
        for (int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].v;
            if (color[v] == color[u])
            {
                --same[v];
            }
            if (color[v] == c)
            {
                ++same[v];
            }
        }
        color[u] = c;
        same[u] = minSame;
        // Record the tabu.
        tabuStep[tsRear] = u;
        stepValid[u] = false;
        if (++tsRear >= TABU_STEP_LEN)
        {
            tsRear = 0;
        }
        if (tsRear == tsFront)
        {
            stepValid[tabuStep[tsFront]] = true;
            if (++tsFront >= TABU_STEP_LEN)
            {
                tsFront = 0;
            }
        }
        tabuColor[u][tcRear[u]] = c;
        colorValid[u][c] = false;
        if (++tcRear[u] >= TABU_COLOR_LEN)
        {
            tcRear[u] = 0;
        }
        if (tcRear[u] == tcFront[u])
        {
            colorValid[u][tabuColor[u][tcFront[u]]] = true;
            if (++tcFront[u] >= TABU_COLOR_LEN)
            {
                tcFront[u] = 0;
            }
        }
        // Find the optimize solution.
        if (sameTotal == 0)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        return 0;
    }
    freopen(argv[1], "r", stdin);
    int u, v;
    scanf("%d%d", &n, &m);
    clearEdge();
    while (m--)
    {
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        ++degree[u];
        ++degree[v];
        maxDegree = max(maxDegree, degree[u]);
        maxDegree = max(maxDegree, degree[v]);
    }
    colorNum = min(n, maxDegree + 1);
    while (true)
    {
        memset(color, -1, sizeof(color));
        initColor(0);
        printf("Test %d\n", colorNum);
        if (tabuSearch())
        {
            FILE *file = fopen(argv[2], "w");
            fprintf(file, "%d %d\n", colorNum, 1);
            for (int i = 0; i < n; ++i)
            {
                fprintf(file, "%d ", color[i]);
            }
            fprintf(file, "\n");
            fclose(file);
            printf("Valid\n");
        }
        else
        {
            printf("Failured\n");
            break;
        }
        --colorNum;
    }
    return 0;
}
