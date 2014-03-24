#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 方法同N-Queues 的方法
// 148ms
class Solution1
{
private:
    void nQueens(vector<int> queens, int *count, int length, int depth)
    {
        for (int col = 0; col < length; col++)
        {
            if (check(queens, length, depth, col))
            {
                queens[depth] = col;
                if (depth >= length - 1)
                {
                    (*count)++;
                    queens[depth] = -1;
                    return ;
                }
                nQueens(queens, count, length, depth + 1);
                queens[depth] = -1;
            }
        }
    }

    bool check(vector<int> queens, int length, int depth, int col)
    {
        if (queens[depth] != -1)
            return false;

        for (int i = 0; i < length; i++)
        {
            if (queens[i] == col)
                return false;
            if (queens[i] != -1)
            {
                if (abs(i - depth) == abs(col - queens[i]))
                    return false;
            }
        }

        return true;
    }

public:
    int totalNQueens(int n)
    {
        int count = 0;
        vector<int> queens(n, -1);

        nQueens(queens, &count, n, 0);

        return count;
    }
};

// 位运算
// 地址[1]：http://www.matrix67.com/blog/archives/266
// 地址[2]：http://www.cnblogs.com/lichen782/p/leetcode_NQueenII.html
// 28ms (提高将近6倍)
class Solution2
{
private:
    int cnt, upper;
    void nQueens(int row, int ld, int rd)
    {
        if (upper != row)
        {
            int pos, p;
            pos = upper & (~(row | ld | rd));

            while (pos)
            {
                p = pos & (-pos);
                pos = pos - p;
                nQueens(row + p, (ld + p) << 1, (rd + p) >> 1);
            }
        }
        else
            cnt++;
    }

public:
    int totalNQueens(int n)
    {
        cnt = 0;
        upper = (1 << n) - 1;
        nQueens(0, 0, 0);

        return cnt;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    cout << s1.totalNQueens(7) << endl;
    cout << s2.totalNQueens(7) << endl;

    return 0;
}
