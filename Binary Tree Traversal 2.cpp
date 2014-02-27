#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 利用 queue 和 stack 进行操作
class Solution1
{
public:
    vector<vector<int> > levelOrderBottom(TreeNode *root)
    {
        vector<vector<int> > data;
        stack<vector<int> > sta;
        vector<int> level;
        queue<TreeNode*> que;
        int i, n;
        TreeNode *temp;

        if (!root)
            return data;
        que.push(root);
        n = 1;
        while (!que.empty())
        {
            i = 0;
            while (n--)
            {
                temp = que.front();
                que.pop();
                if (temp->left)
                {
                    que.push(temp->left);
                    i++;
                }
                if (temp->right)
                {
                    que.push(temp->right);
                    i++;
                }
                level.push_back(temp->val);
            }
            sta.push(level);
            level.clear();
            n = i;
        }
        while (!sta.empty())
        {
            data.push_back(sta.top());
            sta.pop();
        }

        return data;
    }
};

// 递归 其实相当于树的前序遍历
// 在处理每一个节点时，将数值添加到相应的 vector 中
class Solution2
{
private:
    void traversal(vector<vector<int> > &data, int depth, TreeNode *root)
    {
        if (!root)
            return ;
        if (depth > data.size())
            data.push_back(vector<int>());
        data[depth - 1].push_back(root->val);
        traversal(data, depth + 1, root->left);
        traversal(data, depth + 1, root->right);
    }

    void reverse(vector<vector<int> > &data)
    {
        int i, j;
        vector<int> temp;

        i = 0, j = data.size() - 1;
        while(i < j)
        {
            temp = data[i];
            data[i++] = data[j];
            data[j--] = temp;
        }
    }
public:
    vector<vector<int> > levelOrderBottom(TreeNode *root)
    {
        vector<vector<int> > data;
        traversal(data, 1, root);
        reverse(data);

        return data;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    vector<vector<int> > data;

    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    //data = s1.levelOrderBottom(root);
    data = s2.levelOrderBottom(root);
    for(int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
            cout << data[i][j] << ' ' << endl;
        cout << endl;
    }
    return 0;
}
