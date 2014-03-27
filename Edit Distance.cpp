#include <iostream>
#include <cstring>
#include <limits.h>
#include <vector>

using namespace std;

// dfs(超时)
// 对于word1 和  word2的开头元素，有下面几种方式来从word1转换成word2
// 1)如果 word1 开头元素 和 word2 开头元素相同, 则同时从 word1 和 word2 , 开头元素的下一个元素开始遍历，跳过 2)
// 2)若 1)不满足，则变幻 word1 头元素的值使其与 word2 的头元素相, 从 word1 和 word2 的下一个元素开始遍历
// 3)在 word1 开头插入 word2 的头元素, 从 word1 ，以及 word2 开头的下一个元素开始遍历;
// 4)将 word1 的头元素删除, 从word1 头元素的下一个元素， 以及 word2 开头开始遍历;
// dfs 的方法会超时:e.g. word1 = "dinitrophenylhydrazine"， word2 = "acetylphenylhydrazine"
// 所以应该降低算法的时间复杂度 考虑用 DP
class Solution1
{
private:
    int min;
    void helper(string word1, int low1, int high1, string word2, int low2, int high2, int count)
    {
        if (low2 > high2)
        {
            if (low1 <= high1)
                count += high1 - low1 + 1;
            if (count < min)
                min = count;
            return ;
        }
        if (low1 > high1)
        {
            if (low2 <= high2)
                count += high2 - low2 + 1;
            if (count < min)
                min = count;
            return ;
        }
        if (word1[low1] == word2[low2])
            helper(word1, low1 + 1, high1, word2, low2 + 1, high2, count);
        else
            helper(word1, low1 + 1, high1, word2, low2 + 1, high2, count + 1);
        helper(word1, low1, high1, word2, low2 + 1, high2, count + 1);
        helper(word1, low1 + 1, high1, word2, low2, high2, count + 1);
    }

public:
    int minDistance(string word1, string word2)
    {
        min = INT_MAX;
        helper(word1, 0, word1.length() - 1, word2, 0, word2.length() - 1, 0);

        return min;
    }
};

// DP 参考链接：http://www.cnblogs.com/lihaozy/archive/2012/12/31/2840152.html
//EDIT[i, j] = min(EDIT[i - 1, j] + 1, EDIT[i, j - 1] + 1, EDIT[i - 1, j - 1] + f(x[i], j[j]))
//EDIT[i, j] 表示对于字符串a从1到i的子串和字符串b从1到j的字串的编辑距离。（字符串下标从1开始)
//EDIT[i - 1, j] + 1 表示对a 在i 位置删除delete操作
//EDIT[i, j - 1] + 1 表示insert添加操作
//EDIT[i-1, j - 1] + f(x[i], y[j])这里如果x[i] == y[j] 则 f(x[i], y[j]) == 0 否则 == 1
class Solution2
{
private:
    int Min(int x, int y)
    {
        return (x < y ? x : y);
    }

public:
    int minDistance(string word1, string word2)
    {
        int col, row, i, j;

        row = word1.length();
        col = word2.length();
        vector<vector<int> > distance(row + 1, vector<int>(col + 1));

        for (i = 0; i <= row; i++)
            distance[i][0] = i;
        for (j = 0; j <= col; j++)
            distance[0][j] = j;
        for (i = 1; i <= row; i++)
        {
            for (j = 1; j <= col; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                    distance[i][j] = distance[i - 1][j - 1];
                else
                    distance[i][j] = distance[i - 1][j - 1] + 1;
                distance[i][j] = Min(Min(distance[i - 1][j], distance[i][j - 1]) + 1, distance[i][j]);
            }
        }

        return distance[row][col];
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    string word1 = "dinitrophenylhydrazine";
    string word2 = "acetylphenylhydrazine";
  //    string word1 = "abcd";
  //    string word2 = "bd";
 //   cout << s1.minDistance(word1, word2) << endl;
    cout << s2.minDistance(word1, word2) << endl;

    return 0;
}
