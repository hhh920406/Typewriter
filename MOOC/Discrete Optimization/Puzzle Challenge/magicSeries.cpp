#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 10;

int N;
int ans[MAXN];
int sum[MAXN];

bool dfs(int depth)
{
    if (depth == N)
    {
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < N; ++i)
        {
            ++sum[ans[i]];
        }
        for (int i = 0; i < N; ++i)
        {
            if (ans[i] != sum[i])
            {
                return false;
            }
        }
        for (int i = 0; i < N; ++i)
        {
            printf("%d ", ans[i]);
        }
        printf("\n");
        return true;
    }
    for (int i = 0; i < N; ++i)
    {
        ans[depth] = i;
        if (dfs(depth + 1))
        {
            return true;
        }
    }
    return false;
}

int main()
{
    for (int i = 1; i <= 10; ++i)
    {
        N = i;
        dfs(0);
    }
    return 0;
}
