#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

// 暴力法
// 在A中查找1～n之间的正整数
// 时间复杂度O(n^2)
// 8ms
class Solution1
{
public:
    int firstMissingPositive(int A[], int n)
    {
        int i, j;
        for (i = 1; i <= n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (A[j] == i)
                    break;
            }
            if (j == n)
                return i;
        }

        return n + 1;
    }
};

// 基于排序
// 首先排序 然后线性查找第一个被错过的正整数
// 时间复杂度为O(nlogn)
// 32ms (竟然比Solution1执行时间长。。)
class Solution2
{
public:
    int firstMissingPositive(int A[], int n)
    {
        int i, res;
        sort(A, A + n);

        i = 0, res = 1;
        while (i < n)
        {
            if (A[i] < res)
                i++;
            else if (A[i] == res)
            {
                i++;
                res++;
            }
            else
                return res;
        }

        return res;
    }
};

// 类似于计数排序
// 利用O(n)的数组存储1~n之间的整数是否出现过 遍历一遍后，数组每一个元素都别左上标记
// 遍历标记数组 输出最小Missing整数
// 时间复杂度为O(n) 空间复杂度为O(n)
// 8ms
class Solution3
{
public:
    int firstMissingPositive(int A[], int n)
    {
        vector<bool> status(n, false);
        for (int i = 0; i < n; i++)
        {
            if (A[i] >= 1 && A[i] <= n)
                status[A[i] - 1] = true;
        }

        for (int i = 0; i < n; i++)
            if (!status[i])
                return i + 1;

        return n + 1;
    }
};

// 思路与Solution3的一样 都是HASH的细想
// 但是这里我们不用额外的数组来存储状态 而是通过原数组来存储
// 第一遍遍历 将所有的负数 变为一个正数(n+2)
// 第二遍遍历 记录状态
// 第三遍遍历 输出结构
// 时间复杂度为O(n) 空间复杂度为O(1)
// 32ms
class Solution4
{
public:
    int firstMissingPositive(int A[], int n)
    {
        for (int i = 0; i < n; i++)
            if (A[i] <= 0)
                A[i] = n + 2;

        for (int i = 0; i < n; i++)
        {
            if (abs(A[i]) >= 1 && abs(A[i]) <= n)
                if (A[abs(A[i]) - 1] > 0)
                    A[abs(A[i]) - 1] = -A[abs(A[i]) - 1];
        }

        for (int i = 0; i < n; i++)
            if (A[i] > 0)
                return i + 1;

        return n + 1;
    }
};

// 基于交换的思路
// 时间复杂度O(n) 空间复杂度O(1)
// 8ms
class Solution5
{
private:
    void swap(int A[], int x, int y)
    {
        int temp = A[x];
        A[x] = A[y];
        A[y] = temp;
    }

public:
    int firstMissingPositive(int A[], int n)
    {
        for (int i = 0; i < n; i++)
        {
            while ((A[i] >= 1 && A[i] <= n) && (A[i] - 1 != i) && (A[A[i] - 1] != A[i]))
                swap(A, i, A[i] - 1);
        }
        for (int i = 0; i < n; i++)
            if (A[i] != i + 1)
                return i + 1;

        return n + 1;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;
    Solution4 s4;
    Solution5 s5;

    int A[] = {1, 2, 0};
    int B[] = {3, 4, -1, 1};

    cout << "-------Method One------------" << endl;
    cout << s1.firstMissingPositive(A, 3) << endl;
    cout << s1.firstMissingPositive(B, 4) << endl;
    cout << "-------Method Two------------" << endl;
    cout << s2.firstMissingPositive(A, 3) << endl;
    cout << s2.firstMissingPositive(B, 4) << endl;
    cout << "-------Method Three----------" << endl;
    cout << s3.firstMissingPositive(A, 3) << endl;
    cout << s3.firstMissingPositive(B, 4) << endl;
    cout << "-------Method Four-----------" << endl;
  //  cout << s4.firstMissingPositive(A, 3) << endl;
    cout << s4.firstMissingPositive(B, 4) << endl;
    cout << "-------Method Five-----------" << endl;
    cout << s5.firstMissingPositive(A, 3) << endl;
    cout << s5.firstMissingPositive(B, 4) << endl;

    return 0;
}
