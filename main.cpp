#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

// 递归方法 果断超时了
// 从 S 和 T 的最后一个字符开始判断
// 1）若相同 则递归调用 S - 1 和 T - 1 的子串
// 2）不论是否形同 都调用 S - 1 和 T 的子串
// 递归结束条件是 S 剩余子串长度小于或者等于 T 剩余子串长度
// 递归超时果断用 DP 做啊
class Solution1
{
private:
    int helper(string S, int high1, string T, int high2)
    {
        if (high1 <= high2)
        {
            if (S.substr(0, high1 + 1) == T.substr(0, high2 + 1))
                return 1;
            return 0;
        }

        if (S[high1] == T[high2])
            return helper(S, high1 - 1, T, high2) + helper(S, high1 - 1, T, high2 - 1);
        else
            return helper(S, high1 - 1, T, high2);
    }

public:
    int numDistinct(string S, string T)
    {
        return helper(S, S.length() - 1, T, T.length() - 1);
    }
};

// DP
// dp[i][j] 表示从S的第1个元素开始到第i个元素，可以匹配T的前j个元素组成的子串(数组下标从1开始)
// 递推关系如下：dp[i][j] = dp[i - 1][j] + foo(i, j)
// 若S[i] == T[j] 则foo(i, j) = dp[i - 1][j - 1] 否则foo(i, j) = 0
// 算法时间复杂度为O(n*m) 空间复杂度为 O(n*m)
// 80ms
class Solution2
{
public:
    int numDistinct(string S, string T)
    {
        int m, n, i, j;

        m = S.length(), n = T.length();
        vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));

        for (i = 0; i <= m; i++)    // 没有初始化 在这里一直WA
            dp[i][0] = 1;
        for (i = 1; i <= m; i++)
        {
            for (j = 1; j <= i && j <= n; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (S[i - 1] == T[j - 1])
                    dp[i][j] += dp[i - 1][j - 1];
            }
        }
/*
        for (i = 0; i <= m; i++)
        {
            for (j = 0; j <= n; j++)
                cout << dp[i][j] << ' ';
            cout << endl;
        }
*/
        return dp[m][n];
    }
};

// DP 只利用一维数组就可以求解
// 时间复杂度 O(n^m) 空间复杂度O(n) 结果显示时间消耗也降低了
// 22ms
class Solution3
{
public:
    int numDistinct(string S, string T)
    {
        int m, n, temp1, temp2, i , j;

        m = S.length(), n = T.length();
        vector<int> dp(n + 1, 0);

        for (dp[0] = i = 1; i <= m; i++)
        {
            for (temp1 = dp[0], temp2 = dp[1], j = 1; j <= n && j <= i; j++)
            {
                dp[j] = temp2;
                if (S[i - 1] == T[j - 1])
                    dp[j] += temp1;
                temp1 = temp2;
                temp2 = dp[j + 1];
            }
        }

        return dp[n];
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

  //  string S = "rabbbit";
  //  string T = "rabbit";

    string S = "aabdbaabeeadcbbdedacbbeecbabebaeeecaeabaedadcbdbcdaabebdadbbaeabdadeaabbabbecebbebcaddaacccebeaeedababedeacdeaaaeeaecbe";
    string T = "bddabdcae";
  //  string S = "ccc";
  //  string T = "c";
 //   cout << s1.numDistinct(S, T) << endl;
    cout << s2.numDistinct(S, T) << endl;
    cout << s3.numDistinct(S, T) << endl;

    return 0;
}
