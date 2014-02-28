#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// 递归
class Solution1
{
private:
    void perm(vector<vector<int> > &data, vector<int> &num, int start, int end)
    {
        if (start >= end)
        {
            data.push_back(num);
            return ;
        }

        int temp, i;

        for (i = start; i < end; i++)
        {
            temp = num[start], num[start] = num[i], num[i] = temp;
            perm(data, num, start + 1, end);
            temp = num[start], num[start] = num[i], num[i] = temp;
        }
    }

public:
    vector<vector<int> > permute(vector<int> &num)
    {
        vector<vector<int> > data;

        perm(data, num, 0, num.size());

        return data;
    }
};

// dfs 其实跟递归方法差不多 用两个数组visited & vector<int> temp 来记录此时遍历的深度以及访问标记
class Solution2
{
private:
    vector<vector<int> > data;
    bool visited[100];
    int temp[100];

    void dfs(vector<int> &num, int start, int end)
    {
        if (start >= end)
        {
            vector<int> one;
            one.clear();

            for (int i = 0; i < end; i++)
                one.push_back(temp[i]);
            data.push_back(one);

            return ;
        }
        for (int i = 0; i < end; i++)
        {
            if (!visited[i])
            {
                temp[start] = num[i];
                visited[i] = true;
                dfs(num, start + 1, end);
                visited[i] = false;
            }
        }
    }

public:
    vector<vector<int> > permute(vector<int> &num)
    {
        memset(visited, false, sizeof(visited));
        dfs(num, 0, num.size());

        return data;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<vector<int> > data;
    vector<int> num;
    num.push_back(1);
    num.push_back(2);
    num.push_back(3);

   // data = s1.permute(num);
    data = s2.permute(num);
    cout << data.size() << endl;
    for (int i = 0; i < data.size(); i++)
    {
        for(int j = 0; j < data[i].size(); j++)
            cout << data[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
