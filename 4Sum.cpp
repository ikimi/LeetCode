#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 暴力法
// 首先对数组进行排序O(nlogn)
// 四层for循环 跳过重复的元素 时间复杂度O(n^4)
// 时间复杂度O(4^4) 空间复杂度O(1)
// TLE 果断超时了...
class Solution1
{
private:
    vector<vector<int> > res;
public:
    vector<vector<int> > fourSum(vector<int> &num, int target)
    {
        int i, j, k, l, n, temp;
        vector<int> tmp;

        sort(num.begin(), num.end());

        n = num.size();
        for (i = 0; i < n;)
        {
            for (j = i + 1; j < n;)
            {
                for (k = j + 1; k < n;)
                {
                    for (l = k + 1; l < n;)
                    {
                        if (num[i] + num[j] + num[k] + num[l] > target)
                            break;
                        if (num[i] + num[j] + num[k] + num[l] == target)
                        {
                            tmp.clear();
                            tmp.push_back(num[i]);
                            tmp.push_back(num[j]);
                            tmp.push_back(num[k]);
                            tmp.push_back(num[l]);
                            res.push_back(tmp);
                        }
                        temp = num[l];
                        while (l < n && num[l] == temp)
                            l++;
                    }
                    temp = num[k];
                    while (k < n && num[k] == temp)
                        k++;
                }
                temp = num[j];
                while (j < n && num[j] == temp)
                    j++;
            }
            temp = num[i];
            while (i < n && num[i] == temp)
                i++;
        }

        return res;
    }
};

// 支持一遍二分查找
// 首先排序 O(nlogn)
// 三层for循环遍历 并利用二分查找 查找第四个元素是否存在
// 时间复杂度O(n^3*logn) 空间复杂度O(1)
// TLE (又超时了...)
class Solution2
{
private:
    vector<vector<int> > res;
    bool binarySearch(vector<int> &num, int low, int high, int target)
    {
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (num[mid] == target)
                return true;
            else if (num[mid] > target)
                high = mid - 1;
            else
                low = mid + 1;
        }

        return false;
    }

public:
    vector<vector<int> > fourSum(vector<int> &num, int target)
    {
        int i, j, k, n, temp;
        vector<int> tmp;

        sort(num.begin(), num.end());
        n = num.size();

        for (i = 0; i < n;)
        {
            for (j = i + 1; j < n;)
            {
                for (k = j + 1; k < n;)
                {
                    if (binarySearch(num, k + 1, n - 1, target - num[i] - num[j] - num[k]))
                    {
                        tmp.clear();
                        tmp.push_back(num[i]);
                        tmp.push_back(num[j]);
                        tmp.push_back(num[k]);
                        tmp.push_back(target - num[i] - num[j] - num[k]);
                        res.push_back(tmp);
                    }
                    temp = num[k];
                    while (k < n && temp == num[k])
                        k++;
                }
                temp = num[j];
                while (j < n && temp == num[j])
                    j++;
            }
            temp = num[i];
            while (i < n && temp == num[i])
                i++;
        }

        return res;
    }
};

// 外层两遍循环确定两个数 k1 k2
// 内层使用类似2Sum的方法 在O(n)的时间复杂度的情况下找出是否有k3 k4
// 时间复杂度O(n^3) 空间复杂度O(1)
// Accepted!
// 504ms
class Solution3
{
private:
    vector<vector<int> > res;
public:
    vector<vector<int> > fourSum(vector<int> &num, int target)
    {
        int i, j, n, temp, low, high;
        vector<int> tmp;

        sort(num.begin(), num.end());
        n = num.size();
        for (i = 0; i < n;)
        {
            for (j = i + 1; j < n;)
            {
                low = j + 1, high = n - 1;
                while (low < high)
                {
                    if (target == num[i] + num[j] + num[low] + num[high])
                    {
                        tmp.clear();
                        tmp.push_back(num[i]);
                        tmp.push_back(num[j]);
                        tmp.push_back(num[low]);
                        tmp.push_back(num[high]);
                        res.push_back(tmp);
                        while (low < high && num[low] == num[low + 1])
                            low++;
                        if (low < high)
                            low++;
                        while (low < high && num[high] == num[high - 1])
                            high--;
                        if (low < high)
                            high--;
                    }
                    else if (target > num[i] + num[j] + num[low] + num[high])
                        low++;
                    else
                        high--;
                }

                temp = num[j];
                while (j < n && temp == num[j])
                    j++;
            }
            temp = num[i];
            while (i < n && temp == num[i])
                i++;
        }

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    vector<int> num;
    vector<vector<int> > res;

/*
    num.push_back(3);num.push_back(0);
    num.push_back(3);num.push_back(1);num.push_back(1);
    num.push_back(2);num.push_back(4);
    num.push_back(1);num.push_back(3);num.push_back(0);num.push_back(3);
    num.push_back(2);
*/
    //res = s1.fourSum(num, 6);
    //res = s2.fourSum(num, 6);
    //res = s3.fourSum(num, 6);

    num.push_back(1);num.push_back(0);
    num.push_back(-1);num.push_back(0);
    num.push_back(-2);num.push_back(2);


   // res = s1.fourSum(num, 0);
  //  res = s2.fourSum(num, 0);
    res = s3.fourSum(num, 0);

    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            cout << res[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
