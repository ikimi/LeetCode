#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 题目的意思是根据数组构造AVL树，即平衡二叉树
// 思路：刚开始总是想如何从基本的方法构造AVL树，回顾了AVL树的性质，以及添加节点如何旋转节点
// 使AVL树重新平衡，越走越远。。。

// 递归 每次选取中间节点微root，数组左边为其左子树，数组右边为其右子树。
// 这种分隔方式使得 root左右节点最多差一个，也就时最多只能相差一层
// 注意：这种递归方式创建的树 与 通常构造AVL树方式 构造出的树可能不同 即：AVL树不唯一！！
class Solution1
{
    private:
        TreeNode *arrayToTree(vector<int> &num, int low, int high)
        {
            if (low >= high)
            {
                if (low == high)
                {
                    TreeNode *root = new TreeNode(num[low]);
                    return root;
                }
                else
                    return NULL;
            }
            int mid = (low + high) / 2;
            TreeNode *root = new TreeNode(num[mid]);
            root->left = arrayToTree(num, low, mid - 1);
            root->right = arrayToTree(num, mid + 1, high);

            return root;
        }

    public:
        TreeNode *sortedArrayToBST(vector<int> &num)
        {
            if (!num.size())
                return NULL;
            return arrayToTree(num, 0, num.size() - 1);
        }
};

// 通常方式构造 AVL树
class Solution2
{
    public:
        TreeNode *sortedArrayToBST(vector<int> &num)
        {

        }
};
int main()
{
    // test example
    Solution1 s1;
    vector<int> A;
    A.push_back(1);
   // A.push_back(2);
    A.push_back(3);
   // A.push_back(4);
    //A.push_back(5);
    TreeNode *root = NULL;

    root = s1.sortedArrayToBST(A);

    cout << root->val << endl;
    cout << root->right->val << endl;
    cout << root->left->val << endl;
   // cout << root->left->right->val << endl;
   // cout << root->right->right->val << endl;
   // cout << root->left->left->val << endl;

    return 0;
}
