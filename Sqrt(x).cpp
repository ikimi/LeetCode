#include <iostream>
#include <cmath>

#define EPS 1e-6

using namespace std;

// 方法摘自：http://www.cnblogs.com/Matrix_Yao/archive/2009/07/28/1532883.html
// 暴力法
// 根据等差数列 1 + 2 + 3 + ... + 2*n-1 = n ^ 2
// 所以我们可以从i = 1开始累加sum,当sum==x时，直接返回n
// 当sum 第一次 大于 x的时候 返回n-1
// TLE
class Solution1
{
public:
    int sqrt(int x)
    {
        int i;
        long long int sum;  // 注意这里可能溢出 所以sum应该声明为 long long

        for (i = 1, sum = 0; ; i++)
        {
            //sum += 2 * i - 1;
            sum += (i << 1) - 1;
            if (sum > x)
                return i - 1;
        }
    }
};

// 参考：http://www.cnblogs.com/pkuoliver/archive/2010/10/06/1844725.html
// 二分法
// 一个正整数的平方根一定在[0,x]范围内，取中间的数mid=(0+x)/2 若mid*mid==x则返回mid
// 若 mid*mid < x 则所求位置位于[mid,x]区间内，更新low = mid + 1
// 否则所求位置位于[0，mid]区间内,更新high = mid - 1
// 76ms
class Solution2
{
public:
    int sqrt(int x)
    {
        int low, high;

        low = 0, high = x;
        while (low <= high)
        {
            long long int mid = (low + high) / 2;
            if (mid * mid == x)
                return mid;
            else if (mid * mid < x)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return (low + high) / 2;
    }
};

// Newton迭代法
// 其实就是利用方程x*x-a=0的切线不断逼近真实的根
// 初始可以随意估计一个根（这里我们估计根就是x）
// 对方程求导，则方程的切线斜率是2*x,则在（x1, x1*x1-a）点处的切线是：y = 2*x*x1 - x1*x1 - a
// 其在x轴上的交点坐标是（(a+x1*x1)/(2*x1), 0）
// 在次利用新求出的x轴坐标计算下一次迭代的坐标位置，直到两次求得的坐标偏差不超过1e-6为止
// 88ms
class Solution3
{
public:
    int sqrt(int x)
    {
        if (!x)     // 如果不处理x是0的情况 那么下面分母有可能会出现为0的情况 WA了一次
            return 0;

        double pre, cur;    // 必须声明称double类型，如果声明称float类型 会造成精度缺失 WA了一次

        cur = x;
        do
        {
            pre = cur;
            cur = (x / cur + cur) / 2;
        }while (abs(cur-pre) > EPS);

        return (int)cur;
    }
};

// 还有一种更快的sqrt函数 在链接地址中有介绍
int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

   // cout << s1.sqrt(1579205274) << endl;
   // cout << s1.sqrt(2147483647) << endl;
   // cout << s2.sqrt(1579205274) << endl;
    cout << s2.sqrt(2147395599) << endl;
    cout << s3.sqrt(2147395599) << endl;
   // cout << s3.sqrt(2147483647) << endl;
   // cout << sqrt(1579205274) << endl;
   // cout << sqrt(2147483647) << endl;

    return 0;
}
