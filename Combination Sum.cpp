#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 递归迭代法
// 遍历所有的情况
// 网上的代码基本上也都是DFS
class Solution1
{
private:
    void combination(vector<vector<int> > &res, vector<int> &candidates, vector<int> &data, int start, int end, int target)
    {
        if (start > end)
            return ;
        if (!target)   // 调试了很久
        {
            res.push_back(data);
            return ;
        }
        if (candidates[start] > target)
            return ;


        for (int i = start; i <= end; i++)
        {
            data.push_back(candidates[i]);
            combination(res, candidates, data, i, end, target - candidates[i]);
            data.pop_back();
        }
    }

public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int> > res;

        if (!candidates.size())
            return res;

        vector<int> data;
        sort(candidates.begin(), candidates.end());
        combination(res, candidates, data, 0, candidates.size() - 1, target);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;

    vector<vector<int> > res;
    vector<int> data;
    data.push_back(2);
    data.push_back(3);
    data.push_back(6), data.push_back(7);

    res = s1.combinationSum(data, 13);
    cout << res.size() << endl;

    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            cout << res[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
