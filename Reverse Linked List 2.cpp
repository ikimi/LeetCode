#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode (int x) : val(x), next(NULL) {}
};

// 这个是不用利用指针 不交换指针内容的方法
// 只能交换两个元素(开始走弯路了 题目要求的不是这个 先留着吧)
class Solution1
{
public:
    ListNode *reverseBetween(ListNode *head, int m, int n)
    {
        ListNode *first, *second, *i, *j;
        second = head;
        int k;

        for (k = 0; k < n - m; k++)
            second = second->next;

        first = head;
        for (k = 1; k < m - 1; k++)
            first = first->next;

        i = first->next, j = NULL;
        if (second->next)
            j = second->next->next;

        first->next = second->next;
        second->next->next = i->next;
        second->next = i;
        i->next = j;

        return head;
    }
};

// 递归遍历法
// 每一次都要查找与 head 相距某个长度的节点
// 所以时间复杂度是O(n^2)
// 40ms
class Solution2
{
private:
    void helper(ListNode *head, int n)
    {
        if (n == 0 || n < 0)
            return ;

        ListNode *cur;
        int i, temp;

        i = 1, cur = head;
        while (i <= n)
        {
            cur = cur->next;
            i++;
        }

        temp = cur->val;
        cur->val = head->val;
        head->val = temp;

        helper(head->next, n - 2);
    }

public:
    ListNode *reverseBetween(ListNode *head, int m, int n)
    {
        ListNode *cur = head;
        int i = 1;
        while (i < m)
        {
            cur = cur->next;
            i++;
        }

        helper(cur, n - m);
        return head;
    }
};

// 又搞错了。。实现个循环移位。。。
// 利用指针 遍历一遍就可以 也就是 one-pass的
// 利用两个临时变量存储中间结果 也就是 in-place的
class Solution3
{
public:
    ListNode *reverseBetween(ListNode *head, int m, int n)
    {
        ListNode *first, *second, *next;
        int i;

        first = second = head;
        for (i = 0; i < n - m; i++)
            second = second->next;
        for (i = 1; i < m; i++)
        {
            first = first->next;
            second = second->next;
        }

        next = second->next;
        second->next = first;
        int tmp1, tmp2;
        for (i = 0, tmp1 = second->val; i <= n - m; i++)
        {
            tmp2 = second->next->val;
            second->next->val = tmp1;
            tmp1 = tmp2;
            second = second->next;
        }
        second->next = next;

        return head;
    }
};

// 链表逆置法
// 关键就是处理链表的开头何结尾
// 32ms
class Solution4
{
public:
    ListNode *reverseBetween(ListNode *head, int m, int n)
    {
        if (m == n)     // WA了一次
            return head;

        ListNode *i, *j, *k, *next, *cur, *newhead;
        int count, iter;

        ListNode *pre = new ListNode(0);
        newhead = pre;
        pre->next = head;

        for (iter = 1, i = head; iter < m; iter++)
        {
            i = i->next;
            pre = pre->next;
        }
        cur = i;

        if (i->next)
            j = i->next;
        else
            return head;

        count = m;
        while (i)
        {
            if (count >= m && count < n)
            {
                k = j->next;
                j->next = i;
                i = j;
                j = k;
            }
            else
            {
                next = k;
                pre->next = i;
                cur->next = next;
                break;
            }
            count++;
        }

        return newhead->next;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;
    Solution4 s4;

    ListNode *head = new ListNode(1);
    head->next = new ListNode(2), head->next->next = new ListNode(3);
  //  head->next->next->next = new ListNode(4);
   // head->next->next->next->next = new ListNode(5);
   // head->next->next->next->next->next = new ListNode(6);

    //head = s1.reverseBetween(head, 2, 4);
   // head = s2.reverseBetween(head, 2, 5);
  //  head = s3.reverseBetween(head, 2, 5);
    head = s4.reverseBetween(head, 2, 2);

    while (head)
    {
        cout << head->val << ' ';
        head = head->next;
    }
    cout << endl;

    return 0;
}
