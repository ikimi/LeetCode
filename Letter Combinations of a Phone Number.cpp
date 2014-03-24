#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// dfs
// 4ms
class Solution1
{
private:
    string letters[8];
    vector<string> res;

    void helper(string s, string digits, int length, int cur)
    {
        const static string letters[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        if (cur >= length)
        {
            res.push_back(s);
            return ;
        }

        if (digits[cur] == '1' || digits[cur] == '0')
            helper(s, digits, length, cur + 1);
        else
        {
            for (int i = 0; i < letters[digits[cur] - '0' - 2].length(); i++)
            {
                s += letters[digits[cur] - '0' -2][i];
                helper(s, digits, length, cur + 1);
                s.erase(s.end() - 1);
            }
        }
    }

public:
    vector<string> letterCombinations(string digits)
    {
        int len = digits.length();
        string s;

        if (len <= 0)
        {
            res.push_back("");   // 蛋疼 在这里 WA 了一次
            return res;
        }

        helper(s, digits, len, 0);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    vector<string> res;

    res = s1.letterCombinations("23");
    cout << res.size() << endl;
    for (int i = 0; i < res.size(); i++)
        cout << res[i]<< endl;

    return 0;
}
