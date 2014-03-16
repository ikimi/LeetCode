#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// 暴力搜索法 遍历所有的三个数累加的情况
// 时间复杂度O(n^3)
// 432ms
class Solution1
{
public:
    int threeSumClosest(vector<int> &num, int target)
    {
        int sum, i, j, k;

        if (num.size() < 3)
            return -1;

        sum = num[0] + num[1] + num[2];
        for (i = 0; i < num.size() - 2; i++)
            for (j = i + 1; j < num.size() - 1; j++)
                for (k = j + 1; k < num.size(); k++)
                {
                    if (num[i] + num[j] + num[k] == target)
                        return target;
                    if (fabs(num[i] + num[j] + num[k] - target) < fabs(sum - target))
                        sum = num[i] + num[j] + num[k];
                }

        return sum;
    }
};

// 先排序 时间复杂度为O(nlogn)
// 然后选出一个数(共n种可能) 在剩下的 n-1个数中 遍历查找两个数和最接近target的情况 时间复杂度为O()
// 所以 总的时间复杂度为 O(n^2)
// 120ms (性能提升不少)
class Solution2
{
public:
    int threeSumClosest(vector<int> &num, int target)
    {
        int sum, i, low, high;
        sort(num.begin(), num.end());

        sum = num[0] + num[1] + num[num.size() - 1];
        for (i = 0; i < num.size(); i++)
        {
            low = 0, high = num.size() - 1;
            while (low < high)
            {
                if (low == i)
                {
                    low++;
                    continue;
                }
                if (high == i)
                {
                    high--;
                    continue;
                }

                if (num[low] + num[high] + num[i] == target)
                    return target;
                if (fabs(num[low] + num[high] + num[i] - target) < fabs(sum - target))
                    sum = num[low] + num[high] + num[i];
                if (num[low] + num[high] + num[i] > target)
                    high--;
                else
                    low++;
            }
        }

        return sum;
    }
};

// 基于 Solution2的小小的优化
// 36ms
class Solution3
{
public:
    int threeSumClosest(vector<int> &num, int target)
    {
        int sum, i, low, high;
        sort(num.begin(), num.end());

        sum = num[0] + num[1] + num[num.size() - 1];
        for (i = 0; i < num.size(); i++)
        {
            low = i + 1, high = num.size() - 1;
            while (low < high)
            {
                if (num[low] + num[high] + num[i] == target)
                    return target;
                if (fabs(num[low] + num[high] + num[i] - target) < fabs(sum - target))
                    sum = num[low] + num[high] + num[i];
                if (num[low] + num[high] + num[i] > target)
                    high--;
                else
                    low++;
            }
        }

        return sum;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    vector<int> res;
    res.push_back(-1), res.push_back(2), res.push_back(1), res.push_back(-4);

    cout << s1.threeSumClosest(res, 1) << endl;
    cout << s2.threeSumClosest(res, 1) << endl;
    cout << s3.threeSumClosest(res, 1) << endl;

    return 0;
}
