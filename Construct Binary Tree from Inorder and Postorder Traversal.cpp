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

// 水题 一遍AC
// 156ms
class Solution1
{
private:
    TreeNode *build(vector<int> &inorder, int inlow, int inhigh, vector<int> &postorder, int postlow, int posthigh)
    {
        if ((inlow > inhigh) || (postlow > posthigh))
            return NULL;

        TreeNode *root = new TreeNode(postorder[posthigh]);
        int i, n;
        for (i = inlow, n = 0; i <= inhigh && inorder[i] != postorder[posthigh]; i++)
            n++;
        root->left = build(inorder, inlow, inlow + n - 1, postorder, postlow, postlow + n - 1);
        root->right = build(inorder, inlow + n + 1, inhigh, postorder, postlow + n, posthigh - 1);

        return root;
    }

public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        return build(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }
};

void inorderTraversal(TreeNode *root)
{
    if (!root)
        return ;

    inorderTraversal(root->left);
    cout << root->val << ' ';
    inorderTraversal(root->right);
}

void postorderTraversal(TreeNode *root)
{
    if (!root)
        return ;

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->val << ' ';
}

int main()
{
    // test example
    Solution1 s1;

    vector<int> inorder;
    vector<int> postorder;

    inorder.push_back(3);
    inorder.push_back(2);
    inorder.push_back(4);
    inorder.push_back(1);
    inorder.push_back(5);
    inorder.push_back(6);

    postorder.push_back(3);
    postorder.push_back(4);
    postorder.push_back(2);
    postorder.push_back(6);
    postorder.push_back(5);
    postorder.push_back(1);

    TreeNode *root = s1.buildTree(inorder, postorder);
    inorderTraversal(root);
    cout << endl;
    postorderTraversal(root);
    cout << endl;

    return 0;
}
