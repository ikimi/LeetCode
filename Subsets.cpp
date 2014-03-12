#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 算法思路很清晰 先对数组S进行排序 这里选择归并排序 (没有排序WA了一次) 其实可以调用STL中的排序算法。。。
// 然后分别求S的0, 1, 2 ... n的组合数
// 每次将结果存到res二维数组中
class Solution1
{
private:
    void mergeSort(vector<int> &S, int start, int end)
    {
        if (start >= end)
            return ;

        int mid = (start + end) / 2;

        mergeSort(S, start, mid);
        mergeSort(S, mid + 1, end);
        merge(S, start, mid, end);
    }

    void merge(vector<int> &S, int start, int mid, int end)
    {
        int i, j, k;
        vector<int> temp1, temp2;

        for (i = start; i <= mid; i++)
            temp1.push_back(S[i]);
        for (j = mid + 1; j <= end; j++)
            temp2.push_back(S[j]);

        i = j = 0, k = start;
        while ((i < temp1.size()) && (j < temp2.size()))
        {
            if (temp1[i] <= temp2[j])
                S[k++] = temp1[i++];
            else
                S[k++] = temp2[j++];
        }
        while (i < temp1.size())
            S[k++] = temp1[i++];
        while (j < temp2.size())
            S[k++] = temp2[j++];
    }

    void subset(vector<int> &S, vector<vector<int> > &res, vector<int> &data, int start, int end, int k)
    {
        if (end - start < k - 1)
            return ;
        if (!k)
        {
            res.push_back(data);
            return ;
        }

        data.push_back(S[start - 1]);
        subset(S, res, data, start + 1, end, k - 1);
        data.pop_back();
        subset(S, res, data, start + 1, end, k);
    }

public:
    vector<vector<int> > subsets(vector<int> &S)
    {
        vector<vector<int> > res;
        vector<int> data;
        int n = S.size();

        mergeSort(S, 0, n - 1);
        for (int i = 0; i <= n; i++)
        {
            data.clear();
            subset(S, res, data, 1, n, i);
        }

        return res;
    }
};

// 递归 但是不用一次递归求C(n,0), C(n,1) ... C(n,n)
// 而是针对每一个元素判断其是否要被插入到最后结果中
class Solution2
{
private:
    void subset(vector<vector<int> > &res, vector<int> &S, vector<int> &data, int depth)
    {
        if (depth >= S.size())
        {
            res.push_back(data);
            return ;
        }
        data.push_back(S[depth]);
        subset(res, S, data, depth + 1);
        data.pop_back();
        subset(res, S, data, depth + 1);
    }

public:
    vector<vector<int> > subsets(vector<int> &S)
    {
        vector<vector<int> > res;
        vector<int> data;

        sort(S.begin(), S.end());
        subset(res, S, data, 0);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<vector<int> > res;
    vector<int> S;
    S.push_back(4), S.push_back(1), S.push_back(0);
   // res = s1.subsets(S);
    res = s2.subsets(S);

    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            cout << res[i][j] << ' ';
        cout << endl;
    }

    return 0;
}

