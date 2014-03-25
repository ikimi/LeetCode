#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

// 空间复杂度O(1)
// 152ms
class Solution1
{
private:
    void helper(vector<vector<int> > &res, vector<int> data, int index)
    {
        if (index >= data.size())
        {
            res.push_back(data);
            return ;
        }

        int i, j, n, temp;
        sort(data.begin() + index, data.end()); // WA了两次
        helper(res, data, index + 1);
        j = index, n = data.size();
        for (i = index + 1; i <= n - 1; i++)
        {
            if (data[i] != data[j])
            {
                temp = data[index];
                data[index] = data[i];
                data[i] = temp;

                helper(res, data, index + 1);

                temp = data[index];
                data[index] = data[i];
                data[i] = temp;
                j = i;
            }
        }
    }

public:
    vector<vector<int> > permuteUnique(vector<int> &num)
    {
        vector<vector<int> > res;
        sort(num.begin(), num.end());
        helper(res, num, 0);

        return res;
    }
};

// 空间复杂度O(n)
// 144ms
class Solution2
{
private:
    int data[100];
    bool status[100];
    vector<vector<int> > res;

    void helper(int length, int index, vector<int> &num)
    {
        if (index >= length)
        {
            vector<int> temp;
            for (int i = 0; i < length; i++)
                temp.push_back(data[i]);
            res.push_back(temp);
            return ;
        }

        for (int i = 0; i < length; i++)
        {
            if (status[i])
            {
                data[index] = num[i];
                status[i] = false;
                helper(length, index + 1, num);
                status[i] = true;

                while (i < length - 1 && num[i] == num[i + 1])
                    i++;
            }
        }
    }

public:
    vector<vector<int > > permuteUnique(vector<int> &num)
    {
        sort(num.begin(), num.end());
        memset(status, true, sizeof(status));
        helper(num.size(), 0, num);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<vector<int> > res;
    vector<int> data;

    data.push_back(1), data.push_back(0), data.push_back(0), data.push_back(0), data.push_back(9);
    //res = s1.permuteUnique(data);
    res = s2.premuteUnique(data);

    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            cout << res[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
