#include <iostream>

using namespace std;

// DP 求解 时间复杂度O(n) 空间复杂度O(1)
class Solution1
{
    public:
        int climbStairs(int n)
        {
            if (n <= 2)
                return n;

            int x = 1, y = 2, i, res;
            for (i = 3; i <= n; i++)
            {
                res = x + y;
                x = y;
                y = res;
            }

            return res;
        }
};

int main()
{
    // test example
    Solution1 s1;

    cout << s1.climbStairs(2) << endl;
    cout << s1.climbStairs(3) << endl;
    cout << s1.climbStairs(10) << endl;

    // 正好溢出
    cout << s1.climbStairs(48) << endl;

    return 0;
}
