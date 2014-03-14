#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 暴力法 时间复杂度O(n*m) n为strs的大小, m为strs中长度最小字符串的长度
// 从第0个字符开始依次遍历所有的字符串 然后比较下一个字符 以此类推
// 40ms
class Solution1
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        int i, j, n;
        string res;

        n = strs.size();
        if (!n)         // 没有判断 strs 是否为空. WA 了一次.
            return res;

        for (j = 0; ;j++)
        {
            for (i = 0; i < n;)
            {
                if (strs[i][j] && strs[i][j] == strs[0][j])
                {
                    i++;
                }
                else
                    return res;
            }
            res += strs[0][j];
        }

        return res;
    }
};

// Divide-and-Conquer 分治算法
// 与 merge 排序思想相同
// 时间复杂度为O(nlogn) (当 n 和 m 成比例的时候) 但空间复杂度较大
// 20ms
class Solution2
{
private:
    string lonComPre(vector<string> &strs, int low, int high)
    {
        if (low >= high)
            return strs[low];

        int mid = (low + high) / 2;

        string str1 = lonComPre(strs, low, mid);
        string str2 = lonComPre(strs, mid + 1, high);
        string res;

        for (int i = 0; str1[i] && str2[i] && str1[i] == str2[i];)
            res += str1[i++];

        return res;
    }

public:
    string longestCommonPrefix(vector<string> &strs)
    {
        string res;

        if (!strs.size())
            return res;
        res = lonComPre(strs, 0, strs.size() - 1);

        return res;
    }
};

// 也可以先选出长度最小的子串 然后从第0个字符串开始比较
// 每次比较更新 最长前缀的长度 用于下一次比较
// 时间复杂度跟 Solution1 一样
// 代码 略

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<string> strs;
    string res;

    strs.push_back("hello world");
    strs.push_back("hell ew");
    strs.push_back("helr");

    //res = s1.longestCommonPrefix(strs);
    res = s2.longestCommonPrefix(strs);
    cout << res << endl;

    return 0;
}
