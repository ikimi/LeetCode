#include <iostream>
#include <vector>

using namespace std;

// 分治的思想
class Solution1
{
private:
    vector<vector<int> > res;
    void combinations(vector<int> &data, int start, int end, int k)
    {
        if (end - start + 1 < k)
            return ;
        if (!k)
        {
            res.push_back(data);
            return ;
        }

        data.push_back(start);
        combinations(data, start + 1, end, k - 1);
        data.pop_back();
        combinations(data, start + 1, end, k);
    }

public:
    vector<vector<int> > combine(int n, int k)
    {
        if (n < k)
            return res;

        vector<int> data;
        combinations(data, 1, n, k);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    vector<vector<int> > data;

    data = s1.combine(5, 2);
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
            cout << data[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
