#include <iostream>
#include <vector>

using namespace std;

// 纯水题 水题刷多了 这种题应该秒杀 扯远了。。:)
// 利用递归 思路很清晰 每次循环遍历出最外层的结果 并且不断向内层逼近
// 个然感觉比其他的解法更通俗易懂
class Solution1
{
private:
    void generate(vector<vector<int> > &data, int init, int pos, int n)
    {
        int i;

        if (!n)
            return ;
        if (n == 1)
        {
            data[pos][pos] = init;
            return ;
        }
        for (i = 0; i < n; i++)
        {
            data[pos][pos + i] = init++;
        }
        for (i = 1; i < n; i++)
        {
            data[pos + i][pos + n - 1] = init++;
        }
        for (i = n - 2; i >= 0; i--)
        {
            data[pos + n - 1][pos + i] = init++;
        }
        for (i = n - 2; i > 0; i--)
        {
            data[pos + i][pos] = init++;
        }
        generate(data, init, pos + 1, n - 2);
    }

public:
    vector<vector<int> > generateMatrix(int n)
    {
        vector<vector<int> > res;
        int i;

        for (i = 0; i < n; i++)
            res.push_back(vector<int> (n, 0));
        generate(res, 1, 0, n);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    vector<vector<int> > data;

    data = s1.generateMatrix(4);

    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data.size(); j++)
            cout << data[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
