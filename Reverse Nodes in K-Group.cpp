#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 本题可以看作是 Reverse Linked List 2 的延伸
// 非指针操作 利用交换数组的方法
// 140ms
class Solution1
{
private:
    void helper(ListNode *head, int k)
    {
        if (!k || k == 1)
            return ;
        ListNode *next;

        int i, temp;
        for (i = 1, next = head; i < k; i++)
            next = next->next;
        temp = head->val;
        head->val = next->val;
        next->val = temp;

        helper(head->next, k - 2);
    }

public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *cur, *next;
        int i;
        cur = next = head;

        while (next)
        {
            i = 0;
            while (next && i < k)
            {
                next = next->next;
                i++;
            }
            if (i < k)
                break;
            helper(cur, k);
            cur = next;
        }

        return head;
    }
};

// 交换指针的方法
// 104ms
class Solution2
{
public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *newhead = new ListNode(0);
        newhead->next = head;
        ListNode *pre, *cur, *next, *a, *b, *c;
        pre = newhead, cur = next = head;
        int n, count;

        while (next)
        {
            n = 0;
            while (next && n < k)
            {
                next = next->next;
                n++;
            }
            if (n < k)
                break;
            // 进行逆置操作
            a = cur, b = a->next;
            count = 1;
            while (a)
            {
                if (count < k)
                {
                    c = b->next;
                    b->next = a;
                    a = b;
                    b = c;
                }
                else
                {
                    cur->next = next;
                    break;
                }
                count++;
            }
            pre->next = a;
            pre = cur;
            cur = next;
        }

        return newhead->next;
    }
};

int main()
{
    // test example
    //Solution1 s1;
    Solution2 s2;

    ListNode *root = new ListNode(1);
    root->next = new ListNode(2); //, root->next->next = new ListNode(3);
   // root->next->next->next = new ListNode(4), root->next->next->next->next = new ListNode(5);

   // root = s1.reverseKGroup(root, 2);
    root = s2.reverseKGroup(root, 2);

    while (root)
    {
        cout << root->val << ' ';
        root = root->next;
    }
    cout << endl;

    return 0;
}
