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
// 8ms
class Solution1
{
    private:
        void inOrder(TreeNode *root, vector<int> &array)
        {
            if (!root)
                return ;
            if (root->left)
                inOrder(root->left, array);
            array.push_back(root->val);
            if (root->right)
                inOrder(root->right, array);
        }

    public:
        vector<int> inorderTraversal(TreeNode *root)
        {
            vector<int> array;

            inOrder(root, array);

            return array;
        }
};

// 非递归
// 利用栈实现 时间复杂度为O(n) 平均空间复杂度为O(log(n)) 最坏情况下为O(n)
// 8ms
class Solution2
{
    public:
        vector<int> inorderTraversal(TreeNode *root)
        {
            vector<int> array;
            stack<TreeNode*> sta;
            TreeNode *temp;

            while(root || !sta.empty())
            {
                if (root)
                {
                    sta.push(root);
                    root = root->left;
                }
                else
                {
                    temp = sta.top();
                    sta.pop();
                    array.push_back(temp->val);
                    root = temp->right;
                }
            }

            return array;
        }
};

// 使用 Morris 中序遍历
// 时间复杂度为O(n)(系数可能比上面使用栈的系数高) 空间复杂度为O(1)
// 8ms
class Solution3
{
public:
    vector<int> inorderTraversal(TreeNode *root)
    {
        TreeNode *pre, *cur;
        vector<int> array;

        cur = root, pre = NULL;
        while (cur)
        {
            if (!cur->left)
            {
                array.push_back(cur->val);
                cur = cur->right;
            }
            else
            {
                pre = cur->left;
                while (pre->right && (pre->right != cur))
                    pre = pre->right;
                if (!pre->right)
                {
                    pre->right = cur;
                    cur = cur->left;
                }
                else
                {
                    array.push_back(cur->val);
                    pre->right = NULL;
                    cur = cur->right;
                }
            }
        }

        return array;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->left->right = new TreeNode(5);

   // vector<int> arr = s1.inorderTraversal(root);
   // vector<int> arr = s2.inorderTraversal(root);
    vector<int> arr = s3.inorderTraversal(root);

    for(int i = 0; i < arr.size(); i++)
        cout << arr[i] << endl;

    return 0;
}

