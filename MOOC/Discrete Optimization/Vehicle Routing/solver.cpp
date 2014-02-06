#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 430;
const int MAXM = 50;

int n, m, capacity;
int demand[MAXN];
struct Point
{
    double x, y;
    inline void input()
    {
        scanf("%lf%lf", &x, &y);
    }
} position[MAXN];
int route[MAXM][MAXN];
int routeNum[MAXM];
char *outputFileName;
double objectiveValue;

double dist(const Point &a, const Point &b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void input()
{
    scanf("%d%d%d", &n, &m, &capacity);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &demand[i]);
        position[i].input();
    }
}

bool visit[MAXN];

void initGreedy()
{
    objectiveValue = 0.0;
    visit[0] = true;
    for (int i = 0; i < m; ++i)
    {
        routeNum[i] = 1;
        route[i][0] = 0;
        int remain = capacity;
        while (true)
        {
            int v = -1;
            double near = 1e100;
            int u = route[i][routeNum[i] - 1];
            for (int j = 0; j < n; ++j)
            {
                if (!visit[j])
                {
                    if (remain >= demand[j])
                    {
                        if (dist(position[u], position[j]) < near)
                        {
                            near = dist(position[u], position[j]);
                            v = j;
                        }
                    }
                }
            }
            if (v == -1)
            {
                break;
            }
            visit[v] = true;
            remain -= demand[v];
            route[i][routeNum[i]++] = v;
            objectiveValue += dist(position[u], position[v]);
        }
        int u = route[i][routeNum[i] - 1];
        objectiveValue += dist(position[0], position[u]);
        route[i][routeNum[i]++] = 0;
    }
    printf("Greedy Init: %lf\n", objectiveValue);
}

void output()
{
    FILE *file = fopen(outputFileName, "w");
    fprintf(file, "%lf 0\n", objectiveValue);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < routeNum[i]; ++j)
        {
            fprintf(file, "%d ", route[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        freopen(argv[1], "r", stdin);
        outputFileName = argv[2];
        input();
        initGreedy();
        output();
    }
    return 0;
}
