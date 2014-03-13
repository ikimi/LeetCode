#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

// 第一种去重的方法：利用set来判断集合中是否已存在一个结果
// 64ms
class Solution1
{
private:
    void subsets(vector<vector<int> > &res, vector<int> &data, vector<int> &S, set<vector<int> > &check, int start)
    {
        if (start >= S.size())
        {
            set<vector<int> > :: iterator it;
            it = check.find(data);      // 集合 set find 操作
            if (it == check.end())
            {
                res.push_back(data);
                check.insert(data);
            }

            return ;
        }

        data.push_back(S[start]);
        subsets(res, data, S, check, start + 1);
        data.pop_back();
        subsets(res, data, S, check, start + 1);
    }

public:
    vector<vector<int> > subsetsWithDup(vector<int> &S)
    {
        vector<vector<int> > res;
        vector<int> data;
        set<vector<int> > check;

        sort(S.begin(), S.end());
        subsets(res, data, S, check, 0);

        return res;
    }
};

// 不利用 set 去重
// 48ms
class Solution2
{
private:
    void subset(vector<vector<int> > &res, vector<int> &data, vector<int> &S, int start)
    {
        if (start >= S.size())
        {
            res.push_back(data);
            return ;
        }

        data.push_back(S[start]);
        subset(res, data, S, start + 1);
        data.pop_back();
        while ((start + 1 < S.size()) && (S[start] == S[start + 1]))
            start++;
        subset(res, data, S, start + 1);
    }

public:
    vector<vector<int> > subsetsWithDup(vector<int> &S)
    {
        vector<vector<int> > res;
        vector<int> data;

        sort(S.begin(), S.end());
        subset(res, data, S, 0);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<vector<int> > res;
    vector<int> S;
    S.push_back(1), S.push_back(2), S.push_back(2);

    // res = s1.subsetsWithDup(S);
    res = s2.subsetsWithDup(S);
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            cout << res[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
