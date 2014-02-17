#include <iostream>
#include <queue>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 解法1：递归实现
class Solution1
{
    private:
        int max(int left, int right)
        {
            if (left > right)
                return left;
            return right;
        }
    public:
        int maxDepth(TreeNode *root)
        {
            if (!root)
                return 0;
            return (max(maxDepth(root->left), maxDepth(root->right)) + 1);
        }
};

// 解法2：队列实现 BFS
class Solution2
{
    public:
        int maxDepth(TreeNode *root)
        {
            int i, j, depth;
            TreeNode *temp;
            queue <TreeNode*> que;

            if (!root)
                return 0;
            i = j = 1, depth = 0;
            que.push(root);

            while (j)
            {
                j = 0;
                while (i--)
                {
                    temp = que.front();
                    if (temp->left)
                    {
                        que.push(temp->left);
                        j++;
                    }
                    if (temp->right)
                    {
                        que.push(temp->right);
                        j++;
                    }
                    que.pop();
                }
                depth++;
                i = j;
            }
            return depth;
        }
};

// 解法3：使用 DFS 后序遍历，弹栈时，栈的大小即为深度 求其最大值

int main()
{
    // test example
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);

    //Solution1 s1;
    //cout << s1.maxDepth(root) << endl;
    Solution2 s2;
    cout << s2.maxDepth(root) << endl;

    return 0;
}
