#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// 暴力法
// 遍历任意height[i]和height[j]之间的最小高度，并求出其值
// 时间复杂度O(n^2) 空间复杂度为O(1)
// TLE 例子{0,1,2,3...8892} 计算结果19771362
class Solution1
{
public:
    int largestRectangleArea(vector<int> &height)
    {
        int largestArea, minHeight;

        largestArea = 0;
        for (int i = 0; i < height.size(); i++)
        {
            minHeight = height[i];
            for (int j = i; j < height.size(); j++)
            {
                if ((height.size() - i) * minHeight < largestArea)  // 进行剪枝，当将j后的所有节点都加入到矩形之中，并且选取高度为i~j之间的最小高度
                    break;                                          // 若此时面积还是小于最大值，则j后面的节点不用遍历了
                if (height[j] < minHeight)
                    minHeight = height[j];
                int area = (j - i + 1) * minHeight;
                if (area > largestArea)
                    largestArea = area;
            }
        }

        return largestArea;
    }
};

// 参考：http://www.cnblogs.com/lichen782/p/leetcode_Largest_Rectangle_in_Histogram.html
// （1） 假设R（i, j）是最大的连续矩形，其中i是其最左边界，j是其最右边界
// 我们可以知道，i位置的矩形高度一定高于i-1(如果存在)位置的矩形高度，而j位置的矩形高度一定高于j+1(如果存在)位置的矩形高度
// 因为，如果i位置高度不高于i-1，那么R（i-1，j）>R(i,j),同理R（i, j+1）>R(i, j)这与我们假设R（i,j）时最大的矛盾
// (2) 我们接下来的目标就是找到所有满足 j位置高度 > j+1位置高度的坐标j!然后针对每一个j，找到所有可能的i，记录R（i,j）返回最大的R（i,j）即可
// (3) 寻找每一个可能的j时容易的，我们只需要遍历一遍height，每当j>j+1时，就记录j即可
// (4) 那么对于任何一个j寻找所有可能的i呢? 我们可以使用参考链接中的做法，使用一个递增栈来保存一个递增高度
// (5) 每加入一个i,都要判断其height[i] 与 top = stack.top(),height[top]的大小
// 若height[i] >= height[top] 则继续压栈，因为此时j还没有找到
// 若height[i] < height[top] 则开始弹栈，此时top是一个j
// 每一次弹栈都要计算此时的矩形面积，并更新maxArea
// 弹栈的终止条件是：1）栈为空2）height[top] < height[i]
// 条件1很好理解，关键是条件2
// 可以这样想，如果当到达条件2时继续弹栈，计算矩形面积，那么其结果R(top, i-1)肯定会包含在R（top, i）中
// 而后者我们在后面会计算
// 时间复杂度O(n),空间复杂度O(n)
// 100ms
class Solution2
{
public:
    int largestRectangleArea(vector<int> &height)
    {
        height.push_back(0);
        int len, maxArea;
        stack<int> pos;

        len = height.size(), maxArea = 0;
        for (int i = 0; i < len;)
        {
            if (pos.empty() || (height[pos.top()] <= height[i]))
                pos.push(i++);
            else
            {
                int top = pos.top();
                pos.pop();

                int area = height[top] * (pos.empty() ? i : i - pos.top() - 1);
                if (area > maxArea)
                    maxArea = area;
            }
        }
        height.pop_back();

        return maxArea;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<int> height;
    for (int i = 0; i < 8893; i++)
          height.push_back(i);
   // height.push_back(0);height.push_back(1);height.push_back(5);
   // height.push_back(6);height.push_back(2);height.push_back(3);

    cout << s1.largestRectangleArea(height) << endl;
    cout << s2.largestRectangleArea(height) << endl;

    return 0;
}
