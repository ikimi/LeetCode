#include <iostream>
#include <cstring>

using namespace std;

// 以插入排序为例 实现复杂度为O(n^2)的排序算法
class Solution1
{
public:
    void sortColors(int A[], int n)
    {
        int i, j, value;

        for (i = 0; i < n - 1; i++)
        {
            value = A[i + 1], j = i;
            while (j >= 0 && A[j] > value)
            {
                A[j + 1] = A[j];
                j--;
            }
            A[j + 1] = value;
        }
    }
};

// 以归并排序为例 实现时间复杂度为O(nlogn) 空间复杂度为O(n)的算法
class Solution2
{
private:
    void merge(int A[], int start, int mid, int end)
    {
        int i, j, k, B[100], C[100];

        for (i = start, k = 0; i <= mid; i++, k++)
            B[k] = A[start + k];
        for (i = mid + 1, k = 0; i <= end; i++, k++)
            C[k] = A[mid + k + 1];

        i = j = k = 0;
        while (i + start <= mid && j + mid + 1 <= end)
        {
            if (B[i] < C[j])
                A[start + k] = B[i++];
            else
                A[start + k] = C[j++];
            k++;
        }
        while (i + start <= mid)
        {
            A[start + k] = B[i++];
            k++;
        }
        while (j + mid + 1 <= end)
        {
            A[start + k] = C[j++];
            k++;
        }
    }

    void mergeSort(int A[], int start, int end)
    {
        if (start >= end)
            return ;

        int mid = (start + end) / 2;

        mergeSort(A, start, mid);
        mergeSort(A, mid + 1, end);
        merge(A, start, mid, end);
    }

public:
    void sortColors(int A[], int n)
    {
        mergeSort(A, 0, n - 1);
    }
};

// 计数排序（两遍遍历）时间复杂度为O(n) k空间复杂度为O(n)
class Solution3
{
public:
        void sortColors(int A[], int n)
        {
            int num[3], i;

            memset(num, 0, sizeof(num));
            for (i = 0; i < n; i++)
                num[A[i]]++;

            i = 0;
            while (num[0]--)
                A[i++] = 0;
            while (num[1]--)
                A[i++] = 1;
            while (num[2]--)
                A[i++] = 2;
        }
};

// 快排的变形
class Solution4
{
public:
    void sortColors(int A[], int n)
    {
        int i, zero, one, two, temp;

        i = zero = one = two = 0;
        while (i < n)
        {
            if (A[i] == 0)
            {
                if (zero == i)
                {
                    i++, zero++, one++, two++;
                    continue;
                }
                temp = A[zero];
                A[zero] = A[i];
                A[i] = temp;
                zero++;
                if (one < zero) // 忘记这种情况 WA了一次
                    one = zero;
            }
            if (A[i] == 1)
            {
                if (one == i)
                {
                    i++, one++, two++;
                    continue;
                }
                temp = A[one];
                A[one] = A[i];
                A[i] = temp;
                one++;
                if (two < one)  // 同上
                    two = one;
            }
            if (A[i] == 2)
            {
                i++, two++;
            }
        }
    }
};

// 别人代码 其实也是quick sort的变形
// 设置两个zero, two分别指向0,和2应该插入的位置，cur只想数组现在遍历到的位置
class Solution5
{
public:
    void sortColors(int A[], int n)
    {
        int zero, one, two, temp;

        zero = one = 0;
        two = n - 1;

        while (one <= two)
        {
            if (A[one] == 0)
            {
                temp = A[zero];
                A[zero] = 0;
                A[one] = temp;
                zero++, one++;
            }
            else if (A[one] == 2)
            {
                temp = A[two];
                A[two] = 2;
                A[one] = temp;
                two--;
            }
            else
                one++;
        }
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
    int A[] = {1, 2, 1, 1, 0, 2, 0, 1, 0, 2, 1};

    //s1.sortColors(A, 11);
    //s2.sortColors(A, 11);
    //s3.sortColors(A, 11);
    //s4.sortColors(A, 11);
    s5.sortColors(A, 11);
    for (int i = 0; i < 11; i++)
        cout << A[i] << ' ';
    cout << endl;

    return 0;
}
