#include <iostream>
#include <vector>

using namespace std;

// 暴力搜 时间复杂度O(m*n)
// 没想到过了。。:)
class Solution1
{
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target)
    {
        int m, n, i, j;

        if (!matrix.size())
            return false;

        m = matrix.size(), n = matrix[0].size();
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            if (matrix[i][j] == target)
                return true;
        }

        return false;
    }
};

// 二分搜索，首先对每行最后一个元素进行搜索 确定target的范围
// 若为上半区 则检测 target 是否大于mid的行首值 若大于 则在此行搜索 若小于则在上半区搜索
// 若在下半区则直接在下半区搜索即可
class Solution2
{
private:
    bool searchInRow(vector<int> row, int target)
    {
        int low, mid, high;

        low = 0, high = row.size() - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (row[mid] == target)
                return true;
            else if (row[mid] < target)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return false;
    }
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target)
    {
        if (!matrix.size())
            return false;

        int m, n, low, mid, high;
        m = matrix.size(), n = matrix[0].size();
        low = 0, high = m - 1;

        while (low < high)
        {
            mid = (low + high) / 2;
            if (matrix[mid][n - 1] == target)
                return true;
            else if (matrix[mid][n - 1] > target)
            {
                if (matrix[mid][0] <= target)
                    return searchInRow(matrix[mid], target);
                else
                    high = mid - 1;
            }
            else
                low = mid + 1;
        }

        return searchInRow(matrix[low], target);
    }
};

// 将整个二维数组看成是一维数组 寻找中值位置，做位置转换 将其变成二维的坐标
// 时间复杂度O(log(m*n))
// 代码非常简洁
class Solution3
{
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target)
    {
        if (!matrix.size())
            return false;

        int m, n, low, mid, high;
        m = matrix.size(), n = matrix[0].size();
        low = 0, high = m * n - 1;

        while (low <= high)
        {
            mid = (low + high) / 2;
            if (matrix[mid / n][mid % n] == target)
                return true;
            else if (matrix[mid / n][mid % n] < target)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return false;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    vector<vector<int> > data;
    vector<int> row;
    row.push_back(1), row.push_back(3), row.push_back(5), row.push_back(7), data.push_back(row), row.clear();
    row.push_back(10), row.push_back(11), row.push_back(16), row.push_back(20), data.push_back(row), row.clear();
    row.push_back(23), row.push_back(30), row.push_back(34), row.push_back(50), data.push_back(row);

    cout << s1.searchMatrix(data, 17) << endl;
    cout << s2.searchMatrix(data, 89) << endl;
    cout << s2.searchMatrix(data, 2) << endl;

    return 0;
}
