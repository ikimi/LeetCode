#include <iostream>
#include <vector>

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
    void subPathSum(vector<vector<int> > &res, vector<int> &path, int cur, TreeNode *root, int sum)
    {
        if (!root)
            return ;

        if (!root->left && !root->right)
        {
            if (root->val + cur == sum)
            {
                path.push_back(root->val);
                res.push_back(path);
                path.erase(path.end() - 1);
            }
            return ;
        }

        path.push_back(root->val);
        subPathSum(res, path, cur + root->val, root->left, sum), subPathSum(res, path, cur + root->val, root->right, sum);
        path.erase(path.end() - 1);
    }

public:
    vector<vector<int> > pathSum(TreeNode *root, int sum)
    {
        vector<vector<int> > res;
        if (!root)
            return res;

        vector<int> path;
        subPathSum(res, path, 0, root, sum);

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;

    vector<vector<int> > data;
    TreeNode *root = new TreeNode(5);
    root->left = new TreeNode(4), root->right = new TreeNode(8);
    root->left->left = new TreeNode(11), root->right->left = new TreeNode(13), root->right->right = new TreeNode (4);
    root->left->left->left = new TreeNode(7), root->left->left->right = new TreeNode(2);
    root->right->right->left = new TreeNode(5), root->right->right->right = new TreeNode(1);

    data = s1.pathSum(root, 22);
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
            cout << data[i][j] << ' ';
        cout << endl;
    }
    return 0;
}
