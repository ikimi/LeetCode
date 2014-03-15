#include <iostream>
#include <vector>

using namespace std;

// 二分查找 当找到target时 从target左右同时伸展
// 若没有找到 则进入左或者右区间进行查找
// 64ms
class Solution1
{
public:
    vector<int> searchRange(int A[], int n, int target)
    {
        int low, mid, high, i;
        vector<int> res;

        low = 0, high = n - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (A[mid] == target)
            {
                i = mid;
                while ((i >= low) && (A[i] == target))
                    i--;
                res.push_back(i+1);
                i = mid;
                while ((i <= high) && (A[i] == target))
                    i++;
                res.push_back(i-1);

                return res;
            }
            else if (A[mid] < target)
                low = mid + 1;
            else
                high = mid - 1;
        }
        res.push_back(-1), res.push_back(-1);

        return res;
    }
};

// 分三次二分查找
// 第一次查找 找到最中间的 target 位置， 此时再次利用二分查找分别查找左右区间
// 并注意边界条件
// 1次 AC～～
// 52ms(果然比上一个快一些)
class Solution2
{
public:
    vector<int> searchRange(int A[], int n, int target)
    {
        int low, mid, high, llow, lmid, lhigh, rlow, rmid, rhigh;
        vector<int> res(2, -1);

        low = 0, high = n - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (A[mid] == target)
            {
                break;
            }
            else if (A[mid] < target)
                low = mid + 1;
            else
                high = mid - 1;
        }
        if (low > high)
            return res;

        llow = low, lhigh = mid;
        while (llow <= lhigh)
        {
            lmid = (llow + lhigh) / 2;
            if (A[lmid] == target)
                lhigh = lmid - 1;
            else
                llow = lmid + 1;
        }
        res[0] = lhigh + 1;

        rlow = mid, rhigh = high;
        while (rlow <= rhigh)
        {
            rmid = (rlow + rhigh) / 2;
            if (A[rmid] == target)
                rlow = rmid + 1;
            else
                rhigh = rmid - 1;
        }
        res[1] = rlow - 1;

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<int> res;
    int A[] = {5, 7, 7, 8, 8, 10};

    //res = s1.searchRange(A, 6, 7);
    res = s2.searchRange(A, 6, 7);

    for (int i = 0; i < res.size(); i++)
        cout << res[i] << ' ';
    cout << endl;

    return 0;
}
