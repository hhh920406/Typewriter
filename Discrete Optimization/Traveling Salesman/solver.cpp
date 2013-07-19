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
vector<int> prev;
double totalLength;
double minimumLength;

char *outputFileName;

inline int getNext(int x, int p)
{
    if (prev[x] == p)
    {
        return next[x];
    }
    return prev[x];
}

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
        prev.push_back(0);
    }
    totalLength = 0.0;
    for (int i = 0; i < n; ++i)
    {
        totalLength += dist(node[path[i]], node[path[(i + 1) % n]]);
        next[path[i]] = path[(i + 1) % n];
        prev[path[i]] = path[(i + n - 1) % n];
    }
    minimumLength = totalLength;
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
    int p = prev[cur];
    for (int i = 0; i < n; ++i)
    {
        fprintf(file, "%d ", cur);
        int temp = cur;
        cur = getNext(cur, p);
        p = temp;
    }
    fclose(file);
}

#ifdef DEBUG
bool isNextValid()
{
    int cur = 0;
    int p = prev[0];
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
        int temp = cur;
        cur = getNext(cur, p);
        p = temp;
    }
    return cur == 0;
}
#endif

void opt2()
{
    vector<int> nextCopy;
    vector<int> prevCopy;
    nextCopy.assign(next.begin(), next.end());
    prevCopy.assign(prev.begin(), prev.end());
    while (true)
    {
        printf("2 Opt Loop\n");
        for (int t1 = 0; t1 < n; ++t1)
        {
            for (int t3 = 0; t3 < n; ++t3)
            {
                int t2 = next[t1];
                int t4 = next[t3];
                if (t1 == t3 || t1 == t4 || t2 == t3 || t2 == t4)
                {
                    continue;
                }
                if (dist(node[t1], node[t3]) + dist(node[t2], node[t4]) <
                    dist(node[t1], node[t2]) + dist(node[t3], node[t4]))
                {
                    next[t1] = t3;
                    prev[t3] = t1;
                    if (prev[t2] == t1)
                    {
                        prev[t2] = t4;
                    }
                    else
                    {
                        next[t2] = t4;
                    }
                    if (prev[t4] == t3)
                    {
                        prev[t4] = t2;
                    }
                    else
                    {
                        next[t4] = t2;
                    }
                    #ifdef DEBUG
                    if (!isNextValid())
                    {
                        //printf("The next array is broken.\n");
                        next.assign(nextCopy.begin(), nextCopy.end());
                        prev.assign(prevCopy.begin(), prevCopy.end());
                        continue;
                    }
                    #endif
                }
                totalLength = 0;
                for (int i = 0; i < n; ++i)
                {
                    int u = i;
                    int v = next[i];
                    totalLength += dist(node[u], node[v]);
                }
                if (totalLength < minimumLength)
                {
                    nextCopy.assign(next.begin(), next.end());
                    prevCopy.assign(prev.begin(), prev.end());
                    minimumLength = totalLength;
                    savePath();
                }
            }
        }
    }
}

bool isConnect(int t1, int t3, int t5)
{
    vector<int> test;
    test.push_back(t1);
    test.push_back(t3);
    test.push_back(t5);
    test.push_back(next[t1]);
    test.push_back(next[t3]);
    test.push_back(next[t5]);
    test.push_back(prev[t1]);
    test.push_back(prev[t3]);
    test.push_back(prev[t5]);
    test.push_back(getNext(next[t1], t1));
    test.push_back(getNext(next[t3], t3));
    test.push_back(getNext(next[t5], t5));
    sort(test.begin(), test.end());
    for (unsigned int i = 1; i < test.size(); ++i)
    {
        if (test[i] == test[i - 1])
        {
            return false;
        }
    }
    return true;
}

void opt3()
{
    vector<int> nextCopy;
    vector<int> prevCopy;
    nextCopy.assign(next.begin(), next.end());
    prevCopy.assign(prev.begin(), prev.end());
    while (true)
    {
        printf("3 Opt Loop\n");
        for (int t1 = 0; t1 < n; ++t1)
        {
            for (int t3 = 0; t3 < n; ++t3)
            {
                for (int t5 = 0; t5 < n; ++t5)
                {
                    if (isConnect(t1, t3, t5))
                    {
                        continue;
                    }
                    int t2 = next[t1];
                    int t4 = next[t3];
                    int t6 = next[t5];
                    if (dist(node[t1], node[t3]) + dist(node[t6], node[t2]) + dist(node[t5], node[t4]) <
                        dist(node[t1], node[t2]) + dist(node[t3], node[t4]) + dist(node[t5], node[t6]))
                    {
                        next[t1] = t6;
                        if (prev[t6] == t5)
                        {
                            prev[t6] = t1;
                        }
                        else
                        {
                            next[t6] = t1;
                        }
                        next[t3] = t2;
                        if (prev[t2] == t1)
                        {
                            prev[t2] = t3;
                        }
                        else
                        {
                            next[t2] = t3;
                        }
                        next[t5] = t4;
                        if (prev[t4] == t3)
                        {
                            prev[t4] = t5;
                        }
                        else
                        {
                            next[t4] = t5;
                        }
                        #ifdef DEBUG
                        if (!isNextValid())
                        {
                            //printf("The next array is broken.\n");
                            next.assign(nextCopy.begin(), nextCopy.end());
                            prev.assign(prevCopy.begin(), prevCopy.end());
                            continue;
                        }
                        #endif
                    }
                    totalLength += dist(node[t1], node[t3]) + dist(node[t6], node[t2]) + dist(node[t5], node[t4]) -
                                    dist(node[t1], node[t2]) + dist(node[t3], node[t4]) + dist(node[t5], node[t6]);
                    if (totalLength < minimumLength)
                    {
                        nextCopy.assign(next.begin(), next.end());
                        prevCopy.assign(prev.begin(), prev.end());
                        minimumLength = totalLength;
                        savePath();
                    }
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
        savePath();
        optK();
        opt2();
        opt3();
    }
    return 0;
}
