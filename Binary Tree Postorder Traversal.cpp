#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 递归
class Solution1
{
private:
    void postOrder(vector<int> &data, TreeNode *root)
    {
        if (!root)
            return ;
        postOrder(data, root->left);
        postOrder(data, root->right);
        data.push_back(root->val);
    }
public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> data;
        postOrder(data, root);

        return data;
    }
};

// 非递归遍历 利用一个数据栈 和 一个状态栈 最环的空间复杂度为O(n)
class Solution2
{
public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> res;
        stack<TreeNode*> sta;
        stack<bool> status;
        TreeNode *temp;

        while (root || !sta.empty())
        {
            if (root)
            {
                sta.push(root);
                status.push(false);
                root = root->left;
            }
            else
            {
                if (!status.top())
                {
                    status.pop();
                    status.push(true);
                    temp = sta.top();
                    root = temp->right;
                }
                else
                {
                    temp = sta.top();
                    sta.pop();
                    res.push_back(temp->val);
                    status.pop();
                    root = NULL;
                }
            }
        }

        return res;
    }
};

// 非递归 当某节点的左右子树都为空时 处理此节点
// 有点：不需要辅助空间 缺点：破坏了原有的树结构
class Solution3
{
public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> res;
        if (!root)
            return res;

        stack<TreeNode*> sta;
        sta.push(root);
        TreeNode *top;

        while (!sta.empty())
        {
            top = sta.top();
            if (top->left)
            {
                sta.push(top->left);
            }
            else if (top->right)
            {
                sta.push(top->right);
            }
            else
            {
                res.push_back(top->val);
                sta.pop();
                if (!sta.empty())
                {
                    if (sta.top()->left)
                        sta.top()->left = NULL;
                    else
                        sta.top()->right = NULL;
                }
            }
        }

        return res;
    }
};

// 后序遍历的特点是：left->right->mid 而若将前序遍历 mid->left->right左右子树的遍历顺序调换mid->right->left
// 刚好是后序遍历的逆序 所以我们可以先求出这个逆序 然后再求后序遍历的结果
class Solution4
{
private:
    void reverse(vector<int> &data)
    {
        int i, j, n, temp;

        n = data.size();
        for (i = 0, j = n - 1; i < j; i++, j--)
        {
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    };

public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> res;
        if (!root)
            return res;

        stack<TreeNode*> sta;
        TreeNode *temp;

        sta.push(root);
        while (!sta.empty())
        {
            temp = sta.top();
            sta.pop();
            res.push_back(temp->val);
            if (temp->left)
                sta.push(temp->left);
            if (temp->right)
                sta.push(temp->right);
        }
        reverse(res);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;
    Solution4 s4;
    vector<int> data;

    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

   // data = s1.postorderTraversal(root);
   // data = s2.postorderTraversal(root);
  //  data = s3.postorderTraversal(root);
    data = s4.postorderTraversal(root);

    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i] << ' ';
    }
    cout << endl;

    return 0;
}
