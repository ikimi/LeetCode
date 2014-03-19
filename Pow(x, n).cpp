#include <iostream>
#include <cmath>

using namespace std;

// TLE超时了
class Solution1
{
public:
    double pow(double x, int n)
    {
        double res;
        int i;

        for (i = 1; i <= n; i++)
            res *= x;

        return res;
    }
};

// 递归解法
// 时间复杂度O(n) 这里忽略不同数位数字相乘之间的时间差异
// 注意 n 可能为负数 WA 了一次
// 52ms
class Solution2
{
public:
    double pow(double x, int n)
    {
        if (n == 0)
            return 1.0;
        if (n == 1)
            return x;
        if (n == -1)
            return 1.0 / x;

        double temp = pow(x, n / 2); // 用一个变量存储临时结果
        if (n % 2)                   // 每一层只需要存储一个 所以共 log(n) 层 只需计算log(n)次就可以了
        {
            if (n < 0)
                return temp * temp * (1.0 / x);
            return temp * temp * x;
        }
        return temp * temp;
    }
};

int main()
{
    // test example
    Solution2 s2;

    cout << s2.pow(2, 10) << endl;
    cout << s2.pow(34.00515, -3) << endl;

    return 0;
}
