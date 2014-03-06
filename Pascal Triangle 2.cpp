#include <iostream>
#include <vector>

using namespace std;

// 利用了O(k)的辅助空间(除去返回数组)
class Solution1
{
public:
    vector<int> getRow(int rowIndex)
    {
        vector<vector<int> > res;
        res.push_back(vector<int> ());
        res.push_back(vector<int> ());
        int i, j;

        res[0].push_back(1);
        res[1].push_back(1), res[1].push_back(1);
        if (!rowIndex)
            return res[0];
        if (rowIndex == 1)
            return res[1];
        for (i = 2; i <= rowIndex; i++)
        {
            if (i % 2)
            {
                res[1].clear();
                res[1].push_back(1);
                for (j = 0; j < i - 1; j++)
                    res[1].push_back(res[0][j] + res[0][j + 1]);
                res[1].push_back(1);
            }
            else
            {
                res[0].clear();
                res[0].push_back(1);
                for (j = 0; j < i - 1; j++)
                    res[0].push_back(res[1][j] + res[1][j + 1]);
                res[0].push_back(1);
            }
        }
        return res[rowIndex % 2];
    }
};

// 利用两个辅助空间 从前向后遍历
class Solution2
{
public:
    vector<int> getRow(int rowIndex)
    {
        vector<int> res;
        res.push_back(1);

        if (!rowIndex)
            return res;

        int i, j, first, second;
        for (i = 1; i <= rowIndex; i++)
        {
            first = 0, second = res[0];
            for (j = 0; j < i;)
            {
                res[j] = first + second;
                first = second;
                second = res[++j];
            }
            res.push_back(1);
        }

        return res;
    }
};

// 不使用辅助空间 与Solution2不同 该解法时从后向前遍历
class Solution3
{
public:
    vector<int> getRow(int rowIndex)
    {
        vector<int> res;
        res.push_back(1);

        if (!rowIndex)
            return res;

        int i, j;
        for (i = 1; i <= rowIndex; i++)
        {
            res.push_back(1);
            for (j = i; j >= 0; j--)
            {
                if (j == i)
                    res[j] = res[j];
                else if (j == 0)
                    res[j] = 1;
                else
                    res[j] = res[j] + res[j - 1];
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

    vector<int> data;

   // data = s1.getRow(10);
   // data = s2.getRow(4);
    data = s3.getRow(4);
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << ' ';
    cout << endl;

    return 0;
}
