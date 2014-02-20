#include <iostream>

using namespace std;

// 顺序查找 时间复杂度w为 O(n)
class Solution1
{
    public:
        int searchInsert(int A[], int n, int target)
        {
            int i;

            if (n <= 0)
                return 0;

            for (i = 0; i < n;)
                if (A[i] >= target)
                    return i;
                else
                    i++;

            return n;
        }
};

// 二分查找 时间复杂度为O(logn)
class Solution2
{
    public:
        int searchInsert(int A[], int n, int target)
        {
            if (n <= 0)
                return 0;
            int low, high, mid;

            low = 0, high = n - 1;
            while(low <= high)
            {
                mid = (low + high) / 2;
                if (A[mid] == target)
                    return mid;
                else if (A[mid] > target)
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            if (low <= high)
            {
                if (A[low] > target)
                    return low - 1;
                return high + 1;
            }
        }
};

int main()
{
    Solution1 s1;
    Solution2 s2;
    int A[4] = {1, 3, 5, 6};

    cout << s1.searchInsert(A, 4, 5) << endl;
    cout << s1.searchInsert(A, 4, 2) << endl;
    cout << s1.searchInsert(A, 4, 7) << endl;
    cout << s1.searchInsert(A, 4, 0) << endl;

    cout << s2.searchInsert(A, 4, 5) << endl;
    cout << s2.searchInsert(A, 4, 2) << endl;
    cout << s2.searchInsert(A, 4, 7) << endl;
    cout << s2.searchInsert(A, 4, 0) << endl;

    return 0;
}





















