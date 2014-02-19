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
                return head;

            ListNode *pre, *next;
            pre = next = head;

            while (next)
            {
                if (pre->val == next->val)
                {
                    next = next->next;
                }
                else
                {
                    pre->next = next;
                    pre = next;
                }
            }
            pre->next = next;

            return head;
        }
};

int main()
{
    // test example
    ListNode *root = new ListNode(1);
    root->next = new ListNode(1);
    root->next->next = new ListNode(2);
    //root->next->next->next = new ListNode(3);
    //root->next->next->next->next = new ListNode(3);

    Solution1 s1;
    s1.deleteDuplicates(root);

    while (root)
    {
        cout << root->val << endl;
        root = root->next;
    }

    return 0;
}
