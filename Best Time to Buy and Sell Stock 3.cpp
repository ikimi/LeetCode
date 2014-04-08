#include <iostream>
#include <vector>

using namespace std;

// 暴力法
// 将prices数组分为两段，每一段选取收益最大值 相加即可
// 共n种分段方法 每一次分段都要求两段的最大收益
// 时间复杂度为O(n^2)
// TLE
class Solution1
{
private:
    int helper(vector<int> &prices, int low, int high)
    {
        if (low >= high)
            return 0;

        int cur, min, i;
        cur = min = 0;
        i = low;
        while (i < high)
        {
            cur += prices[i] - prices[i + 1];
            if (cur > 0)
                cur = 0;
            else
                if (cur < min)
                    min = cur;
            i++;
        }

        return -min;
    }

public:
    int maxProfit(vector<int> &prices)
    {
        int mid, len, max, cur;

        len = prices.size(), mid = 0;
        cur = max = 0;
        while (mid < len)
        {
            cur = helper(prices, 0, mid) + helper(prices, mid, len);
            if (cur > max)
                max = cur;
            mid++;
        }

        return max;
    }
};

// 发现O(n^2)的时间复杂度不是最好的 我们就要降低时间复杂度
// 还是分段的思想 只不过为了加快每一段最大利润的计算 我们需要将这些中间结果记录下来
// left 数组记录0~1 0~2 ... 0~n每一段的对大利润 我们可以在知道 i~j 的前提下 在O（1）时间内计算出i+1 ~ j
// right 数组记录n 0~n 1~n ... n-1~n每一段的最大利润 但是我们如何在知道了i~n的前提下知道i+1~n的值呢？
// 在这里我们可以反向求解 即我们可以先求出i+1~n 再在O（1）的时间内求出 i~n的值
// 程序对prices进行三次遍历 每次时间复杂度都是O(n)
// 时间复杂度O(n) 空间复杂度O(n)
// 52ms
class Solution2
{
public:
    int maxProfit(vector<int> &prices)
    {
        int i, len = prices.size();
        vector<int> left(len, 0);
        vector<int> right(len, 0);

        int min, cur, max;
        for (i = 1, min = cur = 0; i < len; i++)
        {
            cur += prices[i - 1] - prices[i];
            if (cur > 0)
                cur = 0;
            else
                if (min > cur)
                    min = cur;
            left[i] = -min;
        }

        for (i = len - 2, max = cur = 0; i >= 0; i--)
        {
            cur += prices[i + 1] - prices[i];
            if (cur < 0)
                cur = 0;
            else
                if (cur > max)
                    max = cur;
            right[i] = max;
        }

        for (i = max = 0; i < len; i++)
            if (left[i] + right[i] > max)
                max = left[i] + right[i];

        return max;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<int> prices;
    prices.push_back(1);prices.push_back(4);
    prices.push_back(5);prices.push_back(0);
    prices.push_back(2);prices.push_back(6);
    cout << s1.maxProfit(prices) << endl;
    cout << s2.maxProfit(prices) << endl;

    return 0;
}
