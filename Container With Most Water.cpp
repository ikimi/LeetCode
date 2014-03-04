#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// 最直接的方法 遍历所有可能
// 时间复杂度O(n^2) 空间复杂度O(1)
// Time Limit Exceeded
class Solution1
{
private:
    int min(int x, int y)
    {
        return (x > y) ? y : x;
    }

    int area(vector<int> &height, int x1, int x2)
    {
        return min(height[x1], height[x2]) * (x2 - x1);
    }

public:
    int maxArea(vector<int> &height)
    {
        int i, j, len, max;

        for (i = max = 0, len = height.size(); i < len - 1; i++)
            for (j = i + 1; j < len; j++)
                if (max < area(height, i, j))
                    max = area(height, i, j);

        return max;
    }
};

// 相对暴力法进行剪枝
// 时间复杂度O(n^2) 虽然剪枝了 但仍然超时
// 网上相应的暴力搜没超时。。(可能是当时的example的大小不够大)
class Solution2
{
private:
    int area(vector<int> &height, int j, int i)
    {
        int h;

        h =  (height[i] > height[j]) ? height[j] : height[i];
        return h * (i - j);
    }

public:
    int maxArea(vector<int> &height)
    {
        int i, j, n, max, temp;
        double maxPosition;

        n = height.size(), max = 0;
        for (i = 1; i < n; i++)
        {
            if (!height[i])
                continue;
            maxPosition = i - max / height[i];
            for (j = 0; j < i && j <= maxPosition; j++)
                if ((temp = area(height, j, i)) > max)
                    max = temp;
        }

        return max;
    }
};

// 设两个指针指向height的开头和结尾
// 时间复杂度O (n)
class Solution3
{
public:
    int maxArea(vector<int> &height)
    {
        int i, j, max, area;

        i = 0, j = height.size() - 1, max = 0;
        while (i < j)
        {
            if (height[i] < height[j])
            {
                area = height[i] * (j - i);
                i++;
            }
            else
            {
                area = height[j] * (j - i);
                j--;
            }
            if (area > max)
                max = area;
        }

    return max;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    vector<int> height;
    height.push_back(2);
    height.push_back(5);
    height.push_back(8);
    height.push_back(2);
    height.push_back(32);
    height.push_back(1);

    cout << s1.maxArea(height) << endl;
    cout << s2.maxArea(height) << endl;
    cout << s3.maxArea(height) << endl;

    return 0;
}
