#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

// 看到题目后本能的想到递归解法
// 若s1和s2的长度不等，则两个字符串肯定不是scramble的
// 当s1和s2长度相等时，s1[0..i] s2[0..i]
// 因为scramble定义，分隔点可以使1..i-1中的任何一个（0和i-1除外的原因是 分隔的两个子串都不为空）
// 对于某一个k 如果s1和s2是scramble的，那么其两个子问题：
// (1).s1(0,k),s2(0,k)是scramele的 并且s1(k, i - k), s2(k, i-k)是scramble
// (2).s1(0,k),s2(i-k, k)是scramble 并且s1(k, i-k), s2(0,k)是scramble
// 若两个子问题至少有一个是scramble的 则原字符串是scramble的
// 否则原字符串不是scramble
// 52ms
class Solution1
{
private:
    bool isScrambleHelper(string s1, string s2)
    {
        if (s1 == s2)
            return true;

        string tmp1 = s1;
        string tmp2 = s2;
        sort(tmp1.begin(), tmp1.end());
        sort(tmp2.begin(), tmp2.end());
        if (tmp1 != tmp2)
            return false;

        for(int k = 1; k < s1.size(); k++)
        {
            string sub1 = s1.substr(0, k);
            string sub2 = s1.substr(k);
            string sub3 = s2.substr(0, k);
            string sub4 = s2.substr(k);
            if (isScrambleHelper(sub1, sub3) && isScrambleHelper(sub2, sub4))
                return true;
            sub3 = s2.substr(0, s2.size() - k);
            sub4 = s2.substr(s2.size() - k);
            if (isScrambleHelper(sub1, sub4) && isScrambleHelper(sub2, sub3))
                return true;
        }

        return false;
    }

public:
    bool isScramble(string s1, string s2)
    {
        if (s1.size() != s2.size())
            return false;

        return isScrambleHelper(s1, s2);
    }
};

// DP
// dp[k][i][j] 表示从s1[i]和s2[j]开始的k个元素的子串是否时scramble
// dp[k][i][j] 可由子问题求解 dp[k][i][j] = (dp[div][i][j] && dp[k-div][i+div][j+div]) || (dp[div][i][j+k-div] && dp[k-div][i+div][j]) 其中div=1,2...k-1;
// 初始化 dp[1][i][j] = s1[i] == s2[j] ? true : false; i, j = 0, 1...n-1
// 80ms
class Solution2
{
public:
    bool isScramble(string s1, string s2)
    {
        if (s1.size() != s2.size())
            return false;

        int i, j, k;
        const int n = s1.size();
        bool dp[n + 1][n][n];

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                dp[1][i][j] = (s1[i] == s2[j] ? true : false);

        for (k = 2; k <= n; k++)
            for (i = 0; i <= n - k; i++)
                for (j = 0; j <= n - k; j++)
                {
                    dp[k][i][j] = false;
                    for (int div = 1; div < k && !dp[k][i][j]; div++)
                        dp[k][i][j] = ((dp[div][i][j] && dp[k - div][i + div][j + div])
                                        || (dp[div][i][j + k - div] && dp[k - div][i + div][j]));
                }

        return dp[n][0][0];
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    string str1 = "abc";
    string str2 = "cab";
    cout << s1.isScramble(str1, str2) << endl;
    cout << s2.isScramble(str1, str2) << endl;

    return 0;
}
