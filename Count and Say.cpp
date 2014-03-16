#include <iostream>
#include <string>

using namespace std;

// 模拟法
// 双字符串
// 28m
class Solution1
{
public:
    string countAndSay(int n)
    {
        string str[2];
        int i, j, count, first, second;

        if (n <= 0)
            return str[0];

        i = 1, str[1] = "1";
        while (i < n)
        {
            if (i % 2)
                first = 1, second = 0;
            else
                first = 0, second = 1;
            j = 0, str[second] = "";
            while (j < str[first].size())
            {
                count = 1;
                while (str[first][j] == str[first][j + 1])
                    j++, count++;
                str[second] += count + '0';
                str[second] += str[first][j];
                j++;
            }
            i++;
        }

        return str[n % 2];
    }
};

int main()
{
    Solution1 s1;

    cout << s1.countAndSay(2) << endl;
    //cout << s.c_str() << endl;

    return 0;
}
