#include <iostream>
#include <vector>

using namespace std;

// 暴力法 循环遍历 时间复杂度O(n^2) n为加油站个数
// 果不其然 LTE 超时了
class Solution1
{
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int i, j, n, res;

        n = gas.size();
        for (i = 0; i < n; i++)
        {
            j = res = 0;
            while (j < n)
            {
                res += gas[(i + j) % n];
                if (res < cost[(i + j) % n])
                    break;
                res -= cost[(i + j) % n];
                j++;
            }
            if (j == n)
                return i;
        }

        return -1;
    }
};

// 我们可以记录下目前车内的汽油数量 用left表示 初始化为0
// 每到一个station计算diff=gas[i]-cost[i]的值 若left+diff>=0表示汽车还可以继续向下一站移动 否则汽车停止移动 排除这时的起始位置
// 并从下面一个开始位置开始遍历 以上是O（n^2）的算法
// 其实假设 从i ... j left变为0 那么下一个开始节点只能从j+1开始 为什么呢？
// 反证法：若在i ... j中某一点m开始可以环绕station一圈 则 m ... j >= 0，但是i...j < 0，所以i...m的left < 0
// 此时 在汽车从i开始行进 还没有到达 j 就无法行进了 与前提在j无法行进相互矛盾 得证!
// 48ms
class Solution2
{
private:
    int helper(vector<int> &gas, vector<int> &cost, int i)
    {
        int start, n, left;

        n = gas.size();
        for (start = i, left = 0; start < i + n; start++)
        {
            left += gas[start % n] - cost[start % n];
            if (left < 0)
                return start - i;
        }

        return start - i;
    }

public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int i, j, n, left;

        n = gas.size();
        for (i = 0; i < n; i++)
        {
            j = helper(gas, cost, i);
            if (j == n)
                return i;
            i += j;
        }

        return -1;
    }
};

// NB闪闪的代码 想了一晚上
// 其实与上面的思路是一样的 也是跳跃的遍历 使得时间复杂度为O(n)
// 关键时理解total的用途,至于为什么 i 遍历到n就停止了 而不是像上面一样继续遍历 可以用反证法证明（注意total>=0的含义）
// 40ms
class Solution3
{
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int i, j, n, left, total;

        n = gas.size();
        left = total = 0;
        for (i = j = 0; i < n; i++) // z注意j初始化为0 因为从i = 0开始就可以遍历整个加油站时 j是不改变的 WA了一次
        {
            left += gas[i] - cost[i];
            total += gas[i] - cost[i];
            if (left < 0)
            {
               left = 0;
               j = i + 1;
            }
        }

        return (total >= 0) ? j : -1;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    vector<int> gas;
    vector<int> cost;

    gas.push_back(5);
    gas.push_back(2);
    gas.push_back(1);
    gas.push_back(4);

    cost.push_back(4);
    cost.push_back(3);
    cost.push_back(3);
    cost.push_back(1);
    cout << s1.canCompleteCircuit(gas, cost) << endl;
    cout << s2.canCompleteCircuit(gas, cost) << endl;
    cout << s3.canCompleteCircuit(gas, cost) << endl;

    return 0;
}
