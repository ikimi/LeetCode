#include <iostream>
#include <vector>

using namespace std;

// 思路错了 WA的代码
class Solution1
{
private:
    int Min(int x, int y)
    {
        return (x > y) ? y : x;
    }

public:
    int trap(int A[], int n)
    {
        int i, j, temp, res, start, mid, end;

        res = i = 0;
        while (i < n - 1)
        {
            if (A[i] <= A[i + 1])
                i++;
            else
                break;
        }
        if (i == n - 1)
            return res;
        start = end = i;
        while (i < n - 1)
        {
            while ((i < n - 1) && (A[i] >= A[i + 1]))
                i++;
            if (i == n - 1)
                return res;
            mid = i;
            while ((i < n - 1) && (A[i] <= A[i + 1]))
                i++;
            end = i;
            for (j = mid; j >= start; j--)
                if (A[j] >= A[end])
                {
                    start = j;
                    break;
                }
            for (j = start + 1, temp = 0; j < end; j++)
                temp += A[j];
            res += (end - start - 1) * Min(A[start], A[end]) - temp;
            start = end;
        }

        return res;
    }
};

// 实际上每个方格上方所能存储的水的多少与该方格左右两边的最高高度有关
// 可以通过一次遍历求出每个方格左方的最高距离 一遍遍历求出每个方格右方的最高高度
class Solution2
{
private:
    int Min(int x, int y)
    {
        return (x > y) ? y : x;
    }

public:
    int trap(int A[], int n)
    {
        int i, max, res;
        vector<int> lmax;

        for (i = max = 0; i < n; i++)
        {
            if (A[i] > max)
                max = A[i];
            lmax.push_back(max);
        }
        for (i = n - 1, res = max = 0; i >= 0; i--)
        {
            if (A[i] > max)
                max = A[i];
            if (Min(lmax[i], max) > A[i])
                res += Min(lmax[i], max) - A[i];
        }

        return res;
    }
};

int main()
{
    // test example
    Solution2 s2;
    int A[] = {5, 4, 1, 2};

    cout << s2.trap(A, 4) << endl;

    return 0;
}

