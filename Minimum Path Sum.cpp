#include <iostream>
#include <vector>

using namespace std;

// DP 时间复杂度O(m*n) 空间复杂度O(m*n)
class Solution1
{
private:
    int Min(int x, int y)
    {
        return (x < y) ? x : y;
    }

public:
    int minPathSum(vector<vector<int> > &grid)
    {
        int i, j, m, n;
        vector<vector<int> > res;

        n = grid[0].size();
        m = grid.size();
        for (i = 0; i < m; i++)
            res.push_back(vector<int> ());

        res[0].push_back(grid[0][0]);
        for (i = 1; i < n; i++)
            res[0].push_back(grid[0][i] + res[0][i - 1]);
        for (i = 1; i < m; i++)
            res[i].push_back(res[i - 1][0] + grid[i][0]);

        for (i = 1; i < m; i++)
            for (j = 1; j < n; j++)
                res[i].push_back(Min(res[i - 1][j], res[i][j - 1]) + grid[i][j]);

        return res[m - 1][n - 1];
    }
};

// DP 降低空间复杂度 时间复杂度O(m*n) 空间复杂度O(n)
class Solution2
{
private:
    int Min(int x, int y)
    {
        return (x > y) ? y : x;
    }

public:
    int minPathSum(vector<vector<int> > &grid)
    {
        int i, j, m, n;
        vector<int> data;

        m = grid.size();
        n = grid[0].size();

        data.push_back(grid[0][0]);
        for (i = 1; i < n; i++)
            data.push_back(grid[0][i] + data[i - 1]);
        for (i = 1; i < m; i++)
        {
            data[0] += grid[i][0];
            for (j = 1; j < n; j++)
                data[j] = Min(data[j - 1], data[j]) + grid[i][j];
        }

        return data[n - 1];
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<vector<int> > data;
    vector<int> line1(5, 1);
    vector<int> line2(5, 2);
    vector<int> line3(5, 3);
    data.push_back(line1);
    data.push_back(line2);
    data.push_back(line3);

    cout << s1.minPathSum(data) << endl;
    cout << s2.minPathSum(data) << endl;

    return 0;
}
