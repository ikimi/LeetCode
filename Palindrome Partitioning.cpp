#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// dfs
// 116ms
class Solution1
{
private:
    vector<vector<string> > res;
    bool isPalindrome(string s, int low, int high)
    {
        while (low < high)
        {
            if (s[low++] != s[high--])
                return false;
        }

        return true;
    }

    void helper(vector<string> &data, string s, int low, int high)
    {
        if (low > high)
        {
            res.push_back(data);
            return ;
        }

        for (int i = low; i <= high; i++)
        {
            if (isPalindrome(s, low, i))
            {
                data.push_back(s.substr(low, i - low + 1));
                helper(data, s, i + 1, high);
                data.pop_back();
            }
        }
    }

public:
    vector<vector<string> > partition(string s)
    {
        vector<string> data;
        helper(data, s, 0, s.length() - 1);

        return res;
    }
};

// dp (并非绝对意义上的DP 只是在判断子串是否是回文时 用到DP的思想)
// 64ms
class Solution2
{
private:
    vector<vector<string> > res;
    vector<string> data;
    vector<vector<bool> > status;

    void helper(string s, int low, int high)
    {
        if (low > high)
        {
            res.push_back(data);
            return ;
        }
        for (int i = low; i <= high; i++)
        {
            if (status[low][i])
            {
                data.push_back(s.substr(low, i - low + 1));
                helper(s, i + 1, high);
                data.pop_back();
            }
        }
    }

    void preProcess(string s)
    {
        int len = s.length();
        for (int i = 0; i < len; i++)
        {
            status.push_back(vector<bool>());
            for (int j = 0; j < len; j++)
                status[i].push_back(false);
        }
        for (int i = 0; i < len; i++)
        {
            status.push_back(vector<bool>());
            for (int j = i; j < len; j++)
            {
                if (isPalindrome(s, i, j))
                    status[i][j] = true;
            }
        }
    }

    bool isPalindrome(string s, int low, int high)
    {
        while (low < high)
        {
            if (s[low++] != s[high--])
                return false;
        }
        return true;
    }

public:
    vector<vector<string> > partition(string s)
    {
        preProcess(s);
        helper(s, 0, s.length() - 1);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    vector<vector<string> > res;
    string s = "aa";

    //res = s1.partition(s);
    res = s2.partition(s);

    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            cout << res[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
