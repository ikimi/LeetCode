#include <iostream>
#include <cmath>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 双重递归 即求节点的最深深度需要一次递归求解 而 判断其左右节点都是否为AVL树需要一次递归
// 时间复杂度 和 空间复杂度比较大 但思路更加简洁
class Solution1
{
private:
    int max(int x, int y)
    {
        return (x > y) ? x : y;
    }
    int maxDepth(TreeNode *root)
    {
        if (!root)
            return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

public:
    bool isBalanced(TreeNode *root)
    {
        if (!root)
            return true;
        if (abs(maxDepth(root->left) - maxDepth(root->right)) > 1)
            return false;
        return (isBalanced(root->left) && isBalanced(root->right));
    }
};

// 后序遍历 节点深度通过函数返回值求解
// 只需要递归一次 时间复杂度比 Solution1 好
class Solution2
{
private:
    int maxDepth(TreeNode *root)
    {
        if (!root)
            return 0;

        int ldepth, rdepth;

        ldepth = maxDepth(root->left);
        rdepth = maxDepth(root->right);

        if (ldepth == -1 || rdepth == -1)
            return -1;
        if (abs(ldepth - rdepth) > 1)
            return -1;
        else
            return ((ldepth > rdepth) ? ldepth : rdepth) + 1;
    }
public:
    bool isBalanced(TreeNode *root)
    {
        if (maxDepth(root) == -1)
            return false;
        return true;
    }
};

// 后序遍历 节点深度由参数给出
class Solution3
{
private:
    bool maxDepth(TreeNode *root, int *depth)
    {
        if (!root)
        {
            *depth = 0;
            return true;
        }
        int left, right;
        if (maxDepth(root->left, &left) && maxDepth(root->right, &right))
        {
            if (abs(left - right) > 1)
                return false;
            *depth =  ((left > right) ? left : right) + 1;
            return true;
        }
        else
            return false;
    }
public:
    bool isBalanced(TreeNode *root)
    {
        int depth;

        return maxDepth(root, &depth);
    }
};

// 三种方法的时间复杂度分别为 1 -- 108ms 2--100ms 3--88ms
int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << s1.isBalanced(root) << endl;
    cout << s2.isBalanced(root) << endl;
    cout << s3.isBalanced(root) << endl;

    return 0;
}
#include <iostream>
#include <cmath>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 双重递归 即求节点的最深深度需要一次递归求解 而 判断其左右节点都是否为AVL树需要一次递归
// 时间复杂度 和 空间复杂度比较大 但思路更加简洁
class Solution1
{
private:
    int max(int x, int y)
    {
        return (x > y) ? x : y;
    }
    int maxDepth(TreeNode *root)
    {
        if (!root)
            return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

public:
    bool isBalanced(TreeNode *root)
    {
        if (!root)
            return true;
        if (abs(maxDepth(root->left) - maxDepth(root->right)) > 1)
            return false;
        return (isBalanced(root->left) && isBalanced(root->right));
    }
};

// 后序遍历 节点深度通过函数返回值求解
// 只需要递归一次 时间复杂度比 Solution1 好
class Solution2
{
private:
    int maxDepth(TreeNode *root)
    {
        if (!root)
            return 0;

        int ldepth, rdepth;

        ldepth = maxDepth(root->left);
        rdepth = maxDepth(root->right);

        if (ldepth == -1 || rdepth == -1)
            return -1;
        if (abs(ldepth - rdepth) > 1)
            return -1;
        else
            return ((ldepth > rdepth) ? ldepth : rdepth) + 1;
    }
public:
    bool isBalanced(TreeNode *root)
    {
        if (maxDepth(root) == -1)
            return false;
        return true;
    }
};

// 后序遍历 节点深度由参数给出
class Solution3
{
private:
    bool maxDepth(TreeNode *root, int *depth)
    {
        if (!root)
        {
            *depth = 0;
            return true;
        }
        int left, right;
        if (maxDepth(root->left, &left) && maxDepth(root->right, &right))
        {
            if (abs(left - right) > 1)
                return false;
            *depth =  ((left > right) ? left : right) + 1;
            return true;
        }
        else
            return false;
    }
public:
    bool isBalanced(TreeNode *root)
    {
        int depth;

        return maxDepth(root, &depth);
    }
};

// 三种方法的时间复杂度分别为 1 -- 108ms 2--100ms 3--88ms
int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << s1.isBalanced(root) << endl;
    cout << s2.isBalanced(root) << endl;
    cout << s3.isBalanced(root) << endl;

    return 0;
}

