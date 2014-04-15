#include <iostream>
#include <vector>

using namespace std;

// 暴力法
// 逐行遍历每一个节点(i, j), 如果(i, j)位置为0，则以(i, j)为左上角的矩形的最大面积为0，因为这个矩形第一个块就是0
// 如果(i, j)位置为1,需要求解以(i，j)为左上角的矩形的最大面积
// 在求子矩形的最大面积的时候，仍然逐行遍历
// 在每一行中，需要记录第一个为O列坐标，并与最小的为1的列坐标值相比，更新其大小，在逐行遍历过城中记录最大矩形面积
// 时间复杂度为O(n^4) 空间复杂度为O(1)
// 288ms
class Solution1
{
private:
    int m, n;
    int maximalRectangleHelper(vector<vector<char> > &matrix, int row, int col)
    {
        int minWidth = n, maxArea = 0;
        for (int i = row; i < m && matrix[i][col] == '1'; i++)
        {
            int j = col;
            while (j < n && matrix[i][j] == '1')
                j++;
            if (j - 1 < minWidth)
                minWidth = j - 1;

            int area = (i - row + 1) * (minWidth - col + 1);
            if (area > maxArea)
                maxArea = area;
        }

        return maxArea;
    }

public:
    int maximalRectangle(vector<vector<char> > &matrix)
    {
        m = matrix.size();
        if (!m)
            return 0;
        n = matrix[0].size();

        int maxArea = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                int area = maximalRectangleHelper(matrix, i, j);
                if (area > maxArea)
                    maxArea = area;
            }

        return maxArea;
    }
};

// 从上面我们看到 在求以(i, j)为左上角的最大矩形面积时 O（n）的时间用在查找(i, j)在每行的最短宽度
// 用dp[i][j]表示 （i, j）以(i, j)为起始节点，单行连续最大长度，这样之前的O（n）时间查找，现在可以用O(1)安成
// 采用dp的思想， 时间复杂度O（n^3）
// 92ms(性能提升了很多)
class Solution2
{
public:
    int maximalRectangle(vector<vector<char> > &matrix)
    {
        int m, n;

        m = matrix.size();
        if (!m)
            return 0;
        n = matrix[0].size();

        vector<vector<int> > dp;
        for (int i = 0; i < m; i++)
        {
            dp.push_back(vector<int> (n, 0));
            if (matrix[i][n - 1] == '1')
                dp[i][n - 1] = 1;
            for (int j = n - 2; j >= 0; j--)
                if (matrix[i][j] == '1')
                    dp[i][j] = dp[i][j + 1] + 1;
        }

        int maxArea = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                int k, minWidth = dp[i][j];
                for (k = i; k < m && dp[k][j]; k++)
                {
                    if (minWidth > dp[k][j])
                        minWidth = dp[k][j];

                    int area = (k - i + 1) * minWidth;
                    if (area > maxArea)
                        maxArea = area;
                }
            }

        return maxArea;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<vector<char> > matrix;
    vector<char> tmp(4, '0');
    tmp[2] = '1';
    matrix.push_back(tmp);
    tmp[2] = '0';
    tmp[3] = '1';
    matrix.push_back(tmp);
    tmp[1] = '1';
    tmp[2] = '1';
    tmp[3] = '1';
    matrix.push_back(tmp);
    tmp[1] = '0';
    tmp[2] = '1';
    tmp[3] = '1';
    matrix.push_back(tmp);

    cout << s1.maximalRectangle(matrix) << endl;
    cout << s2.maximalRectangle(matrix) << endl;

    return 0;
}
