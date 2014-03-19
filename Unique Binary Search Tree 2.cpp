#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution1
{
private:
    vector<TreeNode *> generate(int start, int end)
    {
        vector<TreeNode *> res;
        res.clear();

        if (start > end)
        {
            res.push_back(NULL);
            return res;
        }

        int i, j, k;
        for (i = start; i <= end; i++)
        {
            vector<TreeNode *> left = generate(start, i - 1);
            vector<TreeNode *> right = generate(i + 1, end);
            for (j = 0; j < left.size(); j++)
            {
                for (k = 0; k < right.size(); k++)
                {
                    TreeNode *root = new TreeNode(i);   // 一直在这里 WA 注意要在这里定义临时变量
                    root->left = left[j];               //  否则辉出现问题
                    root->right = right[k];
                    res.push_back(root);
                }
            }
        }

        return res;
    }

public:
    vector<TreeNode *> generateTrees(int n)
    {
        vector<TreeNode *> res;

        res = generate(1, n);
        return res;
    }
};

void bfs(TreeNode *root)
{
    queue<TreeNode *> que;
    TreeNode *top;
    que.push(root);
    while (!que.empty())
    {
        top = que.front();
        que.pop();
        cout << top->val << ' ';
        if (top->left)
            que.push(top->left);
        if (top->right)
            que.push(top->right);
    }
}

int main()
{
    // test example
    Solution1 s1;

    vector<TreeNode *> res;
    res = s1.generateTrees(3);

    //cout << res.size() << endl;
    for (int i = 0; i < res.size(); i++)
    {
        bfs(res[i]);
        cout << endl;
    }

    return 0;
}
