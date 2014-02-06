#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 400;
const int MAXM = 9486368;

int itemNum, capacity;
int value[MAXN], weight[MAXN];
int dp[2][MAXM];
vector<char> take[MAXM];
bool path[MAXN];

int main()
{
    scanf("%d%d", &itemNum, &capacity);
    for (int i = 0; i < itemNum; ++i)
    {
        scanf("%d%d", &value[i], &weight[i]);
    }
    for (int i = 0; i < itemNum; ++i)
    {
        int cur = i & 1;
        int pre = cur ^ 1;
        for (int j = capacity; j >= 0; --j)
        {
            dp[cur][j] = dp[pre][j];
            if (j + weight[i] <= capacity)
            {
                if (dp[pre][j] + value[i] > dp[cur][j + weight[i]])
                {
                    dp[cur][j + weight[i]] = dp[pre][j] + value[i];
                    take[j + weight[i]].clear();
                    take[j + weight[i]].assign(take[j].begin(), take[j].end());
                    take[j + weight[i]].push_back(i);
                }
            }
        }
    }
    int last = (itemNum - 1) & 1;
    int maxValue = 0;
    int lastWeight;
    for (int i = 0; i <= capacity; ++i)
    {
        if (dp[last][i] > maxValue)
        {
            maxValue = dp[last][i];
            lastWeight = i;
        }
    }
    for (int i = 0; i < take[lastWeight].size(); ++i)
    {
        path[take[lastWeight][i]] = true;
    }
    printf("%d 1\n", maxValue);
    for (int i = 0; i < itemNum; ++i)
    {
        printf("%d ", path[i]);
    }
    printf("\n");
    return 0;
}
