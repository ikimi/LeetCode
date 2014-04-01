#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 基础题 链表模拟
// 时间复杂度O(n) 空间复杂度O(1)
class Solution1
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *newhead = new ListNode(0);
        newhead->next = l1;
        ListNode *pre = newhead;
        int bit = 0;

        while (l1 && l2)
        {
            l1->val += l2->val + bit;
            if (l1->val >= 10)
            {
                l1->val -= 10;
                bit = 1;
            }
            else
                bit = 0;
            l1 = l1->next;
            l2 = l2->next;
            pre = pre->next;
        }
        if (l2)
        {
            l1 = l2;
            pre->next = l1;
        }
        while (l1)
        {
            l1->val += bit;
            if (l1->val >= 10)
            {
                l1->val -= 10;
                bit = 1;
            }
            else
                bit = 0;
            l1 = l1->next;
            pre = pre->next;
        }
        if (bit)
            pre->next = new ListNode(bit);

        return newhead->next;
    }
};

int main()
{
    // test example
    Solution1 s1;
    ListNode *l1 = new ListNode(1);
    l1->next = new ListNode(0);
    l1->next->next = new ListNode(0);
    ListNode *l2 = new ListNode(9);
    l2->next = new ListNode(9);
    l2->next->next = new ListNode(9);
    l2->next->next->next = new ListNode(9);

    l1 = s1.addTwoNumbers(l1, l2);
    while (l1)
    {
        cout << l1->val << ' ';
        l1 = l1->next;
    }
    cout << endl;

    return 0;
}
