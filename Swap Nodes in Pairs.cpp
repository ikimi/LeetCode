#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 递归法
class Solution1
{
private:
    ListNode *swapPair(ListNode *head)
    {
        if (!head || !head->next)
            return head;

        ListNode *first, *second, *temp;

        first = head, second = first->next;
        temp = swapPair(second->next);
        first->next = temp;
        second->next = first;

        return second;
    }

public:
    ListNode *swapPairs(ListNode *head)
    {
        return swapPair(head);
    }
};

int main()
{
    // test example
    Solution1 s1;

    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);

    head = s1.swapPairs(head);
    while(head)
    {
        cout << head->val << endl;
        head = head->next;
    }

    return 0;
}
