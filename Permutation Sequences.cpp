#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// 采用类似Permutation的方法
// 唯一差别的地方就是：permutation问题只要求解所有的排列就可以，并不要求其大小顺序
// 而本问题需要记录其大小关系，比如 1 2 3 4 的全排列
// 如果仅仅按照permutation的方法 3 2 1 4 要在3 1 2 4之前出现
// 所以每一次调换如 1 2 3 4 --> 3 2 1 4 都需要对子序列进行排序，这里的子序列是 2 1 4 排序后是 1 2 4
// 这样 1 2 3 4 --> 3 1 2 4 就成立了
// count从0开始计数当计数到k的时候 返回res
// TLE...
class Solution1
{
private:
    string res;
    void getPermutationHelper(int low, int high, const int *k, int *count, string &str)
    {
        if (low >= high)
        {
            if (++(*count)== *k)
                res = str.substr(0, high);
            return ;
        }

        for (int index = low; index < high; index++)
        {
            string tmp = str;
            char temp = str[low];
            str[low] = str[index];
            str[index] = temp;

            if (res != "")
                break;
            sort(str.begin() + low + 1, str.end()); // 因为不是乱序查找所有的排列，所以调换位置后 应该重新将子序列排序 最后恢复
            getPermutationHelper(low + 1, high, k, count, str);

            str = tmp;
        }
    }

public:
    string getPermutation(int n, int k)
    {
        res = "";
        int count = 0;
        string str = "123456789";

        getPermutationHelper(0, n, &k, &count, str);
        return res;
    }
};

// 找规律
// 32ms
class Solution2
{
private:
    int data[10];
    string res;
    void exchange(int x, int y)
    {
        char temp = res[x];
        res[x] = res[y];
        res[y] = temp;
    }
    void reverse(int low, int high)
    {
        while (low < high)
        {
            char temp = res[low];
            res[low] = res[high];
            res[high] = temp;
            low++, high--;
        }
    }

public:
    string getPermutation(int n, int k)
    {
        int i, j;

        for (i = 1, res = ""; i <= n; i++)
            res += n - i + 1 + '0';

        for (data[0] = i = 1; i <= n; i++)
            data[i] = data[i - 1] * i;

        while (k)
        {
            for (i = 1; i <= n && data[i] < k;)
                i++;
            if (data[i] == k)
            {
                sort(res.begin(), res.begin() + i);
                break;
            }
            else
            {
                int temp = data[i - 1];
                for (j = 1; j * temp < k;)
                    j++;
                exchange(i - 1, i - j);
                sort(res.begin(), res.begin() + i - 1);
                if (j * temp == k)
                    break;
                else
                {
                    reverse(0, i - 2);
                    k -= (j - 1) * temp;
                }
            }
        }
        reverse(0, res.length() - 1);

        return res;
    }
};

int main()
{
    // test exmaple
    Solution1 s1;
    Solution2 s2;

    cout << s1.getPermutation(9, 305645) << endl;
    cout << s1.getPermutation(4, 7) << endl;
  //  cout << s2.getPermutation(9, 305645) << endl;
 //   for (int i = 1; i <= 2; i++)
        cout << s2.getPermutation(9, 305645) << endl;
    cout << s2.getPermutation(4, 7) << endl;

    return 0;
}
