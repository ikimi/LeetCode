#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 与Cinbination Sum 思路相同
// 88ms
class Solution1
{
private:
    vector<vector<int> > res;
    vector<int> temp;
    void helper(vector<int> &num, vector<int> &temp, int index, int target)
    {
        if (target < 0)
            return ;
        if (target == 0)
        {
            res.push_back(temp);
            return ;
        }
        if (index >= num.size())
            return ;

        temp.push_back(num[index]);
        helper(num, temp, index + 1, target - num[index]);
        temp.pop_back();

        for (int i = index + 1; i < num.size(); i++)
        {
            if (num[i] != num[index])
            {
                temp.push_back(num[i]);
                helper(num, temp, i + 1, target - num[i]);
                temp.pop_back();
                index = i;
            }
        }
    }

public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target)
    {
        vector<int> temp;
        sort(num.begin(), num.end());
        helper(num, temp, 0, target);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;

    vector<vector<int> > res;
    vector<int> data;
    data.push_back(4);
    data.push_back(1);
    data.push_back(1);
    data.push_back(4);
    data.push_back(4);
    data.push_back(4);
    data.push_back(4);
    data.push_back(2);
    data.push_back(3);
    data.push_back(5);

    res = s1.combinationSum2(data, 10);
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            cout << res[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
