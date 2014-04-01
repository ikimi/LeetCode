#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

// 暴力法 时间复杂度为O（n^2）
// TLE
class Solution1
{
public:
    vector<string> anagrams(vector<string> &strs)
    {
        vector<string> res;
        vector<bool> status;
        int i = 0, j, count, n = strs.size();
        for (j = 0; j < n; j++)
            status.push_back(false);

        while (i < n)
        {
            if (status[i])
            {
                i++;
                continue;
            }
            status[i] = true;
            string temp1 = strs[i];
            sort(temp1.begin(), temp1.end());
            count = 1;
            j = i + 1;
            while (j < n)
            {
                if (status[j])
                {
                    j++;
                    continue;
                }
                string temp2 = strs[j];
                sort(temp2.begin(), temp2.end());
                if (temp2 == temp1)
                {
                    count++;
                    status[j] = true;
                    res.push_back(strs[j]);
                }
                j++;
            }
            if (count > 1)
                res.push_back(strs[i]);
            i++;
        }

        return res;
    }
};

// 利用 map和sort 时间复杂度为O(k) （不算排序时间 对于每一次调用sort都要花费 nlog(n)）
// 228ms
class Solution2
{
public:
    vector<string> anagrams(vector<string> &strs)
    {
        vector<string> res;
        map<string, int> table;
        int i, n;

        i = 0, n = strs.size();
        while (i < n)
        {
            string temp = strs[i];
            sort(temp.begin(), temp.end());
            if (table.find(temp) == table.end())
            {
                table[temp] = i;
            }
            else
            {
                if (table[temp] != -1)
                {
                    res.push_back(strs[table[temp]]);
                    table[temp] = -1;
                }
                res.push_back(strs[i]);
            }
            i++;
        }

        return res;
    }
};

// 因为题目假设所有的字符都是小写字母'a'~'z'
// 所以比较两个字符串是否是anagrams时，可以不使用sort，而是利用int a[26]大小的数组来存储字符串中每个字符出现的次数
// 若两个字符串对应的数组相同 则两个字符串是anagrams的 这里计算数组与数组比较的时间复杂度都是O(n) 要比使用sort更加有效
// 384ms
class Solution3
{
public:
    vector<string> anagrams(vector<string> &strs)
    {
        vector<string> res;
        map<vector<int>, int> table;
        int i, j, n;

        i = 0, n = strs.size();
        while (i < n)
        {
            vector<int> fp(26, 0);
            for (j = 0; j < strs[i].length(); j++)
                fp[strs[i][j] - 'a']++;

            if (table.find(fp) == table.end())
                table[fp] = i;
            else
            {
                if (table[fp] != -1)
                {
                    res.push_back(strs[table[fp]]);
                    table[fp] = -1;
                }
                res.push_back(strs[i]);
            }
            i++;
        }

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;
    vector<string> res;
    vector<string> data;

    data.push_back("abc");
    data.push_back("bca");
    data.push_back("bac");
    data.push_back("bbb");
    data.push_back("bbca");
    data.push_back("abcb");

    //res = s1.anagrams(data);
    //res = s2.anagrams(data);
    res = s3.anagrams(data);

    for (int i = 0; i < res.size(); i++)
        cout << res[i] << endl;

    return 0;
}
