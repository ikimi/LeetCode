#include <iostream>
#include <deque>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 利用 STL 双向队列
class Solution1
{
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int> > res;
        vector<int> row;
        deque<TreeNode*> que;
        int direction;
        int i, j;
        TreeNode *top;

        if(!root)
            return res;

        que.push_back(root);
        row.push_back(root->val);
        res.push_back(row);
        direction = 1, i = 1;

        while (!que.empty())
        {
            j = 0, row.clear();
            while (i)
            {
                if (direction == 1)
                {
                    top = que.front();
                    que.pop_front();
                    if (top->right)
                    {
                        que.push_back(top->right);
                        row.push_back(top->right->val);
                        j++;
                    }
                    if (top->left)
                    {
                        que.push_back(top->left);
                        row.push_back(top->left->val);
                        j++;
                    }
                }
                else
                {
                    top = que.back();
                    que.pop_back();
                    if (top->left)
                    {
                        que.push_front(top->left);
                        row.push_back(top->left->val);
                        j++;
                    }
                    if (top->right)
                    {
                        que.push_front(top->right);
                        row.push_back(top->right->val);
                        j++;
                    }
                }
                i--;
            }
            i = j;
            direction *= -1;
            res.push_back(row);
        }
        res.pop_back(); // 每次都多添加一个空行 所以最后要删除 WA了一次

        return res;
    }
};

// 利用两个栈实现
//
class Solution2
{
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int> > res;

        if (!root)
            return res;

        stack<TreeNode*> lsta, rsta;
        vector<int> row;
        TreeNode *top;

        lsta.push(root);
        row.push_back(root->val);
        res.push_back(row);

        while (!lsta.empty() || !rsta.empty())
        {
            row.clear();
            if (!lsta.empty())
            {
                while (!lsta.empty())
                {
                    top = lsta.top();
                    lsta.pop();
                    if (top->right)
                    {
                        rsta.push(top->right);
                        row.push_back(top->right->val);
                    }
                    if (top->left)
                    {
                        rsta.push(top->left);
                        row.push_back(top->left->val);
                    }
                }
                if (row.size())             // 又忘记增加边界处理 WA了一次
                    res.push_back(row);
            }
            else
            {
                while (!rsta.empty())
                {
                    top = rsta.top();
                    rsta.pop();
                    if (top->left)
                    {
                        lsta.push(top->left);
                        row.push_back(top->left->val);
                    }
                    if (top->right)
                    {
                        lsta.push(top->right);
                        row.push_back(top->right->val);
                    }
                }
                if (row.size())        // 又忘记增加边界处理 WA了一次
                    res.push_back(row);
            }
        }

        return res;
    }
};
// 也可以利用 层次遍历的递归算法

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<vector<int> > res;
    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(9), root->right = new TreeNode(20);
    root->left->left = new TreeNode(6), root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    //res = s1.zigzagLevelOrder(root);
    res = s2.zigzagLevelOrder(root);

    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            cout << res[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
