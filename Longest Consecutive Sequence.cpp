#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

// 排序法 时间复杂度O(nlogn)
// 在一些小细节上WA了4次 注意数组元素可以重复
// 对于这种前后元素比较的算法 注意结束条件(否则会落下情况)
// 88ms
class Solution1
{
public:
    int longestConsecutive(vector<int> &num)
    {
        int count, temp, i, n;

        n = num.size();
        if (n == 1 || n == 0)
            return n;

        sort(num.begin(), num.end());
        for (i = count = 0, temp = 1; i + 1 < n; i++)
        {
            if (num[i] == num[i + 1])   // WA了一次
                continue;
            else if (num[i] + 1 == num[i + 1])
                temp++;
            else
            {
                if (temp > count)
                    count = temp;
                temp = 1;   // WA了一次
            }
        }

        if (temp > count)   // WA了一次
            count = temp;

        return count;
    }
};

// 利用hash set(查找添加删除的时间复杂度都是O(1))
// 对于某个数x 我们分别从x-1 和 x+1两个方向上查找最长连续序列
// 同时从hash set将这些元素删除 否则会出现重复查找的问题
// 综上 时间复杂度为O(n) 空间复杂度O(n)
// 84ms
class Solution2
{
public:
    int longestConsecutive(vector<int> &num)
    {
        if (num.size() <= 1)
            return num.size();

        int i, max, cur, temp;
        unordered_set<int> set;
        unordered_set<int> :: const_iterator iter;

        for (i = 0; i < num.size(); i++)
        {
            if ((iter = set.find(num[i])) == set.end())
                set.insert(num[i]);
        }

        for (i = max = 0; i < num.size(); i++)
        {
            cur = 0, temp = num[i];
            if ((iter = set.find(num[i])) != set.end())
            {
                set.erase(temp);
                cur++;
            }
            else
                continue;

            while (1)
            {
                if ((iter = set.find(temp - 1)) == set.end())
                    break;
                set.erase(temp - 1);
                temp--, cur++;
            }
            temp = num[i];
            while (1)
            {
                if ((iter = set.find(temp + 1)) == set.end())
                    break;
                set.erase(temp + 1);
                temp++, cur++;
            }
            if (cur > max)
                max = cur;
        }

        return max;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<int> data;
    data.push_back(1), data.push_back(2), data.push_back(0);
    data.push_back(1); //data.push_back(3), data.push_back(2);

    cout << s1.longestConsecutive(data) << endl;

    return 0;
}
