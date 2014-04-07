#include <iostream>
#include <cstring>

using namespace std;

// 暴力法
// 使用前后指针遍历 时间复杂度O(n) 空间复杂度为O(1)
// 80ms
class Solution1
{
private:
    bool isCharacter(char ch)
    {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
            return true;
        return false;
    }

    bool isDigit(char ch)
    {
        if (ch >= '0' && ch <= '9')
            return true;
        return false;
    }

public:
    bool isPalindrome(string s)
    {
        if (!s.length())
            return true;

        int low, high, len;
        len = s.length();
        low = 0, high = len - 1;

        while (low < high)
        {
            if (isCharacter(s[low]) && isCharacter(s[high]))
            {
                if ((s[low] == s[high]) || (s[low] - 'A' + 'a' == s[high]) || (s[low] - 'a' + 'A' == s[high]))
                    low++, high--;
                else
                    return false;
            }
            else if (isDigit(s[low]) && isdigit(s[high]))
            {
                if (s[low] == s[high])
                    low++, high--;
                else
                    return false;
            }
            else
            {
                bool flag = true;
                if (!isCharacter(s[low]) && !isDigit(s[low]))
                    flag = false, low++;
                if (!isCharacter(s[high]) && !isDigit(s[high]))
                    flag = false, high--;
                if (flag)
                    return false;
            }
        }

        return true;
    }
};

int main()
{
    // test example
    Solution1 s1;
    cout << s1.isPalindrome("A man, a plan, a canal: Panama") << endl;
    cout << s1.isPalindrome("race a car") << endl;
    cout << s1.isPalindrome("") << endl;
    cout << s1.isPalindrome("1a2") << endl;
    cout << s1.isPalindrome("ab2a") << endl;

    return 0;
}
