#include <iostream>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 递归求解
// 对于某一个节点root 有四种情况
// 1)左子树的最大值 < root < 右子树的最小值 此时递归调整root 左子树/右子树
// 2)左子树最大值 > root && root < 右子树最小值 此时调换root 与左子树最大值即可
// 3)左子树最大值 < root && root > 右子树最小值 此时调换root 与右子树最小值即可
// 4)右子树最小值 < root < 左子树最大值 此时调换左子树最大值与右子树最小值即可
// 注意要处理指针是NULL的情况 这也是代码较长的原因
// 272ms
class Solution1
{
private:
    TreeNode *Min(TreeNode *a, TreeNode *b)
    {
        return (a->val < b->val) ? a : b;
    }

    TreeNode *Max(TreeNode *a, TreeNode *b)
    {
        return (a->val > b->val) ? a : b;
    }

    TreeNode *getMin(TreeNode *root)
    {
        if (!root)
            return NULL;
        if (!root->left && !root->right)
            return root;
        if (!root->left)
            return Min(root, getMin(root->right));
        if (!root->right)
            return Min(root, getMin(root->left));
        return Min(root, Min(getMin(root->left), getMin(root->right)));
    }

    TreeNode *getMax(TreeNode *root)
    {
        if (!root)
            return NULL;
        if (!root->left && !root->right)
            return root;
        if (!root->left)
            return Max(root, getMax(root->right));
        if (!root->right)
            return Max(root, getMax(root->left));
        return Max(root, Max(getMax(root->left), getMax(root->right)));
    }

    void helper(TreeNode *root)
    {
        TreeNode *max = getMax(root->left);
        TreeNode *min = getMin(root->right);

        if (!min && !max)
            return ;
        if (!max)
        {
            if (root->val > min->val)
            {
                int temp = root->val;
                root->val = min->val;
                min->val = temp;
                return ;
            }
            helper(root->right);
            return ;
        }
        if (!min)
        {
            if (root->val < max->val)
            {
                int temp = root->val;
                root->val = max->val;
                max->val = temp;
                return ;
            }
            helper(root->left);
            return ;
        }
        if (max->val < root->val && root->val < min->val)
        {
            helper(root->left);
            helper(root->right);
            return ;
        }
        if (root->val < max->val && root->val < min->val)
        {
            int temp = root->val;
            root->val = max->val;
            max->val = temp;
            return ;
        }
        if (root->val > max->val && root->val > min->val)
        {
            int temp = root->val;
            root->val = min->val;
            min->val = temp;
            return ;
        }
        if (root->val < max->val && root->val > min->val)
        {
            int temp = max->val;
            max->val = min->val;
            min->val = temp;
            return ;
        }
        return ;
    }

public:
    void recoverTree(TreeNode *root)
    {
        if (!root)
            return ;
        helper(root);
    }
};

// BST的中序遍历结果是一个非递减序列 所以若BST树中有两个节点的位置被调换 那么在中序遍历过程中一定会出现两个节点first和second
// 在中序遍历BST时，若出现第一个其值 小于 其前驱节点时，则将第一个排错的数字计为first
// 接着遍历 当出现第一个其值 大于 first的值时，其前驱节点设为second
// 此时交换 first和second的值即可
// 算法的空间复杂度为O（h） h为递归嵌套的深度, 平均情况h为logn 最坏情况为n
// 260ms
class Solution2
{
private:
    void inorderTraversal(TreeNode *root, TreeNode * &pre, TreeNode * &first, TreeNode * &second)
    {
        if (!root)
            return ;
        if (first && second)    // 不提前跳出 284ms 提前跳出 260ms
            return ;
        inorderTraversal(root->left, pre, first, second);
        if (pre)
        {
            if (!first && root->val < pre->val)
                first = pre;
            else if (first && root->val > first->val)
                second = pre;
            if (first && second)
                return ;
        }
        pre = root;
        inorderTraversal(root->right, pre, first, second);
    }

public:
    void recoverTree(TreeNode *root)
    {
        TreeNode *pre, *first, *second;

        pre = first = second = NULL;
        inorderTraversal(root, pre, first, second);
        if (first)
        {
            if (!second)
                second = pre;
            int temp = first->val;
            first->val = second->val;
            second->val = temp;
        }

        return ;
    }
};

// 利用 stack 进行中序遍历
// 空间复杂度为 O(h) h 为栈的深度 平均情况下为 log(n) 最坏情况下为 n
// 288ms
class Solution3
{
public:
    void recoverTree(TreeNode *root)
    {
        TreeNode *pre, *first, *second;
        stack<TreeNode *> sta;

        pre = first = second = NULL;
        while (root || !sta.empty())
        {
            if (root)
            {
                sta.push(root);
                root = root->left;
            }
            else
            {
                TreeNode *top = sta.top();
                sta.pop();
                if (pre)
                {
                    if (!first && top->val < pre->val)
                        first = pre;
                    else if (first && top->val > first->val)
                        second = pre;
                    if (first && second)
                        break;
                }
                pre = top;
                root = top->right;
            }
        }

        if (!second)
            second = pre;
        int temp = first->val;
        first->val = second->val;
        second->val = temp;

        return ;
    }
};

// Morris Traversal
// 时间复杂度 O(n) 空间复杂度O(1)
// 288ms
class Solution4
{
public:
    void recoverTree(TreeNode *root)
    {
        TreeNode *cur, *tmp, *pre, *first, *second;

        cur = root, tmp = pre = first = second = NULL;
        while (cur)
        {
            if (!cur->left)
            {
                if (pre)
                {
                    if (!first && cur->val < pre->val)
                        first = pre;
                    else if (first && !second && cur->val > first->val)
                        second = pre;
                    /* 在first 和 second 都求出来的情况下 不需要退出 因为此时Morris遍历还没有恢复原来树的结构
                    if (first && second)
                        break;
                    */
                }
                pre = cur;
                cur = cur->right;
            }
            else
            {
                tmp = cur->left;
                while (tmp->right && (tmp->right != cur))
                    tmp = tmp->right;
                if (!tmp->right)
                {
                    tmp->right = cur;
                    cur = cur->left;
                }
                else
                {
                    if (pre)
                    {
                        if (!first && (cur->val < pre->val))
                            first = pre;
                        else if (first && !second && (cur->val > first->val))
                            second = pre;
                        /* first 和 second 都求出来之后 不能退出 否则可能无法恢复原来树的结构
                        if (first && second)
                            break;
                        */
                    }
                    pre = cur;
                    tmp->right = NULL;
                    cur = cur->right;
                }
            }
        }

        if (!second)
            second = pre;
        int temp = first->val;
        first->val = second->val;
        second->val = temp;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;
    Solution4 s4;

/*
    TreeNode *root = new TreeNode(68);
    root->left = new TreeNode(41);
    root->left->left = new TreeNode(-85);
    root->left->left->left = new TreeNode(-73);
    root->left->left->right = new TreeNode(-49);
    root->left->left->left->left = new TreeNode(-98);
    root->left->left->left->left->left = new TreeNode(-124);
*/
    TreeNode *root = new TreeNode (2);
  //  root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(1);

    //s1.recoverTree(root);
    //s2.recoverTree(root);
    //s3.recoverTree(root);
    s4.recoverTree(root);

    cout << root->val << endl;
  //  cout << root->left->val << endl;
    cout << root->right->val << endl;
    cout << root->right->left->val << endl;
  //  cout << root->left->left->val << endl;
  //  cout << root->left->left->left->val << endl;

    return 0;
}
