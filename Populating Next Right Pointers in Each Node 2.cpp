#include <iostream>
#include <queue>

using namespace std;

struct TreeLinkNode
{
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

// 使用队列
class Solution1
{
public:
    void connect(TreeLinkNode *root)
    {
        if (!root)
            return ;

        queue<TreeLinkNode *> que;
        TreeLinkNode *top, *temp;
        int i, j;
        que.push(root), i = 1;

        while(!que.empty())
        {
            j = 0, temp = NULL;
            while (i--)
            {
                top = que.front();
                que.pop();
                if (top->left)
                {
                    if (temp)
                        temp->next = top->left;
                    temp = top->left;
                    que.push(top->left);
                    j++;
                }
                if (top->right)
                {
                    if (temp)
                        temp->next = top->right;
                    temp = top->right;
                    que.push(top->right);
                    j++;
                }
            }
            i = j;
        }
    }
};

// 空间复杂度为O(1)的方法
// 利用 next 指针
class Solution2
{
private:
    TreeLinkNode *nextNode(TreeLinkNode *root)
    {
        while (root->next)
        {
            if (root->next->left)
                return root->next->left;
            if (root->next->right)
                return root->next->right;
            root = root->next;
        }
        return root->next;
    }

public:
    void connect(TreeLinkNode *root)
    {
        if (!root)
            return ;
        if (root->right)
            root->right->next = nextNode(root);
        if (root->left)
        {
            if (root->right)
                root->left->next = root->right;
            else
                root->left->next = nextNode(root);
        }
        connect(root->right);
        connect(root->left);
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    TreeLinkNode *root = new TreeLinkNode(1);
    root->left = new TreeLinkNode(2), root->right = new TreeLinkNode(3);
    root->left->left = new TreeLinkNode(4), root->left->right = new TreeLinkNode(5), root->right->right = new TreeLinkNode(7);

    //s1.connect(root);
    s2.connect(root);

    cout << root->left->next->val << endl;
    cout << root->left->right->next->val << endl;
    cout << root->left->left->next->val << endl;

    return 0;
}
