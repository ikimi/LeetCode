#include <iostream>
#include <vector>

using namespace std;

// 寻找序列的所有单调递增序列 找出每个序列的最小值 和 最大值 求出最大差值 然后累加
// 时间复杂度微 O(n) 空间复杂度为 O(1)
class Solution1
{
    public:
        int maxProfit(vector <int> &prices)
        {
            if (prices.size() < 2)
                return 0;

            int min, max, res = 0;
            unsigned i;

            for (i = min = max = 0; i < prices.size() - 1; i++)
            {
                if (prices[i + 1] > prices[i])
                    max = i + 1;
                else
                {
                    res += prices[max] - prices[min];
                    max = min = i + 1;
                }
            }
            if (min != max)
                res += prices[max] - prices[min];
            return res;
        }
};

int main()
{
    // test examples
    Solution1 s1;
    vector <int> prices;
    //prices.push_back(2);
   // prices.push_back(1);
   // prices.push_back(7);
   // prices.push_back(1);
   // prices.push_back(5);
   // prices.push_back(7);
   // prices.push_back(8);
   // prices.push_back(1);
   prices.push_back(1);
   prices.push_back(2);
    cout << s1.maxProfit(prices) << endl;
    return 0;
}
