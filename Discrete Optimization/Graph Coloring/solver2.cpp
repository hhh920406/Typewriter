#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
const int MAXM = 400000 * 2;

int n, m;
struct Edge
{
    int v, next;
} edge[MAXM];
int head[MAXN], edgeNum;
int color[MAXN];
bool visit[MAXN][MAXN];
int totalColor[MAXN], maxColor;
int ansNum;
struct Node
{
    int x, in;
    bool operator <(const Node &node) const
    {
        return in > node.in;
    }
} node[MAXN];
char *outputFileName;

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

void dfs(int d)
{
    if (maxColor + 1 >= ansNum)
    {
        return;
    }
    if (d == n)
    {
        ansNum = maxColor + 1;
        printf("Find: %d\n", ansNum);
        FILE *file = fopen(outputFileName, "w");
        fprintf(file, "%d 1\n", ansNum);
        for (int i = 0; i < n; ++i)
        {
            fprintf(file, "%d ", color[i]);
        }
        fprintf(file, "\n");
        fclose(file);
        return;
    }
    int u = node[d].x;
    for (int i = 0; i <= maxColor; ++i)
    {
        visit[d][i] = false;
    }
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].v;
        if (color[v] != -1)
        {
            visit[d][color[v]] = true;
        }
    }
    for (int i = 0; i <= maxColor + 1; ++i)
    {
        if (!visit[d][i])
        {
            int recentColor = maxColor;
            color[u] = i;
            ++totalColor[i];
            if (i > maxColor)
            {
                maxColor = i;
            }
            dfs(d + 1);
            maxColor = recentColor;
            --totalColor[i];
            color[u] = -1;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        return 0;
    }
    freopen(argv[1], "r", stdin);
    outputFileName = argv[2];
    int u, v;
    scanf("%d%d", &n, &m);
    clearEdge();
    for (int i = 0; i < n; ++i)
    {
        node[i].x = i;
        node[i].in = 0;
    }
    while (m--)
    {
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        ++node[u].in;
        ++node[v].in;
    }
    sort(node, node + n);
    ansNum = n;
    for (int i =0 ; i < n; ++i)
    {
        color[i] = -1;
    }
    maxColor = -1;
    dfs(0);
    return 0;
}
