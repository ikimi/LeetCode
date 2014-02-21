#include <iostream>

using namespace std;

// 题目不难 关键是理解罗马数字的表示方法 参见 http://zh.wikipedia.org/wiki/%E7%BD%97%E9%A9%AC%E6%95%B0%E5%AD%97
class Solution1
{
    private:
        int romanValue(char c)
        {
            switch(c)
            {
                case 'I' : return 1;
                case 'V' : return 5;
                case 'X' : return 10;
                case 'L' : return 50;
                case 'C' : return 100;
                case 'D' : return 500;
                case 'M' : return 1000;
                default : return 0;
            }
        }

    public:
        int romanToInt(string s)
        {
            int i, sum, cur, len;

            sum = cur = 0;
            len = s.length();
            for (i = 0; i < len; i++)
            {
                if (cur < romanValue(s[i]))
                    sum -= cur;
                else
                    sum += cur;
                cur = romanValue(s[i]);
            }
            sum += cur;

            return sum;
        }
};

int main()
{
    // test example
    Solution1 s1;

    string a("VII");
    string b("IX");
    string c("XCIX");

    cout << s1.romanToInt(a) << endl;
    cout << s1.romanToInt(b) << endl;
    cout << s1.romanToInt(c) << endl;

    return 0;
}
