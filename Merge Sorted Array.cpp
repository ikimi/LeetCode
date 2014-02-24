#include <iostream>

using namespace std;

// 从两个数组的开头开始添加最小的元素
// 时间复杂度O(m+n) 空间复杂度O(m+n)
class Solution1
{
public:
    void merge(int A[], int m, int B[], int n)
    {
        int i, j, k, C[m + n];
        i = j = k = 0;

        while (i < m && j < n)
        {
            if (A[i] <= B[j])
                C[k++] = A[i++];
            else
                C[k++] = B[j++];
        }
        if (i == m)
        {
            while (j < n)
                C[k++] = B[j++];
        }
        else
        {
            while (i < m)
                C[k++] = A[i++];
        }
        for (k = 0; k < m + n; k++)
            A[k] = C[k];
    }
};

// 分别从A 和 B的最后一位（即最大值）填充A的末端
// 时间复杂度O(n + m) 空间复杂度 O(1)
class Solution2
{
public:
    void merge(int A[], int m, int B[], int n)
    {
        int len, i, j;
        len = m + n - 1, i = m - 1, j = n - 1;

        while (i >= 0 && j >= 0)
        {
            if (A[i] >= B[j])
                A[len--] = A[i--];
            else
                A[len--] = B[j--];
        }
        if (i < 0)
            while (j >= 0)
                A[len--] = B[j--];
    }
};

// 可以先将B复制到A的末端，然后采用快排
// 时间复杂度O((m+n)log(m+n)) 空间复杂度O(1)

int main()
{
    // test example
   // Solution1 s1;
    Solution2 s2;
    int i, A[7] = {1, 4, 5}, B[] = {2, 4, 8, 9};

    //s1.merge(A, 3, B, 4);
    s2.merge(A, 3, B, 4);
    for (i = 0; i < 7; i++)
        cout << A[i] << endl;

    return 0;
}
