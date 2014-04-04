#include <iostream>
#include <cstring>

using namespace std;

// 132ms
class Solution1
{
public:
    string convert(string s, int nRows)
    {
        if (nRows <= 1)
            return s;

        string res;
        int i, j, temp = 2 * nRows - 2, gap, len;
        len = s.length();

        for (i = 0, gap = temp; i < len && i < nRows; i++)
        {
            gap = temp - 2 * i;
            for (j = i; j < len;)
            {
                res += s[j];
                if (!gap)
                {
                    gap = temp - gap;
                    j += gap;
                    continue;
                }
                j += gap;
                gap = temp - gap;
            }
        }

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;

    string res;
    string str1 = "PAYPALISHIRING";
    string str2 = "PAYPALISHIRING";

    res = s1.convert(str1, 3);
    //res = s1.convert(str2, 4);
    cout << res << endl;

    return 0;
}
