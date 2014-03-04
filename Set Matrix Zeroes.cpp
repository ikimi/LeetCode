#include <iostream>
#include <vector>

using namespace std;

// 利用temp数组存放matrix的副本 当遍历matrix数组遇到0元素时，将temp数组相应的行和列设为0
// 时间复杂度O(m*n) 空间复杂度O(m*n)
class Solution1
{
public:
    void setZeroes(vector<vector<int> > &matrix)
    {
        int i, j, k, m, n;
        vector<vector<int> > temp;

        m = matrix.size(), n = matrix[0].size();
        for (i = 0; i < m; i++)
            temp.push_back(matrix[i]);

        for (i = 0; i < m; i++)
            for (j = 0; j < n; j++)
                if (!matrix[i][j])
                {
                    k = n;
                    while (k--)
                        temp[i][k] = 0;
                    k = m;
                    while (k--)
                        temp[k][j] = 0;
                }

        for (i = 0; i < m; i++)
            for (j = 0; j < n; j++)
                matrix[i][j] = temp[i][j];
    }
};

// 利用状态数组记录某行/某列是否被全赋为0
class Solution2
{
public:
    void setZeroes(vector<vector<int> > &matrix)
    {
        int m, n, i, j;

        m = matrix.size(), n = matrix[0].size();
        vector<bool> line(n, false), row(m, false);

        for (i = 0; i < m; i++)
            for (j = 0; j < n; j++)
                if (!matrix[i][j])
                {
                    line[j] = true;
                    row[i] = true;
                }
        for (i = 0; i < m; i++)
            if (row[i])
                for (j = 0; j < n; j++)
                    matrix[i][j] = 0;
        for (j = 0; j < n; j++)
            if (line[j])
                for (i = 0; i < m; i++)
                    matrix[i][j] = 0;
    }
};

// 辅助空间大小为常数 只有两种情况：(1)采用常数个变量存储 (2)原有的空间可以再利用
// 本题就是第二种情况。我们利用第一行和第一列来像方法（2）那样记录每行 每列是否存在0
// 而0行和0列的值通过两个bool值确定
class Solution3
{
public:
    void setZeroes(vector<vector<int> > &matrix)
    {
        bool line1, row1;
        int i, j, m, n;

        m = matrix.size(), n = matrix[0].size();
        line1 = false, row1 = false;

        for (j = 0; j < n; j++)
            if (!matrix[0][j])
            {
                row1 = true;
                break;
            }
        for (i = 0; i < m; i++)
            if (!matrix[i][0])
            {
                line1 = true;
                break;
            }
        for (i = 0; i < m; i++)
            for (j = 0; j < n; j++)
                if (!matrix[i][j])
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }

        for (i = 1; i < m; i++)
            if (!matrix[i][0])
                for (j = 1; j < n; j++)
                    matrix[i][j] = 0;
        for (j = 1; j < n; j++)
            if (!matrix[0][j])
                for (i = 1; i < m; i++)
                    matrix[i][j] = 0;

        if (line1)
            for (i = 0; i < m; i++)
                matrix[i][0] = 0;
        if (row1)
            for (j = 0; j < n; j++)
                matrix[0][j] = 0;

    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;
    vector<vector<int> > data;

    for (int i = 0; i < 10; i++)
            data.push_back(vector<int> (10, 1));
    data[5][0] = data[4][3] = data[4][6] = data[6][2] = 0;

    //s1.setZeroes(data);
    //s2.setZeroes(data);
    s3.setZeroes(data);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            cout << data[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
