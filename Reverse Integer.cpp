#include <iostream>

using namespace std;

class Solution
{
    public:
        int reverse(int x)
        {
            int sign = 1, res = 0, temp;
            bool flag = false;

            if (x == 0)
                return 0;

            if (x < 0)
            {
                sign = -1;
                x = -x;
            }

            while (x)
            {
                temp = x % 10;
                if (temp)
                {
                    if (!flag)
                        flag = true;
                    res = 10 * res + temp;
                }
                else
                {
                    if (flag)
                        res *= 10;
                }
                x /= 10;
            }

            return sign * res;
        }
};

int main()
{
    // test example
    Solution s;
    cout << s.reverse(-000) << endl;
    return 0;
}
