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

// 递归实现 递归判断左右子树
class Solution1
{
    public:
        bool isSameTree(TreeNode *p, TreeNode *q)
        {
            if (!p && !q)
                return true;
            else if (p && q && (p->val == q->val))
            {
                if (isSameTree(p->left, q->left) && isSameTree(p->right, q->right))
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
};


int main()
{

    // test example
    TreeNode *p = new TreeNode(1);
    p->left = new TreeNode(2);
    p->right = new TreeNode(3);
    p->right->left = new TreeNode(4);

    TreeNode *q = new TreeNode(1);
    q->left = new TreeNode(2);
    q->right = new TreeNode(3);
    q->right->left = new TreeNode(4);

    Solution1 s1;
    if (s1.isSameTree(p, q))
        cout << "true" << endl;
    else
    cout << "false" << endl;

    return 0;
}
