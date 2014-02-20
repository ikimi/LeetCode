#include <iostream>

using namespace std;

// DP 时间复杂度为 O(n) 空间复杂度为 O(1)
class Solution1
{
    public:
        int maxSubArray(int A[], int n)
        {
            int i, max, cur;

            max = cur = A[0];
            for (i = 1; i < n; i++)
            {
                if (cur < 0)
                    cur = A[i];
                else
                    cur += A[i];
                if (cur > max)
                    max = cur;
            }
            if (max < 0)
            {
                max = A[0];
                for (i = 1; i < n; i++)
                    if (A[i] > max)
                        max = A[i];
            }

            return max;
        }
};

// 暴力法 时间复杂度为 O(n^2) LeetCode 运行 Time Limit Exceeded
class Solution2
{
    public:
        int maxSubArray(int A[], int n)
        {
            int i, j, cur, max = A[0];

            for (i = 0; i < n; i++)
            {
                for (j = i, cur = 0; j < n; j++)
                {
                    cur += A[j];
                    if (cur > max)
                        max = cur;
                }
            }

            return max;
        }
};

// 二分法：将数组分成左右两部分，递归求两部分最大连续子数组，由于最大连续子数组可能横跨左右，故需对这种情况进行处理
//假设数组A[left, right]存在最大值区间[i, j](i>=left & j<=right)，以mid = (left + right)/2 分界，无非以下三种情况：

//subarray A[i,..j] is
//(1) Entirely in A[low,mid-1]
//(2) Entirely in A[mid+1,high]
//(3) Across mid
//对于(1) and (2)，直接递归求解即可，对于(3)，则需要以mid为中心，向左及向右扫描求最大值，意味着在A[left, Mid]区间中找出A[i..mid], 而在A[mid+1, right]中找出A[mid+1..j]，两者加和即为(3)的解。
//比较三种情况下得到的子数组和，取其中最大值
class Solution3
{
    private:
        int maxSubSubArray(int A[], int low, int high)
        {
            if (low >= high)
                return A[low];

            int mid, max_left, max_right, max;

            mid = (low + high) / 2;
            max_left = maxSubSubArray(A, low, mid - 1);
            max_right = maxSubSubArray(A, mid + 1, high);

            int i, lmax, rmax, sum;

            sum = lmax = rmax = 0;
            for(i = mid - 1; i >= low; i--)
            {
                sum += A[i];
                if(sum > lmax)
                    lmax = sum;
            }
            for(i = mid + 1, sum = 0; i <= high; i++)
            {
                sum += A[i];
                if (sum > rmax)
                    rmax = sum;
            }

            max = (max_left > max_right) ? max_left : max_right;
            return (max > (A[mid] + lmax + rmax)) ? max : (A[mid] + lmax + rmax);
        }

    public:
        int maxSubArray(int A[], int n)
        {
            return maxSubSubArray(A, 0, n - 1);
        }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    int a[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int b[] = {3, -1, 2, -2, 2};
    cout << s1.maxSubArray(a, 9) << endl;
    cout << s2.maxSubArray(a, 9) << endl;
    cout << s3.maxSubArray(a, 9) << endl;
    cout << s3.maxSubArray(b, 5) << endl;

    return 0;
}
