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

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->left->right = new TreeNode(5);

   // vector<int> arr = s1.inorderTraversal(root);
    vector<int> arr = s2.inorderTraversal(root);
    for(int i = 0; i < arr.size(); i++)
        cout << arr[i] << endl;

    return 0;
}
