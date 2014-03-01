#include <iostream>

using namespace std;

// DP 没什么好说的 时间复杂度O(m*n) 空间复杂度O(m*n)
class Solution1
{
public:
    int uniquePaths(int m, int n)
    {
        int paths[101][101], i, j;

        for (i = 1; i <= m; i++)
            paths[i][1] = 1;
        for (j = 1; j <= n; j++)
            paths[1][j] = 1;
        for (i = 2; i <= m; i++)
            for (j = 2; j <= n; j++)
                paths[i][j] = paths[i - 1][j] + paths[i][j - 1];

        return paths[m][n];
    }
};

// 节省空间的DP 时间复杂度O(m*n) 空间复杂度O(n)
// 因为path[i][j]的值只依靠path[i - 1][j] 和 path[i][j - 1]
// 所以我们可以把path[i][j - 1]的值存储在path[i - 1][j - 1]中
class Solution2
{
public:
    int uniquePaths(int m, int n)
    {
        int paths[101], i, j;

        for (i = 1; i <= n; i++)
            paths[i] = 1;
        for (i = 2; i <= m; i++)
        {
            for (j = 2; j <= n; j++)
                paths[j] += paths[j - 1];
        }

        return paths[n];
    }
};

// 直接用排列组合理论也可以求解 空间复杂度O(1) 时间复杂度O(n) (n为 行数与列数的最大值)
// 从start 到 finsh 共需要(m+n-2)步，其中向下m-1步 向右n-1步，所以不同的路线个数为C(m+n-2, m-1)
class Solution3
{
private:
    long long int factor(int start, int end)
    {
        long long int res = 1;
        int i;

        for (i = start; i <= end; i++)
            res *= i;

        return res;
    }

public:
    int uniquePaths(int m, int n)
    {
        int total, max, min;
        long long int res;

        total = m + n - 2;
        max = m > n ? m : n;
        min = m > n ? n : m;
        res = factor(max, total);
        return res / factor(1, min - 1);
    }
};

int main()
{
    //test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    cout << s1.uniquePaths(3, 7) << endl;
    cout << s2.uniquePaths(3, 7) << endl;
    cout << s3.uniquePaths(3, 7) << endl;

    return 0;
}
