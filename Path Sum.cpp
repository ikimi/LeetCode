#include <iostream>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 看错题了 以为所有的节点的权值都为正
// 要是这样的话就可以利用 分治限界 排除一些不可能的分支
// 虽然没过 但是对后序遍历更熟悉了 (纪念一下吧:))
class Solution1
{
public:
    bool hasPathSum(TreeNode *root, int sum)
    {
        if (!root)
            return false;

        stack<TreeNode*> sta;
        stack<bool> status;
        TreeNode *top;
        int value = 0;

        while (root || !sta.empty())
        {
            if (root)
            {
                if (value + root->val <= sum)
                {
                    sta.push(root);
                    status.push(false);
                    value += root->val;
                    root = root->left;
                }
                else
                    root = NULL;
            }
            else
            {
                top = sta.top();
                if (!status.top())
                {
                    status.pop();
                    status.push(true);
                    root = top->right;
                }
                else
                {
                    if (!top->left && !top->right && (value == sum))
                        return true;
                    sta.pop();
                    status.pop();
                    value -= top->val;
                    root = NULL;
                }
            }
        }

        return false;
    }
};

// 递归 正如Solution1必须遍历所有情况才行
class Solution2
{
private:
    bool pathSum(TreeNode *root, int sum, int value)
    {
        if (!root->left && !root->right)
        {
            if (value + root->val == sum)
                return true;
            return false;
        }
        if (root->left && !root->right)
            return pathSum(root->left, sum, value + root->val);
        else if (!root->left && root->right)
            return pathSum(root->right, sum, value + root->val);
        else
            return (pathSum(root->left, sum, value + root->val) || pathSum(root->right, sum, value + root->val));
    }

public:
    bool hasPathSum(TreeNode *root, int sum)
    {
        if (!root)
            return false;

        return pathSum(root, sum, 0);
    }
};

// 采用后序遍历
class Solution3
{
public:
    bool hasPathSum(TreeNode *root, int sum)
    {
        if (!root)
            return false;

        stack<TreeNode*> sta;
        stack<bool> status;
        TreeNode *top;
        int value = 0;

        while (root || !sta.empty())
        {
            if (root)
            {
                value += root->val;
                sta.push(root);
                status.push(false);
                root = root->left;
            }
            else
            {
                top = sta.top();
                if (!status.top())
                {
                    status.pop();
                    status.push(true);
                    root = top->right;
                }
                else
                {
                    if (!top->left && !top->right && (sum == value))
                        return true;
                    value -= top->val;
                    sta.pop();
                    status.pop();
                    root = NULL;
                }
            }
        }

        return false;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    TreeNode *root = new TreeNode(5);
    root->left = new TreeNode(4), root->right = new TreeNode(8);
    root->left->left = new TreeNode(11), root->right->left = new TreeNode(13), root->right->right = new TreeNode(4);
    root->left->left->left = new TreeNode(7), root->left->left->right = new TreeNode(2), root->right->right->right = new TreeNode(1);

    //cout << s1.hasPathSum(root, 27) << endl;
    //cout << s2.hasPathSum(root, 28) << endl;
    cout << s3.hasPathSum(root, 25) << endl;

    return 0;
}
