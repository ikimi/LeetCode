#include <iostream>

using namespace std;

//
class Solution1
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0)          // 负数在 LeetCode 中定义为不是回文数
            return false;   // 在这 WA 了一次

        int temp, y;

        temp = x, y = 0;
        while (temp)   // 可能溢出
        {
            y *= 10;
            y += temp % 10;
            temp /= 10;
        }
        if (x ==  y)
            return true;
        return false;
    }
};

// 判断最高位 和 最低位 是否相同
class Solution2
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0)
            return false;

        int high, low;

        high = low = 1;
        while (x / 10 >= high)
            high *= 10;

        while (x > 9)
        {
            if ((x / high) != (x % 10))
                return false;
            x %= high;
            x /= 10;
            high /= 100;
        }

        return true;
    }
};

int main()
{
    // test example
    Solution1 s1;

    cout << s1.isPalindrome(1234321) << endl;
    cout << s1.isPalindrome(-1234321) << endl;
    cout << s1.isPalindrome(123421) << endl;
    cout << s1.isPalindrome(-2147447412) << endl;

    return 0;
}
