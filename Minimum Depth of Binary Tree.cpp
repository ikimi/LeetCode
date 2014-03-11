#include <iostream>
#include <queue>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 递归求解最小深度
class Solution1
{
private:
    int Min(int x, int y)
    {
        return (x > y) ? y : x;
    }

    int subMinDepth(TreeNode *root)
    {
        if (!root->left && !root->right)    // WA 了一次
            return 1;
        if (!root->left)
            return subMinDepth(root->right) + 1;
        if (!root->right)
            return subMinDepth(root->left) + 1;

        return Min(subMinDepth(root->left), subMinDepth(root->right)) + 1;
    }

public:
    int minDepth(TreeNode *root)
    {
        if (!root)
            return 0;
        return subMinDepth(root);
    }
};

// 队列层次遍历 当遇到第一个leaf节点时 返回此时的树高度
class Solution2
{
public:
    int minDepth(TreeNode *root)
    {
        if (!root)
            return 0;

        queue<TreeNode*> que;
        TreeNode *top;
        int depth = 1, i, j;
        bool flag;

        que.push(root), i = 1;
        while (!que.empty())
        {
            j = 0;
            while (i--)
            {
                top = que.front();
                que.pop();
                flag = true;

                if (top->left)
                {
                    flag = false;
                    j++;
                    que.push(top->left);
                }
                if (top->right)
                {
                    flag = false;
                    j++;
                    que.push(top->right);
                }
                if (flag)
                    return depth;
            }
            depth++, i = j;
        }

        return depth;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2), root->right = new TreeNode(3);
    root->left->left = new TreeNode(4), root->left->right = new TreeNode(5);
    root->left->right->left = new TreeNode(6);

    cout << s1.minDepth(root) << endl;
    cout << s2.minDepth(root) << endl;

    return 0;
}
