#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 2005;
const int MAXM = 2005;

int n, m;
int capacity[MAXN];
double setupCost[MAXN];
int demand[MAXM];
double travelCost[MAXM][MAXN];
char *outputFileName;
double objectiveValue;
int mapping[MAXM];

void input()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%lf", &capacity[i], &setupCost[i]);
    }
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &demand[i]);
        for (int j = 0; j < n; ++j)
        {
            scanf("%lf", &travelCost[i][j]);
        }
    }
}

bool setup[MAXN];
int remain[MAXN];

void initGreedy()
{
    objectiveValue = 0.0;
    memset(setup, false, sizeof(setup));
    memcpy(remain, capacity, sizeof(remain));
    for (int i = 0; i < m; ++i)
    {
        double near = 1e100;
        int index = -1;
        for (int j = 0; j < n; ++j)
        {
            if (remain[j] >= demand[i])
            {
                if (travelCost[i][j] < near)
                {
                    near = travelCost[i][j];
                    index = j;
                }
            }
        }
        if (!setup[index])
        {
            objectiveValue += setupCost[index];
            setup[index] = true;
        }
        remain[index] -= demand[i];
        mapping[i] = index;
    }
    printf("Greedy Init: %lf\n", objectiveValue);
}

void output()
{
    FILE *file = fopen(outputFileName, "w");
    fprintf(file, "%lf 0\n", objectiveValue);
    for (int i = 0; i < m; ++i)
    {
        fprintf(file, "%d ", mapping[i]);
    }
    fprintf(file, "\n");
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
