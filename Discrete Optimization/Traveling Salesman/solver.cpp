#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define DEBUG

#ifdef DEBUG
    //#define DEBUG_INIT
#endif

int n;
struct Node
{
    double x, y;
    inline void input()
    {
        scanf("%lf%lf", &x, &y);
    }
};
vector<Node> node;

vector<int> next;
double totalLength;
double minimumLength;

char *outputFileName;

inline double dist(double x, double y)
{
    return sqrt(x * x + y * y);
}

inline double dist(const Node &a, const Node &b)
{
    return dist(a.x - b.x, a.y - b.y);
}

void createInitPath()
{
    int cur = 0;
    vector<int> path;
    /*
    path.push_back(0);
    totalLength = 0.0;
    vector<bool> visit(n);
    visit[0] = true;
    for (int i = 1; i < n; ++i)
    {
        visit[i] = false;
    }
    for (int i = 1; i < n; ++i)
    {
        double localMin = 1e100;
        int next = -1;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j])
            {
                double temp = dist(node[cur], node[j]);
                if (temp < localMin)
                {
                    localMin = temp;
                    next = j;
                }
            }
        }
        totalLength += localMin;
        path.push_back(next);
        cur = next;
        visit[cur] = true;
    }
    totalLength += dist(node[0], node[cur]);
    minimumLength = totalLength;*/

    FILE *file = fopen(outputFileName, "r");
    fscanf(file, "%lf 0", &minimumLength);
    for (int i = 0; i < n; ++i)
    {
        int temp;
        fscanf(file, "%d", &temp);
        path.push_back(temp);
    }
    fclose(file);

    for (int i = 0; i < n; ++i)
    {
        next.push_back(0);
    }
    for (int i = 0; i < n; ++i)
    {
        next[path[i]] = path[(i + 1) % n];
    }
    #ifdef DEBUG_INIT
    printf("Init Length: %lf\n", minimumLength);
    for (int i = 0; i < n; ++i)
    {
        printf("%d %d\n", path[i], next[i]);
    }
    printf("\n");
    #endif
}

void savePath()
{
    printf("Minimize %lf\n", minimumLength);
    FILE *file = fopen(outputFileName, "w");
    fprintf(file, "%lf 0\n", minimumLength);
    int cur = 0;
    for (int i = 0; i < n; ++i)
    {
        fprintf(file, "%d ", cur);
        cur = next[cur];
    }
    fclose(file);
}

#ifdef DEBUG
bool isNextValid()
{
    int cur = 0;
    vector<bool> visit(n);
    for (int i = 0; i < n; ++i)
    {
        visit[i] = false;
    }
    for (int i = 0; i < n; ++i)
    {
        if (visit[cur])
        {
            return false;
        }
        visit[cur] = true;
        cur = next[cur];
    }
    return cur == 0;
}
#endif

void opt2()
{
    int iter = 0;
    for (int t1 = 0; ; t1 = (t1 + 1) % n)
    {
        for (int t3 = t1 + 2; t3 < n; ++t3)
        {
            if (++iter % 1000 == 0)
            {
                //printf("Iter %d %lf\n", iter, minimumLength);
            }
            int t2 = next[t1];
            int t4 = next[t3];
            if (dist(node[t1], node[t3]) + dist(node[t2], node[t4]) <
                dist(node[t1], node[t2]) + dist(node[t3], node[t4]))
            {
                next[t1] = t3;
                int prev = t4;
                for (int i = t2; i != t4;)
                {
                    int temp = next[i];
                    next[i] = prev;
                    prev = i;
                    i = temp;
                }
            }
            #ifdef DEBUG
            if (!isNextValid())
            {
                printf("The next array is broken.\n");
                exit(0);
            }
            #endif
            totalLength = 0;
            for (int i = 0; i < n; ++i)
            {
                int u = i;
                int v = next[i];
                totalLength += dist(node[u], node[v]);
            }
            if (totalLength < minimumLength)
            {
                minimumLength = totalLength;
                savePath();
            }
        }
    }
}

void opt3()
{
    int iter = 0;
    for (int t1 = 0; ; t1 = (t1 + 1) % n)
    {
        int t5 = next[t1];
        for (int ii = 2; ii < n; ++ii)
        {
            t5 = next[t5];
            int t3 = next[t5];
            for (int jj = 6; jj < n; ++jj)
            {
                t3 = next[t3];
                if (++iter % 1000 == 0)
                {
                    printf("Iter %d %lf\n", iter, minimumLength);
                }
                int t2 = next[t1];
                int t4 = next[t3];
                int t6 = next[t5];
                if (dist(node[t1], node[t3]) + dist(node[t6], node[t2]) + dist(node[t5], node[t4]) <
                    dist(node[t1], node[t2]) + dist(node[t3], node[t4]) + dist(node[t5], node[t6]))
                {
                    next[t1] = t3;
                    next[t5] = t4;
                    int prev = t2;
                    for (int i = t6; i != t4;)
                    {
                        int temp = next[i];
                        next[i] = prev;
                        prev = i;
                        i = temp;
                    }
                }
                #ifdef DEBUG
                if (!isNextValid())
                {
                    printf("The next array is broken.\n");
                    exit(0);
                }
                #endif
                totalLength = 0;
                for (int i = 0; i < n; ++i)
                {
                    int u = i;
                    int v = next[i];
                    totalLength += dist(node[u], node[v]);
                }
                if (totalLength < minimumLength)
                {
                    minimumLength = totalLength;
                    savePath();
                }
            }
        }
    }
}

void optK()
{
    savePath();
    queue<int> recent;
    vector<int> valid(n);
    for (int i = 0; i < n; ++i)
    {
        valid[i] = true;
    }
    int iter = 0;
    for (int index = 0; ; index = (index + 1) % n)
    {
        if (++iter % 1000 == 0)
        {
            printf("Iter %d %lf\n", iter, minimumLength);
        }
        while (true)
        {
            int t1 = index;
            int t2 = next[index];
            double minDist = 1e100;
            int t4;
            for (int i = 0; i < n; ++i)
            {
                if (i != t1 && i != t2)
                {
                    int t3 = next[i];
                    double temp = dist(node[t2], node[t3]) + dist(node[t1], node[i]) - dist(node[t3], node[i]);
                    if (temp < minDist)
                    {
                        minDist = temp;
                        t4 = i;
                    }
                }
            }
            if (minDist >= dist(node[t1], node[t2]) - 1e-6)
            {
                break;
            }
            int t3 = next[t4];
            next[t1] = t4;
            int prev = t3;
            for (int i = t2; i != t3;)
            {
                int temp = next[i];
                next[i] = prev;
                prev = i;
                i = temp;
            }
            #ifdef DEBUG
            if (!isNextValid())
            {
                printf("The next array is broken.\n");
                break;
            }
            #endif
        }
        #ifdef DEBUG
        if (!isNextValid())
        {
            printf("The next array is broken.\n");
            break;
        }
        #endif
        totalLength = 0;
        for (int i = 0; i < n; ++i)
        {
            int u = i;
            int v = next[i];
            totalLength += dist(node[u], node[v]);
        }
        if (totalLength < minimumLength)
        {
            minimumLength = totalLength;
            savePath();
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        freopen(argv[1], "r", stdin);
        outputFileName = argv[2];
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            Node newNode;
            newNode.input();
            node.push_back(newNode);
        }
        createInitPath();
        opt3();
        opt2();
        optK();
    }
    return 0;
}
