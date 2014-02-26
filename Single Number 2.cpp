#include <iostream>
#include <map>

using namespace std;

// 用 map 时间复杂度为O(n) 空间复杂度为O(n)
// map<num times> times用来存储num出现的次数
class Solution1
{
public:
    int singleNumber(int A[], int n)
    {
        map<int, int> list;
        map<int, int>::iterator iter;
        int i;

        for (i = 0; i < n; i++)
        {
            iter = list.find(A[i]);
            if (iter == list.end())
                list.insert(pair<int, int>(A[i], 1));
            else
                (*iter).second++;
        }
        for (iter = list.begin(); iter != list.end(); iter++)
            if ((*iter).second == 1)
                return (*iter).first;

        return 0;
    }
};

// 位运算
class Solution2
{
public:
    int singleNumber(int A[], int n)
    {
        int i, j, len, id, res, count;

        len = sizeof(int) * 8, res = 0, id = 1;
        for (i = 0; i < len; i++)
        {
            for (j = count = 0; j < n; j++)
            {
                if (A[j] & id)
                    count++;
            }
            if (count % 3)
                res ^= id;
            id <<= 1;
        }

        return res;
    }
};

// 位运算 n个数字除了出现一次的数字外，其他的数字在每一位上'1'出现的次数都为3的倍数
// 将这些1置0 则最后剩余的就是出现一次的数字在这一bit上的值
// 思路同方法二 只不过方法三的代码更简洁
// 其实就是利用二进制来模拟三进制
class Solution3
{
public:
    int singleNumber(int A[], int n)
    {
        int i, ones, twos, threes;

        ones = twos = threes = 0;
        for (i = 0; i < n; i++)
        {
            twos |= ones & A[i];
            ones ^= A[i];
            threes = ~(ones & twos);
            ones &= threes;
            twos &= threes;
        }

        return ones;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    int A[] = {1, 2, 2, 4, 2, 1, 1, 4, 5, 4};
    cout << s1.singleNumber(A, 10) << endl;
    cout << s2.singleNumber(A, 10) << endl;
    cout << s3.singleNumber(A, 10) << endl;

    return 0;
}

