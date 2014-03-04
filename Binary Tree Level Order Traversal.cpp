#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 层次遍历 利用队列
class Solution1
{
public:
    vector<vector<int> > levelOrder(TreeNode *root)
    {
        vector<vector<int> > data;

        if (!root)
            return data;

        int i, n;
        vector<int> row;
        queue<TreeNode *> que;
        TreeNode *temp;

        que.push(root), n = 1;
        while (!que.empty())
        {
            i = 0, row.clear();
            while (n--)
            {
                temp = que.front();
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
                row.push_back(temp->val);
                que.pop();
            }
            n = i;
            data.push_back(row);
        }

        return data;
    }
};

// 递归方法
class Solution2
{
private:
    void Level(vector<vector<int> > &data, TreeNode *root, int level)
    {
        if (!root)
            return ;
        if (data.size() < level)
            data.push_back(vector<int> ());

        data[level - 1].push_back(root->val);
        Level(data, root->left, level + 1);
        Level(data, root->right, level + 1);
    }

public:
    vector<vector<int> > levelOrder(TreeNode *root)
    {
        vector<vector<int> > data;
        Level(data, root, 1);

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

    //data = s1.levelOrder(root);
    data = s2.levelOrder(root);
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
            cout << data[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
