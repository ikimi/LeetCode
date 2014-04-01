#include <iostream>
#include <cstring>

using namespace std;

// 字符包括除字母以外的其他字符
// 题目理解错了 题目描述的子串应该是连续子串而不是任意子串
// 下面是针对非连续子串的结果（错误答案）
class Solution1
{
public:
    int lengthOfLongestSubstring(string s)
    {
        bool res[128];
        int count = 0;
        memset(res, false, sizeof(res));

        for (int i = 0; i < s.length(); i++)
            if (!res[s[i]])
                res[s[i]] = true;
        for (int i = 0; i < 128; i++)
            if (res[i])
                count++;

        return count;
    }
};

// 144ms
class Solution2
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int res[128], max, i, j, n;

        memset(res, -1, sizeof(res));
        max = i = j = 0;
        n = s.length();

        while (j < n)
        {
            while ((j < n) && (res[s[j]] == -1))
            {
                res[s[j]] = j;
                j++;
            }
            if (j >= n)
                break;
            if (max < j - i)
                max = j - i;
            while (i <= res[s[j]])
                res[s[i++]] = -1;
        }
        if (max < j - i)    // 忘记处理结束情况 WA了一次
            max = j - i;

        return max;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    //string s = "abcabcbb";
    string s = "qopubjguxhxdipfzwswybgfylqvjzhar";
   // cout << s1.lengthOfLongestSubstring(s) << endl;
    cout << s2.lengthOfLongestSubstring(s) << endl;

    return 0;
}
