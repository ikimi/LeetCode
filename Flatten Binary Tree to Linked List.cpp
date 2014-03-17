#include <iostream>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 利用先序遍历 将遍历结果存储在新的树中 最后返回新的树
// 时间复杂度O(n) 空间复杂度O(n)
// 但是更改不了root指针的指向 所以方案失败
class Solution1
{
public:
    void flatten(TreeNode *root)
    {
        if (!root)
            return ;

        stack<TreeNode*> sta;
        TreeNode *bin = root;
        TreeNode *fla = NULL;
        TreeNode *res = NULL;

        while (bin || !sta.empty())
        {
            if (bin)
            {
                if (!res)
                {
                    fla = new TreeNode(bin->val);
                    res = fla;
                }
                else
                {
                    fla->right = new TreeNode(bin->val);
                    fla = fla->right;
                }
                sta.push(bin);
                bin = bin->left;
            }
            else
            {
                TreeNode *top = sta.top();
                sta.pop();
                bin = top->right;
            }
        }

        root = res;
    }
};

// in-place 方案
// 80ms
class Solution2
{
public:
    void flatten(TreeNode *root)
    {
        TreeNode *right, *temp;
        while (root)
        {
            if (root->left)
            {
                right = root->right;
                temp = root->left;
                while (temp->right)
                    temp = temp->right;
                temp->right = right;
                root->right = root->left;
            }
            root->left = NULL;  // 注意将left 变为 right 后 left应该变为空 在这里WA了一次
            root = root->right;
        }
    }
};

// 应用递归
// 48ms
class Solution3
{
private:
    TreeNode *makeLine(TreeNode *root)
    {
        if (!root || (!root->left && !root->right))
            return root;

        TreeNode *left = root->left;
        TreeNode *right = root->right;

        root->left = NULL;
        if (left)
        {
            root->right = left;
            root =  makeLine(left);
        }
        if (right)
        {
            root->right = right;
            root = makeLine(right);
        }

        return root;
    }

public:
    void flatten(TreeNode *root)
    {
        makeLine(root);
    }
};

int main()
{
    // test example
    Solution2 s2;
    Solution3 s3;

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
  //  root->right = new TreeNode(2);
   // root->left->left = new TreeNode(3);
  //  root->left->right = new TreeNode(4);
//root->right->right = new TreeNode(6);

   // s2.flatten(root);
    s3.flatten(root);
    while (root)
    {
        cout << root->val << ' ';
        root = root->right;
    }

    cout << endl;

    return 0;
}
