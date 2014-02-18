#include <iostream>

using namespace std;

// 递归 辅助空间少 但是运行时间长
// 设以i 为BST树根节点的所有情况：左子树有 i - 1个不同元素，右子树有 n - i 个不同元素
// 同时左右子树都为BST树，并且保证唯一性，所以以 i 为根节点的所有不同树为 左右子树个数的乘积
// 最后累加 1..n 为根节点的BST树个数 即为所求
class Solution1
{
    public:
        int numTrees(int n)
        {
            int i, res = 0;

            if (n == 0 || n == 1)
                return 1;
            if (n == 2)
                return 2;

            for (i = 1; i <= n; i++)
                res += numTrees(i - 1) * numTrees(n - i);

            return res;
        }
};

// DP 执行时间短 但有O（n）的额外存储空间
class Solution2
{
    public:
        int numTrees(int n)
        {
            int i, j, dp[1001];

            dp[0] = dp[1] = 1;
            for (i = 2; i <= 1000; i++)
            {
                for(j = dp[i] = 0; j < i; j++)
                    dp[i] += dp[j] * dp[i - j - 1];
            }

            return dp[n];
        }
};

int main()
{

    Solution1 s1;
    Solution2 s2;

    cout << s1.numTrees(4) << endl;
    cout << s2.numTrees(3) << endl;
   // cout << s.subTrees(3) << endl;

    return 0;
}
