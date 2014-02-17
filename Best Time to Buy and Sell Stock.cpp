#include <iostream>
#include <vector>

using namespace std;

// 采用分治法递归求解 时间复杂度 O（n logn）
// 因为在 分 的时候要用 O(n) 的时间来查找子数组的最大/最小值
class Solution1
{
    private:
        int find_profit(vector <int> &prices, int start, int end)
        {
            int mid, i, min, max, max_profit, max_profit1, max_profit2;

            if (start >= end)
                return 0;

            mid = (start + end) / 2;
            for (i = min = start; i <= mid; i++)
                if (prices[i] < prices[min])
                    min = i;
            for (i = max = mid + 1; i <= end; i++)
                if (prices[i] > prices[max])
                    max = i;

            max_profit1 = find_profit(prices, start, mid);
            max_profit2 = find_profit(prices, mid + 1, end);
            max_profit = (max_profit1 > max_profit2) ? max_profit1 : max_profit2;
            return (max_profit > prices[max] - prices[min]) ? max_profit : (prices[max] - prices[min]);
        }

    public:
        int maxProfit(vector <int> &prices)
        {
            return find_profit(prices, 0, prices.size() - 1);
        }
};

// 分治法递归求解 时间复杂度O（n）
// 寻找子树组 最小/最大值 不需要遍历 所以不需要O（n）时间
class Solution2
{
    private:
        int find_maxProfit(vector <int> &prices, int start, int end, int *min, int *max)
        {
            int mid, max1, max2, min_left, min_right, max_left, max_right, cross;

            if (start >= end)
            {
                *min = *max = prices[start];
                return 0;
            }

            mid = (end + start) / 2;
            max1 = find_maxProfit(prices, start, mid, &min_left, &max_left);
            max2 = find_maxProfit(prices, mid + 1, end, &min_right, &max_right);

            cross = max_right - min_left;
            if (cross < 0)
                cross = 0;
            *min = (min_left < min_right) ? min_left : min_right;
            *max = (max_left > max_right) ? max_left : max_right;

            max1 = (max1 > max2) ? max1 : max2;
            return (max1 > cross) ? max1 : cross;
        }

    public:
        int maxProfit(vector <int> &prices)
        {
            int min, max, len;
            len = prices.size();
            if (!len)
                return 0;
            return find_maxProfit(prices, 0, len - 1, &min, &max);
        }
};

// 转化法 转化为求数组的最小连续子数组 时间复杂度微O(n) 但空间复杂度为 O(n)
class Solution3
{
    public:
    int maxProfit(vector <int> &prices)
    {
        if (prices.size() < 2)
            return 0;

        int curSum = 0, minSum = 0;
        unsigned i;
        vector <int> data;

        for (i = 0; i < prices.size() - 1; i++)
            data.push_back(prices[i] - prices[i + 1]);

        for (i = 0; i < data.size(); i++)
        {
            curSum += data[i];

            if (curSum > 0)
                curSum = 0;
            if (curSum < minSum)
                minSum = curSum;
        }
        if (!minSum)
            minSum = 0;
        return -minSum;
    }
};

// DP 方法 时间复杂度 O(n) 空间复杂度O(1)
class Solution4
{
    public:
        int maxProfit(vector <int> &prices)
        {
            if (prices.size() < 2)
                return 0;

            int min = prices[0], minDiff = prices[0] - prices[1], curDiff;
            unsigned i;

            for (i = 2; i < prices.size(); i++)
            {
                if (min > prices[i - 1])
                    min = prices[i - 1];
                curDiff = min - prices[i];
                if (curDiff < minDiff)
                    minDiff = curDiff;
            }
            if (minDiff > 0)
                return 0;
            return -minDiff;
        }
};

int main()
{
    // test example
    Solution4 s4;
    vector <int> prices;
    prices.push_back(2);
    prices.push_back(1);
    prices.push_back(7);
    prices.push_back(1);
    prices.push_back(5);
    prices.push_back(7);
    prices.push_back(8);
    prices.push_back(1);
    cout << s4.maxProfit(prices) << endl;

    return 0;
}
