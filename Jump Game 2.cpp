#include <iostream>
#include <vector>

using namespace std;

// DP 空间复杂度O(n^2)
// MLE 空间超了。。。
class Solution1
{
public:
    int jump(int A[], int n)
    {
        vector<vector<int> > dp(n, vector<int> (n, 0));

        int gap, index, i, min;

        for (index = 0; index < n - 1; index++)
        {
            if (!A[index])
                dp[index][index + 1] = -1;
            else
                dp[index][index + 1] = 1;
        }

        for (gap = 2; gap < n; gap++)
        {
            for (index = 0; index + gap < n; index++)
            {
                if (A[index] >= gap)
                    dp[index][index + gap] = 1;
                else
                    dp[index][index + gap] = -1;
                for (i = index + 1; i < index + gap; i++)
                {
                    if  (dp[index][i] != -1 && dp[i][index + gap] != -1)
                    {
                        min = dp[index][i] + dp[i][index + gap];
                        if (dp[index][index + gap] == -1 || min < dp[index][index + gap])
                            dp[index][index + gap] = min;
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};

// DP 思路相同 但是空间复杂度为O(n)
// 但是 TLE 了
class Solution2
{
public:
    int jump(int A[], int n)
    {
        vector<int> dp(n, 0);

        int minJump, i, j;
        for (i = n - 2; i >= 0; i--)
        {
            minJump = n;
            for (j = i + 1; j <= A[i] + i && j < n; j++)
            {
                if (dp[j] + 1 < minJump)
                    minJump =  dp[j]+ 1;
            }
            dp[i] = minJump;
        }

        return dp[0];
    }
};

// Greedy 终于AC
// ret 表示要跳跃的次数， cur 表示在目前这一跳中所能到达的最远位置 next表示下一跳能到达的最远距离
// 48ms
class Solution3
{
public:
    int jump(int A[], int n)
    {
        if (n <= 1)
            return 0;

        int i, res, cur, next;
        i = res = cur = next = 0;

        while (i < n)
        {
            while (i <= cur)
            {
                if (A[i] + i > next)
                    next = A[i] + i;
                if (next >= n - 1)
                    return ++res;
                i++;
            }
            cur = next;
            res++;
        }

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    int A[] = {2, 3, 1, 1, 4};
    cout << s1.jump(A, 5) << endl;
    cout << s2.jump(A, 5) << endl;
    cout << s3.jump(A, 5) << endl;

    return 0;
}
