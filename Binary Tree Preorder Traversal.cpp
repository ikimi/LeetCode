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

// 递归解法
// 28ms
class Solution1
{
    private:
        void preOrder(TreeNode *root, vector<int> &array)
        {
            if (!root)
                return ;
            array.push_back(root->val);
            preOrder(root->left, array);
            preOrder(root->right, array);
        }

    public:
        vector<int> preorderTraversal(TreeNode *root)
        {
            vector<int> array;
            preOrder(root, array);

            return array;
        }
};

// 非递归实现
// 时间复杂度O(n) 平均空间复杂度O(logn) 最坏时间复杂度O(n)
// 8ms
class Solution2
{
    public:
        vector<int> preorderTravelsal(TreeNode *root)
        {
            stack<TreeNode *> sta;
            TreeNode *temp;
            vector <int> array;

            while (root || !sta.empty())
            {
                if (root)
                {
                    array.push_back(root->val);
                    sta.push(root);
                    root = root->left;
                }
                else
                {
                    temp = sta.top();
                    sta.pop();
                    root = temp->right;
                }
            }

            return array;
        }
};

// Morris Traversal 前序遍历
// 时间复杂度为O(n) 空间复杂度为O(1)
// 32ms
class Solution3
{
public:
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> array;

        TreeNode *cur, *pre;
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
                    array.push_back(cur->val);
                    pre->right = cur;
                    cur = cur->left;
                }
                else
                {
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
    TreeNode *root = new TreeNode(1);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->left = new TreeNode(2);
    root->left->right = new TreeNode(5);

    Solution1 s1;
    Solution2 s2;
    Solution3 s3;
    vector <int> array;

    //array = s1.preorderTraversal(root);
   // array = s2.preorderTravelsal(root);
    array = s3.preorderTraversal(root);

    for (int i = 0; i < array.size(); i++)
        cout << array[i] << endl;
    return 0;
}
