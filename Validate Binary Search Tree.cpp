#include <iostream>
#include <climits>  // 要用到 c 语言的头文件
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// dfs 递归搜索
// 每次进入某个层次 都要更新下一层的最大值和最小值
// 80ms
class Solution1
{
private:
    bool helper(TreeNode *root, int min, int max)
    {
        if (!root)
            return true;

        if (root->val <= min || root->val >= max)   // 注意此时的BST中没有重复元素
            return false;

        return (helper(root->left, min, root->val) && helper(root->right, root->val, max));
    }

public:
    bool isValidBST(TreeNode *root)
    {
        return helper(root, INT_MIN, INT_MAX);
    }
};

// 利用 BST 中序遍历结果是一个单点递增序列
// 所以我们可以中序遍历 BST 然后判断其是否为单调递增的
// 56ms
class Solution2
{
private:
    bool helper(TreeNode *root)
    {
        stack<TreeNode *> sta;
        TreeNode *top;
        int min = INT_MIN;

        while (root || !sta.empty())
        {
            if (root)
            {
                sta.push(root);
                root = root->left;
            }
            else
            {
                top = sta.top();
                sta.pop();
                if (top->val <= min)
                    return false;
                min = top->val;
                root = top->right;
            }
        }

        return true;
    }

public:
    bool isValidBST(TreeNode *root)
    {
        return helper(root);
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    TreeNode *root = new TreeNode(5);
    root->left = new TreeNode(3), root->right = new TreeNode(8);
    root->left->left = new TreeNode(2), root->left->right = new TreeNode(4);

    cout << s1.isValidBST(root) << endl;
    cout << s2.isValidBST(root) << endl;

    return 0;
}
