#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    生成合法的括号对。
    这里只需要搞清楚“合法(well-formed)”的概念就行了，那就是
    1.左右括号数相等
    2.任一位置之前的右括号数不大于左括号数

    有了这样两点，那么要生成括号对总数为n的所有可能性的串。就从空字符串开始，按照上面的第二点限制，逐步添加左右括号即可。
    当拿到合法的串，长度为k，时，要继续添加一个括号，那么就看这个串如果左括号的数目没有达到n，那就可以在此基础上添加一个左括号；
    同时，如果串内右括号数目小于左括号数目的话，还可以在k串上添加一个右括号。
    这样遍历了所有长度为k的合法串之后，我们就得到了所有合法的长度为k+1的串。
    当我们生成了所有长度为2n的合法串，就得到了答案
*/
// 最简洁的思路解决最难的问题
class Solution1
{
private:
    void generate(vector<string> &res, string str, int left, int right, int n)
    {
        if (left == n)
        {
            for (int i = 0; i < n - right; i++)
                str += ')';
            res.push_back(str);
            return ;
        }
        generate(res, str + '(', left + 1, right, n);
        if (left > right)
            generate(res, str + ')', left, right + 1, n);
    }

public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> res;
        generate(res, "", 0, 0, n);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    vector<string> str;

    str = s1.generateParenthesis(3);
    for (int i = 0; i < str.size(); i++)
        cout << str[i] << endl;

    return 0;
}
