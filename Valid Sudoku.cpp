#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution1
{
public:
    bool isValid(string s)
    {
        stack<char> sta;

        int i = 0, n = s.length();
        while (i < n)
        {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')
                sta.push(s[i]);
            else
            {
                if (s[i] == ')')
                {
                    if (sta.empty() || sta.top() != '(')
                        return false;
                    sta.pop();
                }
                else if (s[i] == ']')
                {
                    if (sta.empty() || sta.top() != '[')
                        return false;
                    sta.pop();
                }
                else
                {
                    if (sta.empty() || sta.top() != '{')
                        return false;
                    sta.pop();
                }
            }
            i++;
        }
        if (!sta.empty())
            return false;
        return true;
    }
};

int main()
{
    // test example
    Solution1 s1;

    string s = "(())}]";
    cout << s1.isValid(s) << endl;

    return 0;
}
