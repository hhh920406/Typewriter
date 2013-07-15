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
int color[MAXN], colorNum;
bool visit[MAXN][MAXN];
int totalColor[MAXN], maxColor;
int ans[MAXN], ansNum;
struct Node
{
    int x, in;
    bool operator <(const Node &node) const
    {
        return in > node.in;
    }
} node[MAXN];

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

bool dfs(int u, int d)
{
    if (d == n)
    {
        return true;
    }
    u = node[d].x;
    for (int i = 0; i < colorNum; ++i)
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
    for (int i = 0; i < colorNum && i <= maxColor + 1; ++i)
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
            if (dfs(u + 1, d + 1))
            {
                return true;
            }
            maxColor = recentColor;
            --totalColor[i];
            color[u] = -1;
        }
    }
    return false;
}

bool valid(int x)
{
    colorNum = x;
    for (int i =0 ; i < n; ++i)
    {
        color[i] = -1;
    }
    maxColor = -1;
    return dfs(0, 0);
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
    ansNum = n;
    int left = 1, right = min(n, node[0].in + 1);
    while (left <= right)
    {
        int mid = (left + right) >> 1;
        printf("%d ", mid);
        if (valid(mid))
        {
            printf("Valid");
            right = mid - 1;
            if (mid < ansNum)
            {
                ansNum = mid;
                for (int i = 0; i < n; ++i)
                {
                    ans[i] = color[i];
                }
            }
        }
        else
        {
            left = mid + 1;
        }
        printf("\n");
    }
    freopen(argv[2], "w", stdout);
    printf("%d 1\n", ansNum);
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", ans[i]);
    }
    return 0;
}
