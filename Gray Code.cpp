#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 参见百度百科 Gray Code:http://baike.baidu.com/view/358724.htm
// 递归求解法
// 假设现在有 n - 1位的Gray Code 那么 n 位的Gray Code 可以这样生成
// 顺序遍历 n - 1个数，并在每一个数前添加0,倒序遍历所有数，并在每一个数前添加1
class Solution1
{
public:
    vector<int> grayCode(int n)
    {
        int i, j, mark, temp;
        vector<int> data;

        if (n < 0)
            return data;

        mark = 1, data.push_back(0);
        for (i = 0; i < n; i++)
        {
            for (j = data.size() - 1; j >= 0; j--)
            {
                temp = data[j] | mark;
                data.push_back(temp);
            }
            mark <<= 1;
        }

        return data;
    }
};

// 非递归算法 根据数字的二进制表示直接生成相应的Gray Code
// 此方法从对应的n位二进制码字中直接得到n位格雷码码字，步骤如下：
//对n位二进制的码字，从右到左，以0到n-1编号
//如果二进制码字的第i位和i+1位相同，则对应的格雷码的第i位为0，否则为1（当i+1=n时，二进制码字的第n位被认为是0，即第n-1位不变）
class Solution2
{
public:
    vector<int> grayCode(int n)
    {
        int i, j, num, mark, res;
        vector<int> data;

        num = pow(2, n);
        for (i = 0; i < num; i++)
        {
            res = i;
            for (j = 0, mark = 1; j < n; j++)
            {
                if ((res & mark) * 2  == (res & (mark << 1)))
                    res &= ~mark;
                else
                    res |= mark;
                mark <<= 1;    // 错在这个地方 WA了两次
            }
            data.push_back(res);
        }

        return data;
    }
};

// 移位异或 （不是很懂。。。）
class Solution3
{
public:
    vector<int> grayCode(int n)
    {
        int i, len;
        vector<int> data;

        len = 1 << n;
        for (i = 0; i < len; i++)
            data.push_back(i ^ (i >> 1));

        return data;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;
    vector<int> data;

    //data = s1.grayCode(2);
   // data = s2.grayCode(4);
   data = s3.grayCode(4);
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << endl;

    return 0;
}
