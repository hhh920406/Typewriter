#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1000;
const int INF = 0x7fffffff;

//#define DEBUG

#ifdef DEBUG
    //#define DEBUG_GRAPH
    //#define DEBUG_LINK
    //#define DEBUG_DANCING
#endif

int N;
int row, col;
vector<int> num;
struct Node
{
    int u, d, l, r;
    int row, col;
};
vector<Node> node;
vector< vector<int> > graph;
struct Answer
{
    int row, col;
    Answer(int _row, int _col)
    {
        row = _row;
        col = _col;
    }
};
vector<Answer> ans;

void init()
{
    node.clear();
    num.clear();
    for (int i = 0; i <= col; ++i)
    {
        Node newNode;
        newNode.u = i;
        newNode.d = i;
        newNode.l = i - 1;
        newNode.r = i + 1;
        newNode.row = 0;
        newNode.col = i;
        node.push_back(newNode);
        num.push_back(0);
    }
    node[0].l = col;
    node[col].r = 0;
}

void remove(int c)
{
    node[node[c].r].l = node[c].l;
    node[node[c].l].r = node[c].r;
    for (int i = node[c].d; i != c; i = node[i].d)
    {
        for (int j = node[i].r; j != i; j = node[j].r)
        {
            node[node[j].d].u = node[j].u;
            node[node[j].u].d = node[j].d;
            --num[node[j].col];
        }
    }
}

void resume(int c)
{
    for (int i = node[c].u; i != c; i = node[i].u)
    {
        for (int j = node[i].l; j != i; j = node[j].l)
        {
            node[node[j].d].u = j;
            node[node[j].u].d = j;
            ++num[node[j].col];
        }
    }
    node[node[c].l].r = c;
    node[node[c].r].l = c;
}

inline int getPos(const int x, const int y)
{
    return x * N + y;
}

inline int getX(const int pos)
{
    return pos / N;
}

inline int getY(const int pos)
{
    return pos % N;
}

inline bool inBoard(const int x, const int y)
{
    return x >= 0 && x < N && y >= 0 && y < N;
}

bool dfs(int depth)
{
    #ifdef DEBUG_DANCING
    printf("Dancing %d: \n", depth);
    for (int i = 0; i < col; ++i)
    {
        printf("%d ", num[i]);
    }
    printf("\n");
    for (int i = node[col].r; i != col; i = node[i].r)
    {
        printf("%d: ", i);
        for (int j = node[i].d; j != i; j = node[j].d)
        {
            printf("%d ", node[j].row);
        }
        printf("\n");
    }
    #endif
    if (depth == N)
    {
        return true;
    }
    if (node[col].r == col)
    {
        #ifdef DEBUG_DANCING
        printf("Empty %d\n", depth);
        #endif
        return false;
    }
    int minValue = INF;
    int c;
    for (int i = node[col].r; i != col; i = node[i].r)
    {
        if (i >= N + N)
        {
            continue;
        }
        if (num[i] < minValue)
        {
            minValue = num[i];
            c = i;
            if (minValue == 1)
            {
                break;
            }
        }
    }
    remove(c);
    for (int i = node[c].d; i != c; i = node[i].d)
    {
        for (int j = node[i].r; j != i; j = node[j].r)
        {
            remove(node[j].col);
        }
        ans.push_back(Answer(getX(node[i].row), getY(node[i].row)));
        #ifdef DEBUG_DANCING
        printf("Remove %d - %d %d  %d %d\n\n", depth, c, node[i].row, getX(node[i].row), getY(node[i].row));
        #endif
        if (dfs(depth + 1))
        {
            return true;
        }
        ans.pop_back();
        for (int j = node[i].l; j != i; j = node[j].l)
        {
            resume(node[j].col);
        }
    }
    resume(c);
    #ifdef DEBUG_DANCING
    printf("Leave %d\n", depth);
    #endif
    return false;
}

void buildGraph()
{
    row = N * N;
    col = N * 6 - 6;
    for (unsigned int i = 0; i < graph.size(); ++i)
    {
        graph[i].clear();
    }
    graph.clear();
    for (int i = 0; i < row; ++i)
    {
        graph.push_back(vector<int>());
    }
    int gc = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            graph[getPos(i, j)].push_back(gc);
        }
        ++gc;
    }
    for (int j = 0; j < N; ++j)
    {
        for (int i = 0; i < N; ++i)
        {
            graph[getPos(i, j)].push_back(gc);
        }
        ++gc;
    }
    for (int i = N - 2; i >= 0; --i)
    {
        int tx = 0;
        int ty = i;
        while (inBoard(tx, ty))
        {
            graph[getPos(tx, ty)].push_back(gc);
            ++tx, ++ty;
        }
        ++gc;
    }
    for (int i = 1; i < N - 1; ++i)
    {
        int tx = i;
        int ty = 0;
        while (inBoard(tx, ty))
        {
            graph[getPos(tx, ty)].push_back(gc);
            ++tx, ++ty;
        }
        ++gc;
    }
    for (int i = 1; i < N; ++i)
    {
        int tx = 0;
        int ty = i;
        while (inBoard(tx, ty))
        {
            graph[getPos(tx, ty)].push_back(gc);
            ++tx, --ty;
        }
        ++gc;
    }
    for (int i = 1; i < N - 1; ++i)
    {
        int tx = i;
        int ty = N - 1;
        while (inBoard(tx, ty))
        {
            graph[getPos(tx, ty)].push_back(gc);
            ++tx, --ty;
        }
        ++gc;
    }
    #ifdef DEBUG_GRAPH
    printf("Graph: \n");
    for (int i = 0; i < col; ++i)
    {
        printf("%d: ", i);
        for (unsigned int j = 0; j < graph.size(); ++j)
        {
            for (unsigned int k = 0; k < graph[j].size(); ++k)
            {
                if (i == graph[j][k])
                {
                    printf("%d ", j);
                    break;
                }
            }
        }
        printf("\n");
    }
    printf("\n");
    #endif
}

void buildLink()
{
    init();
    for (int i = 0; i < row; ++i)
    {
        int head;
        for (unsigned j = 0; j < graph[i].size(); ++j)
        {
            int c = graph[i][j];
            int nodeNum = node.size();
            Node newNode;
            newNode.row = i;
            newNode.col = c;
            newNode.u = node[c].u;
            newNode.d = c;
            node[newNode.u].d = nodeNum;
            node[newNode.d].u = nodeNum;
            if (j == 0)
            {
                newNode.l = nodeNum;
                newNode.r = nodeNum;
                head = nodeNum;
            }
            else
            {
                newNode.l = node[head].l;
                newNode.r = head;
                node[newNode.l].r = nodeNum;
                node[newNode.r].l = nodeNum;
            }
            node.push_back(newNode);
            ++num[c];
        }
    }
    #ifdef DEBUG_LINK
    printf("Link: \n");
    for (int i = 0; i < col; ++i)
    {
        printf("%d ", num[i]);
    }
    printf("\n");
    for (int i = 0; i <= col; ++i)
    {
        if (node[i].d != i)
        {
            printf("%d: ", i);
            for (int j = node[i].d; j != i; j = node[j].d)
            {
                printf("%d ", node[j].row);
            }
            printf("\n");
        }
    }
    #endif
}

void solve()
{
    printf("Solving: %d ", N);
    buildGraph();
    buildLink();
    ans.clear();
    if (dfs(0))
    {
        char fileName[1024];
        sprintf(fileName, "queens/%d.txt", N);
        FILE *file = fopen(fileName, "w");
        for (unsigned int i = 0; i < ans.size(); ++i)
        {
            fprintf(file, "%d %d\n", ans[i].row, ans[i].col);
        }
        fclose(file);
        printf("Succeed\n");
    }
    else
    {
        printf("Failed\n");
    }
}

int main()
{
    #ifdef DEBUG
    N = 6;
    solve();
    return 0;
    #endif
    for (int i = 1; i < MAXN; ++i)
    {
        N = i;
        solve();
    }
    return 0;
}
