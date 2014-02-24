#include <iostream>
#include <queue>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 递归 即判断root节点左节点的左子树与右节点右子树对称， 左节点右子树与右节点左子树对称
class Solution1
{
private:
    bool isSym(TreeNode *left, TreeNode *right)
    {
        if (!left && !right)
            return true;
        if (left && right)
        {
            if (left->val == right->val)
            {
                return (isSym(left->left, right->right) && isSym(left->right, right->left));
            }
            else
                return false;
        }
        else
            return false;
    }

public:
    bool isSymmetric(TreeNode *root)
    {
        if (!root)
            return true;

        return isSym(root->left, root->right);
    }
};

// 非递归算法 利用两个队列存储root的左右子树
// 左子树的入队列顺序时先入左孩子，再入右孩子
// 而右子树的入队列顺序是先入右孩子，再入左孩子
// 在压入每一个节点的时候比较是否相同
class Solution2
{
public:
    bool isSymmetric(TreeNode *root)
    {
        if (!root)
            return true;

        queue<TreeNode*> left;
        queue<TreeNode*> right;
        left.push(root), right.push(root);

        while (!left.empty() && !right.empty())
        {
            TreeNode *tmp1, *tmp2;

            tmp1 = left.front(), tmp2 = right.front();
            left.pop(), right.pop();
            if (tmp1->left && tmp2->right)
            {
                if (tmp1->left->val != tmp2->right->val)
                    return false;
                left.push(tmp1->left), right.push(tmp2->right);
            }
            else if (!tmp1->left && !tmp2->right);
            else return false;

            if (tmp1->right && tmp2->left)
            {
                if (tmp1->right->val != tmp2->left->val)
                    return false;
                left.push(tmp1->right), right.push(tmp2->left);
            }
            else if (!tmp1->right && !tmp2->left);
            else return false;
        }

        return true;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);

    cout << s1.isSymmetric(root) << endl;
    cout << s2.isSymmetirc(root) << endl;

    return 0;
}
