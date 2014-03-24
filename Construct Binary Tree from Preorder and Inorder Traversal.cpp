#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 176ms
class Solution1
{
private:
    TreeNode *helper(vector<int> &preorder, int preStart, int preEnd, vector<int> &inorder, int inStart, int inEnd)
    {
        if (preStart > preEnd)
            return NULL;
        if (inStart > inEnd)    // WA 了一次
            return NULL;

        int i;
        TreeNode *root = new TreeNode (preorder[preStart]);
        for (i = inStart; i <= inEnd; i++)
            if (inorder[i] == preorder[preStart])
                break;
        root->left = helper(preorder, preStart + 1, preStart + i - inStart, inorder, inStart, i - 1);
        root->right = helper(preorder, preStart + i - inStart + 1, preEnd, inorder, i + 1, inEnd);

        return root;
    }

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        return helper(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
};

int main()
{
    // test example
    Solution1 s1;

    TreeNode *root;
    vector<int> preorder;
    vector<int> inorder;
    preorder.push_back(4), preorder.push_back(2), preorder.push_back(1), preorder.push_back(3), preorder.push_back(5);
    inorder.push_back(1), inorder.push_back(2), inorder.push_back(3), inorder.push_back(4), inorder.push_back(5);

    root = s1.buildTree(preorder, inorder);
    cout << root->val << endl;
    cout << root->left->val<< endl;
    cout << root->right->val << endl;

    return 0;
}
