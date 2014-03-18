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
    ListNode *partition(ListNode *head, int x)
    {
        ListNode *small = NULL, *large = NULL, *cur, *i, *j;

        cur = head;
        while (cur)
        {
            if (cur->val >= x)
            {
                if (!large)
                {
                    large = cur;
                    i = cur;
                }
                else
                {
                    i->next = cur;
                    i = i->next;
                }
            }
            else
            {
                if (!small)
                {
                    small = cur;
                    j = cur;
                }
                else
                {
                    j->next = cur;
                    j = j->next;
                }
            }
            cur = cur->next;
        }

        i->next = NULL;
        if (small)
        {
            j->next = large;
            return small;
        }
        return large;
    }
};

int main()
{
    // test example
    Solution1 s1;

    ListNode *root = new ListNode(1);
    root->next = new ListNode(4);
    root->next->next = new ListNode(3);
    root->next->next->next = new ListNode(2);
    root->next->next->next->next = new ListNode(5);
    root->next->next->next->next->next = new ListNode(2);

    root = s1.partition(root, 3);

    while (root)
    {
        cout << root->val << ' ';
        root = root->next;
    }
    cout << endl;

    return 0;
}
