#include <iostream>
#include <vector>

using namespace std;

// 没什么可说的 模拟大数加法 而且一个加数为1
class Solution1
{
public:
    vector<int> plusOne(vector<int> &digits)
    {
        if (!digits.size())
        {
            digits.push_back(1);
            return digits;
        }
        int i, flag, n;

        n = digits.size();
        for (i = n - 1, flag = 1; i >=0; i--)
        {
            digits[i] += flag;
            if (digits[i] >= 10)
            {
                flag = 1;
                digits[i] %= 10;
            }
            else
            {
                flag = 0;
                break;
            }
        }

        if (i < 0 && flag)
        {
            digits.insert(digits.begin(), flag);
        }

        return digits;
    }
};

int main()
{
    // test example
    Solution1 s1;
    vector<int> digits(9, 4);

    digits = s1.plusOne(digits);
    for (int i = 0; i < digits.size(); i++)
        cout << digits[i];
    cout << endl;

    return 0;
}
