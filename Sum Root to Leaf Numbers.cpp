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
    int getSum(TreeNode *root, int sum)
    {
        if (!root->left && !root->right)
            return sum * 10 + root->val;
        if (!root->right)
            return getSum(root->left, sum * 10 + root->val);
        if (!root->left)
            return getSum(root->right, sum * 10 + root->val);
        return getSum(root->left, sum * 10 + root->val) + getSum(root->right, sum * 10 + root->val);
    }

public:
    int sumNumbers(TreeNode *root)
    {
        if (!root)
            return 0;
        return getSum(root, 0);
    }
};

// 后序遍历求解
class Solution2
{
public:
    int sumNumbers(TreeNode *root)
    {
        if (!root)
            return 0;

        vector<TreeNode*> sta;
        stack<bool> status;
        TreeNode *top;
        int temp, sum = 0;

        while (root || !sta.empty())
        {
            if (root)
            {
                sta.push_back(root);
                status.push(false);
                root = root->left;
            }
            else
            {
                top = sta[sta.size() - 1];
                if (!status.top())
                {
                    status.pop();
                    status.push(true);
                    root = top->right;
                }
                else
                {
                    if (!top->left && !top->right)
                    {
                        temp = 0;
                        for (int i = 0; i < sta.size(); i++)
                            temp = 10 * temp + sta[i]->val;
                        sum += temp;
                    }
                    sta.erase(sta.end() - 1);
                    status.pop();
                    root = NULL;
                }
            }
        }

        return sum;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2), root->right = new TreeNode(3);
    root->left->left = new TreeNode(4), root->left->right =  new TreeNode(5);

    cout << s1.sumNumbers(root) << endl;
    cout << s2.sumNumbers(root) << endl;
    return 0;
}
