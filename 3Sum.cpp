#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 三层for循环
// 先排序O(nlogn) 然后遍历所有情况O(n^3)
// 308ms
class Solution1
{
public:
    vector<vector<int> > threeSum(vector<int> &num)
    {
        vector<vector<int> > res;
        vector<int> tmp;
        int i, j, k, n, temp;

        sort(num.begin(), num.end());
        n = num.size();
        for (i = 0; i < n;)
        {
            for (j = i + 1; j < n;)
            {
                for (k = j + 1; k < n;)
                {
                    if (num[i] + num[j] + num[k] == 0)
                    {
                        tmp.clear();
                        tmp.push_back(num[i]);
                        tmp.push_back(num[j]);
                        tmp.push_back(num[k]);
                        res.push_back(tmp);
                    }
                    if (num[i] + num[j] + num[k] > 0)
                        break;
                    temp = num[k];
                    while (k < n && temp == num[k])
                        k++;
                }
                temp = num[j];
                while (j < n && temp == num[j])
                    j++;
            }
            temp =  num[i];
            while (i < n && temp == num[i])
                i++;
        }

        return res;
    }
};

// 一层for循环
// 时间复杂度O(n^2)
// 264ms
class Solution2
{
public:
    vector<vector<int> > threeSum(vector<int> &num)
    {
        vector<vector<int> > res;
        vector<int> tmp;

        int i, low, high, n;

        sort(num.begin(), num.end());
        n = num.size();
        for (i = 0; i < n;)
        {
            low = i + 1, high = n - 1;
            while (low < high)
            {
                if (num[i] + num[low] + num[high] == 0)
                {
                    tmp.clear();
                    tmp.push_back(num[i]);
                    tmp.push_back(num[low]);
                    tmp.push_back(num[high]);
                    res.push_back(tmp);

                    int temp = num[low];
                    while (low < high && temp == num[low])
                        low++;
                    temp = num[high];
                    while (low < high && temp == num[high])
                        high--;
                }
                else if (num[i] + num[low] + num[high] > 0)
                    high--;
                else
                    low++;
            }
            int temp = num[i];
            while (i < n && temp == num[i])
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
    vector<vector<int> > res;
    vector<int> num;

    num.push_back(-1);num.push_back(0);
    num.push_back(1);num.push_back(2);
    num.push_back(-1);num.push_back(-4);

    //res = s1.threeSum(num);
    res = s2.threeSum(num);

    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            cout << res[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
