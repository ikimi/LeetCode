#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Node
{
    int index;
    int val;
    Node(int x, int y) : index(x), val(y) {}
};

bool compare (const Node &a, const Node &b)
{
    return a.val < b.val;
}

// 暴力搜
// 时间复杂度为O(n^2)
// TLE
class Solution1
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        int i, j, n;
        vector<int> res;

        n = numbers.size();
        for (i = 0; i < n; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (target == numbers[i] + numbers[j])
                {
                    res.push_back(i + 1);
                    res.push_back(j + 1);
                    break;
                }
            }
        }

        return res;
    }
};

// 采用二分的方法
// 先排序O(nlogn) 在用二分查找O(nlogn)
// 时间复杂度O(nlogn) 空间复杂度O(n) (因为创建了Node数组)
// 28ms
class Solution2
{
private:
    int binarySearch(vector<Node> &data, int low, int high, int target)
    {
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (data[mid].val == target)
                return mid;
            else if (target < data[mid].val)
                high = mid - 1;
            else
                low = mid + 1;
        }

        return -1;
    }

public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        int index1, index2, n;
        vector<int> res;
        vector<Node> data;

        n = numbers.size();
        for (int i = 0; i < n; i++)
            data.push_back(Node(i, numbers[i]));
        sort(data.begin(), data.end(), compare);

        for (index1 = 0; index1 < n; index1++)
        {
            if ((index2 = binarySearch(data, index1 + 1, n - 1, target - data[index1].val)) != -1)
            {
                res.push_back(data[index1].index + 1);
                res.push_back(data[index2].index + 1);
                if (res[0] > res[1])
                {
                    int pos = res[0];
                    res[0] = res[1];
                    res[1] = pos;
                }
                break;
            }
        }

        return res;
    }
};

// Solution2 方法在查找匹配的数对时 采用二分方法 时间复杂度为O(nlogn)
// 这一步可以使线性查找的方法 时间复杂度为O(n)
// 时间复杂度O(nlogn) 空间复杂度O(n)
// 76ms
class Solution3
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        int i, n, low, high;
        vector<Node> data;
        vector<int> res;

        n = numbers.size();
        for (i = 0; i < n; i++)
            data.push_back(Node(i, numbers[i]));

        sort(data.begin(), data.end(), compare);

        low = 0, high = n - 1;
        while (low < high)
        {
            if (data[low].val + data[high].val == target)
            {
                res.push_back(data[low].index + 1);
                res.push_back(data[high].index + 1);
                if (res[0] > res[1])
                {
                    int pos = res[0];
                    res[0] = res[1];
                    res[1] = pos;
                }
                break;
            }
            else if (data[low].val + data[high].val < target)
                low++;
            else
                high--;
        }

        return res;
    }
};

// 利用map可实现O(n)的时间复杂度
// map<int, vector<int>> table 索引值是元素的值，vector中的值是索引值的索引
// 第一遍遍历将数组元素映射到map中
// 第二遍遍历匹配数对
// 时间复杂度O(n) 空间复杂度O(n)
// 144ms
class Solution4
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        int i, n;

        vector<int> res;
        map<int, vector<int> > table;

        n = numbers.size();
        for (i = 0; i < n; i++)
        {
            map<int, vector<int> > :: iterator it = table.find(numbers[i]);
            if (it == table.end())
                table.insert(pair<int, vector<int> >(numbers[i], vector<int>(1, i)));
            else
                it->second.push_back(i);
        }

        for (i = 0; i < n; i++)
        {
            map<int, vector<int> > :: iterator it = table.find(target - numbers[i]);
            if (it != table.end())
            {
                for (int j = 0; j < it->second.size(); j++)
                    if (i != it->second[j])
                    {
                        res.push_back(i + 1);
                        res.push_back(it->second[j] + 1);
                        if (res[0] > res[1])
                        {
                            int pos = res[0];
                            res[0] = res[1];
                            res[1] = pos;
                        }
                        return res;
                    }
            }
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
    Solution4 s4;

    vector<int> res;
    vector<int> numbers;

    numbers.push_back(3);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(5);

    //res = s1.twoSum(numbers, 9);
    //res = s2.twoSum(numbers, 6);
   // res = s3.twoSum(numbers, 6);
    res = s4.twoSum(numbers, 6);

    for (int i = 0; i < res.size(); i++)
        cout << res[i] << ' ';
    cout << endl;

    return 0;
}
