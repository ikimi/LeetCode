#include <iostream>

using namespace std;

class Solution1
{
public:
    int lengthOfLastWord(const char *s)
    {
        int start, end, len;

        start = end = len = 0;
        while (s[end])
        {
            if (' ' == s[end])
            {
                if (end - start > 0)
                    len = end - start;
                end++;
                start = end;
            }
            else
                end++;
        }
        if (end - start > 0)    // 当s只有一个单词的情况
            len = end - start;  // WA了一次

        return len;
    }
};

int main()
{
    // test example
    Solution1 s1;
    char s[] = "Hello World";

    cout << s1.lengthOfLastWord(s) << endl;

    return 0;
}
