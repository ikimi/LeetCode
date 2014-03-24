#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

// 基于数组全排列的方法
// 每次求出数组的一个全排列 检查此时是否满足N-Queues条件
// 若满足则输出结果
// 关键是求解 n 个数字的全排列
// 首先，n-queens问题要求每行不能同时存在两个Q，所以我们可以设一个 n大小的一维数组用来代表每行的Q所对应的列
// 因为每列也不能同时存在里两个Q，所以我们可以设定数组的每个数字不同
// 以上求解出n排列，剩下的部分就是判断斜着的Q不能冲突.设 两个Q的坐标时(i, j) (m, n) 若两坐标的横坐标差 == 纵坐标差 则冲突
// 若每两个都不冲突 则返回结果
// 最后生成string表示的棋盘就可以了
// 232ms (时间复杂度略大)
class Solution1
{
private:
    void nQueens(vector<vector<string> > &res, vector<int> &queens, int length, int index)
    {
        if (length == index)
        {
            if (check(queens, length))
            {
                generate(res, queens, length);
                return ;
            }
        }

        for (int i = index; i < length; i++)
        {
            int temp = queens[index];
            queens[index] = queens[i];
            queens[i] = temp;

            nQueens(res, queens, length, index + 1);

            temp = queens[index];
            queens[index] = queens[i];
            queens[i] = temp;
        }
    }

    bool check(vector<int> &queens, int length)
    {
        for (int i = 0; i < length; i++)
            for (int j = i + 1; j < length; j++)
            {
                if (abs(i - j) == abs(queens[i] - queens[j]))
                    return false;
            }

        return true;
    }

    void generate(vector<vector<string> > &res, vector<int> &queens, int length)
    {
        vector<string> temp(length, string(length, '.'));
        for (int i = 0; i < length; i++)
            temp[i][queens[i]] = 'Q';

        res.push_back(temp);
    }

public:
    vector<vector<string> > solveNQueens(int n)
    {
        vector<vector<string> > res;
        vector<int> queens;

        for (int i = 0; i < n; i++)
            queens.push_back(i);
        nQueens(res, queens, n, 0);

        return res;
    }
};
// 利用回溯法
// 参见：http://www.cppblog.com/aaxron/archive/2013/03/20/198631.html
// 52ms(性能提升6倍)
class Solution2
{
private:
    void nQueens(vector<vector<string> > &res, vector<int> queens, int length, int depth)
    {
        int i;

        for (i = 0; i < length; i++)
        {
            if (check(queens, length, depth, i))
            {
                queens[depth] = i;
                if (depth >= length - 1)
                {
                    generate(res, queens, length);
                    queens[depth] = -1;
                    return ;
                }
                nQueens(res, queens, length, depth + 1);
                queens[depth] = -1;
            }
        }
    }

    bool check(vector<int> &queens, int length, int depth, int col)
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

    void generate(vector<vector<string> > &res, vector<int> queens, int length)
    {
        vector<string> temp(length, string(length, '.'));
        for (int i = 0; i < length; i++)
            temp[i][queens[i]] = 'Q';

        res.push_back(temp);
    }

public:
    vector<vector<string> > solveNQueens(int n)
    {
        vector<vector<string> > res;
        vector<int> queens (n, -1);

        nQueens(res, queens, n, 0);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<vector<string> > res;
   // res = s1.solveNQueens(7);
    res = s2.solveNQueens(7);

    cout << res.size() << endl;
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
        {
            for (int k = 0; k < res[i].size(); k++)
                cout << res[i][j][k] << ' ';
            cout << endl;
        }
        cout << "------------------" << endl;
    }

    return 0;
}
