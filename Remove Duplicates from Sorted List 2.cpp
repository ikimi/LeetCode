#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution1
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (!head)
            return NULL;
        ListNode *p = new ListNode(0);
        p->next = head;

        ListNode *pre, *cur, *next;
        pre = p, cur = head, next = head->next;

        while (cur && cur->next)
        {
            if (cur->val == next->val)
            {
                cur = next;
                next = next->next;
            }
            else
            {
                if (cur == pre->next)
                {
                    pre = cur;
                    cur = next;
                    next = next->next;
                }
                else
                {
                    cur = next;
                    next = next->next;
                    pre->next = cur;
                }
            }
        }

        if ((pre->next->val == cur->val) && (pre->next != cur))
            pre->next = NULL;

        return p->next;
    }
};

int main()
{
    // test example
    Solution1 s1;
    ListNode *root = new ListNode(1);
    root->next = new ListNode(1), root->next->next = new ListNode(1);
    root->next->next->next = new ListNode(2);
    root->next->next->next->next = new ListNode(3);
    root->next->next->next->next->next = new ListNode(4);
    root->next->next->next->next->next->next = new ListNode(5);
    root->next->next->next->next->next->next->next = new ListNode(5);

    root = s1.deleteDuplicates(root);
    while (root)
    {
        cout << root->val << ' ';
        root = root->next;
    }
    cout << endl;

    return 0;
}
