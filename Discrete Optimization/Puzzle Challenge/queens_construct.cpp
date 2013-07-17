#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

bool judge(vector<int> &ans)
{
    for (int i = 0; i < ans.size(); ++i)
    {
        for (int j = i + 1; j < ans.size(); ++j)
        {
            if (ans[i] == ans[j])
            {
                return false;
            }
            if (abs(ans[i] - ans[j]) == abs(i - j))
            {
                return false;
            }
        }
    }
    return true;
}

void solve(int n)
{
    vector<int> ans;
    if (n % 6 != 2 && n % 6 != 3)
    {
        for (int i = 1; i < n; i += 2)
        {
            ans.push_back(i);
        }
        for (int i = 0; i < n; i += 2)
        {
            ans.push_back(i);
        }
    }
    else
    {
        int k = n >> 1;
        if (!(k & 1) && !(n & 1))
        {
            for (int i = k - 1; i < n; i += 2)
            {
                ans.push_back(i);
            }
            for (int i = 1; i < k - 2; i += 2)
            {
                ans.push_back(i);
            }
            for (int i = k + 2; i < n - 1; i += 2)
            {
                ans.push_back(i);
            }
            for (int i = 0; i < k + 1; i += 2)
            {
                ans.push_back(i);
            }
        }
        else if (!(k & 1) && (n & 1))
        {
            for (int i = k - 1; i < n - 1; i += 2)
            {
                ans.push_back(i);
            }
            for (int i = 1; i < k - 2; i += 2)
            {
                ans.push_back(i);
            }
            for (int i = k + 2; i < n - 2; i += 2)
            {
                ans.push_back(i);
            }
            for (int i = 0; i < k + 1; i += 2)
            {
                ans.push_back(i);
            }
            ans.push_back(n);
        }
        else if ((k & 1) && !(n & 1))
        {
            for (int i = k - 1; i < n - 1; i += 2)
            {
                ans.push_back(i);
            }
            for (int i = 0; i < k - 2; i += 2)
            {
                ans.push_back(i);
            }
            for (int i = k + 2; i < n; i += 2)
            {
                ans.push_back(i);
            }
            for (int i = 1; i < k + 1; i += 2)
            {
                ans.push_back(i);
            }
        }
        else
        {
            for (int i = k - 1; i < n - 2; i += 2)
            {
                ans.push_back(i);
            }
            for (int i = 0; i < k - 2; i += 2)
            {
                ans.push_back(i);
            }
            for (int i = k + 2; i < n - 1; i += 2)
            {
                ans.push_back(i);
            }
            for (int i = 1; i < k + 1; i += 2)
            {
                ans.push_back(i);
            }
            ans.push_back(n);
        }
    }
    char fileName[1024];
    sprintf(fileName, "queens/%d.txt", n);
    FILE *file = fopen(fileName, "w");
    for (int i = 0; i < n; ++i)
    {
        fprintf(file, "%d %d\n", i, ans[i]);
    }
    fclose(file);
}

int main()
{
    for (int i = 70; i <= 100000; ++i)
    {
        printf("Solving %d\n", i);
        solve(i);
    }
    return 0;
}
