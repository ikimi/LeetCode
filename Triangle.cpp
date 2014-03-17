#include <iostream>
#include <vector>

using namespace std;

// 看题目要求就知道要用DP 所以我们要往DP那里想
// 也就是要考虑子问题的解
// 在这道题中 每处理到一行的每一个元素 我们记录以这个元素为终止的路径的最小和
// 这个和只有两种可能：分别来自上一层的两个节点(注意处理每行的第0个和最后一个元素,因为他们只有一个子问题)
// 时间复杂度O(n^2) 空间复杂度O(n) (n为矩阵的行数)
// 44ms
class Solution1
{
private:
    int Min(int x, int y)
    {
        return (x < y) ? x : y;
    }

public:
    int minimumTotal(vector<vector<int> > &triangle)
    {
        int i, j, row, min;

        row = triangle.size();
        if (!row)
            return 0;

        vector<int> res(row, 0);
        vector<int> temp(row, 0);   // 每次求某一行的解时 要将上一层的结果存储起来
        res[0] = triangle[0][0];
        for (i = 1; i < row; i++)
        {
            for (j = 0; j < i; j++)
                temp[j] = res[j];
            res[0] = temp[0] + triangle[i][0];
            for (j = 1; j < i; j++)
                res[j] = Min(temp[j - 1], temp[j]) + triangle[i][j];
            res[i] = temp[i - 1] + triangle[i][i];
        }
        for (j = min = 0; j < row; j++)
            if (res[j] < res[min])
                min = j;

        return res[min];
    }
};

// 不使用副本 而是使用两个变量来存储上一行的结果
// 空间节省一倍
// 44ms
class Solution2
{
private:
    int Min(int x, int y)
    {
        return (x < y) ? x : y;
    }

public:
    int minimumTotal(vector<vector<int> > &triangle)
    {
        int row;

        row = triangle.size();
        if (!row)
            return 0;
        vector<int> res(row, 0);
        int temp1, temp2, i, j, min;

        res[0] = triangle[0][0];
        for (i = 1; i < row; i++)
        {
            temp1 = res[0], temp2 = res[1];
            res[0] += triangle[i][0];
            for (j = 1; j < i; j++)
            {
                res[j] = Min(temp1, temp2) + triangle[i][j];
                temp1 = temp2, temp2 = res[j + 1];
            }
            res[i] = temp1 + triangle[i][i];
        }

        for (j = min = 0; j < row; j++)
            if (res[j] < res[min])
                min = j;

        return res[min];
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<vector<int > > data;
    data.push_back(vector<int> (1, 2));
    data.push_back(vector<int> (2, 3));
    data.push_back(vector<int> (3, 6));
    data.push_back(vector<int> (4, 4));
    data[1][1] = 4;
    data[2][1] = 5, data[2][2] = 7;
    data[3][1] = 1, data[3][2] = 8, data[3][3] = 3;

    cout << s1.minimumTotal(data) << endl;
    cout << s2.minimumTotal(data) << endl;

    return 0;
}
