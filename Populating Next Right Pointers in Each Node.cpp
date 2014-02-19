#include <iostream>
#include <queue>

using namespace std;

struct TreeLinkNode
{
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

// 利用队列
// 思路清晰 但是需要O （n）的辅助空间
class Solution1
{
    public:
    void connect(TreeLinkNode *root)
    {
        if (!root)
            return;

        int i, j;
        TreeLinkNode *temp;
        queue <TreeLinkNode*> que;

        que.push(root);

        i = 1;
        while (!que.empty())
        {
            for (j = 1; j < i; j++)
            {
                temp = que.front();
                que.pop();
                temp->next = que.front();
                if (temp->left)
                    que.push(temp->left);
                if (temp->right)
                    que.push(temp->right);
            }
            temp = que.front();
            que.pop();
            temp->next = NULL;
            if (temp->left)
                que.push(temp->left);
            if (temp->right)
                que.push(temp->right);
            i *= 2;
        }
    }
};

// 采用递归方法 ， 辅助空间为O(1)
// 思想：其实设置next的难点在于对不同根节点的字节点之间的连接
// 我们注意到：不同根节点的字节点相互连接时 -- 当且仅当 在某一层上 其中一个是左子树的最右字节点 另一个时右子树的最左字节点
class Solution2
{
    public:
    void connect(TreeLinkNode *root)
    {
        if (!root)
            return ;
        if (root->left)
        {
            TreeLinkNode *l, *r;

            l = root->left, r = root->right;
            while (l)
            {
                l->next = r;
                r = r->left;
                l = l->right;
            }
            connect(root->left);
            connect(root->right);
        }
    }
};

int main()
{
    //TreeLinkNode *root = new TreeLinkNode(0);
    // test example
    return 0;
}
