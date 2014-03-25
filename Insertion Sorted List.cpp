#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 标准插入排序
// 244ms
class Solution1
{
public:
    ListNode *insertionSortList(ListNode *head)
    {
        ListNode *p = new ListNode(0);
        p->next = head;

        ListNode *i, *j, *pre, *cur, *next;
        i = head;
        while (i && i->next)
        {
            j = i->next, pre = p, cur = p->next;
            while ((cur != j) && (j->val > cur->val))
            {
                pre = cur;
                cur = cur->next;
            }
            if (cur != j)
            {
                next = j->next;
                pre->next = j;
                j->next = cur;
                i->next = next;
            }
            else
                i = i->next;
        }

        return p->next;
    }
};

int main()
{
    // test example
    Solution1 s1;

    ListNode *head = new ListNode(4);
    head->next = new ListNode(3), head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(1);

    head = s1.insertionSortList(head);
    while (head)
    {
        cout << head->val << ' ';
        head = head->next;
    }
    cout << endl;

    return 0;
}
