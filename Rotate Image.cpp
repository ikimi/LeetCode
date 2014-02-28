#include <iostream>
#include <vector>
using namespace std;

// 采用辅助空间的方式 时间复杂度O(n*n) 空间复杂度O(n*n)
class Solution1
{
public:
    void rotate(vector<vector<int> > &matrix)
    {
        vector<vector<int> > temp;
        int i, j, n;

        n = matrix.size();
        for (i = 0; i < n; i++)
        {
            temp.push_back(vector<int> ());
            for (j = n - 1; j >= 0; j--)
                temp[i].push_back(matrix[j][i]);
        }
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                matrix[i][j] = temp[i][j];
    }
};

// 递归算法 每次遍历二维数组的最外层一圈 将每个元素循环移位
// 当二维数组足够小时 终止迭代
class Solution2
{
private:
    void nextPos(int start, int end, int pos[], int step, int n)
    {
        if (step == 0)
        {
            pos[0] = start + n;
            pos[1] = end;
        }
        else if (step == 1)
        {
            pos[0] = end;
            pos[1] = end - n;
        }
        else if (step == 2)
        {
            pos[0] = end - n;
            pos[1] = start;
        }
        else
        {
            pos[0] = start;
            pos[1] = start + n;
        }
    }

    void circle(vector<vector<int> > &matrix, int start, int end)
    {
        int i, j, k, temp, cur[2], next[2];

        for (i = start,k = 0; i < end; i++, k++) // 没给k赋值 WA 三次啊！！
        {
            temp = matrix[start][start + k];
            nextPos(start, end, next, 3, k);
            for (j = 3; j > 0; j--)
            {
                nextPos(start, end, cur, j - 1, k);
                matrix[next[0]][next[1]] = matrix[cur[0]][cur[1]];
                next[0] = cur[0], next[1] = cur[1];
            }
            matrix[next[0]][next[1]] = temp;
            /*
            for (int m = 0; m < 6; m++)
            {
                for (int n = 0; n < 6; n++)
                    cout << matrix[m][n] << ' ';
                cout << endl;
            }
            cout << "-------------" << endl;
            */
        }
    }
public:
    void rotate(vector<vector<int> > &matrix)
    {
        int i, j;

        i = 0, j = matrix.size() - 1;
        while (i < j)
        {
            circle(matrix, i, j);
            i++, j--;
        }
    }
};

// 可以先求矩阵的转置矩阵 然后逆序数组的列即为所求
// 空间复杂度O(1) 时间复杂度O(n*n)
class Solution3
{
private:
    void rotation(vector<vector<int> > &matrix)
    {
        int i, j, n, temp;

        for (i = 0, n = matrix.size(); i < n; i++)
            for (j = i + 1; j < n; j++)
            {
                temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
    }

    void reverse(vector<vector<int> > &matrix)
    {
        int i, j, k, temp, n;

        i = 0, n = matrix.size(), j = n - 1;
        while (i < j)
        {
            for (k = 0; k < n; k++)
            {
                temp = matrix[k][i];
                matrix[k][i] = matrix[k][j];
                matrix[k][j] = temp;
            }
            i++, j--;
        }
    }

public:
    void rotate(vector<vector<int> > &matrix)
    {
        rotation(matrix);
        reverse(matrix);
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    vector<vector<int> > data;
    vector<int> line;

    int i, j, k;
    for (i = k = 0; i < 6; i++)
    {
        line.clear();
        for (j = 0; j < 6; j++)
        {
            line.push_back(k++);
        }
        data.push_back(line);
    }
   // s1.rotate(data);
   // s2.rotate(data);
    s3.rotate(data);
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
            cout << data[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
