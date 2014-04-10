#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 理解错误 题目的意思是从后往前的第k个调转 而不是从前往后
// 下面是从前往后的代码
// WA
class Solution1
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        int i = 0;
        ListNode *low, *high;

        low = high = head;
        while (high && i < k)
        {
            high = high->next;
            i++;
        }
        if (!high || !high->next)
            return low;

        ListNode *newhead, *temp;
        newhead = temp = high->next;

        while (temp->next)
            temp = temp->next;
        temp->next = head;
        high->next = NULL;

        return newhead;
    }
};

// 从后往前调转 其实还是那个思路用 left 和 right指针
// right指针比left指针多向前移动k个位置 注意处理边界情况
// 时间复杂度O(m)
// 题目不难 但是比较坑,难怪这么简单的题AC率只有21.6%...
// 82ms
class Solution2
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        if (!head)  // 当head为NULL时需要判断WA了一次
            return NULL;

        int i = 0;
        ListNode *left, *right;

        left = right = head;
        while (i < k)
        {
            right = right->next;
            if (!right)         // 当k大于链表的长度时要循环遍历而不是直接返回 WA了一次
                right = left;
            i++;
        }
        if (left == right)
            return left;
        while (right->next)
        {
            right = right->next;
            left = left->next;
        }
        right->next = head;
        ListNode *newhead = left->next;
        left->next = NULL;

        return newhead;
    }
};

// 56ms
class Solution3
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        if (!head)
            return NULL;

        int i, len;

        i = len = 0;
        ListNode *left, *right;

        left = right = head;
        while (right)   // 第一遍求得len 可加速循环
        {
            len++;
            right = right->next;
        }

        k %= len;
        right = head;
        while (i < k)
        {
            right = right->next;
            i++;
        }

        while (right->next)
        {
            left = left->next;
            right = right->next;
        }

        right->next = head;
        ListNode *newhead = left->next;
        left->next = NULL;

        return newhead;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    //ListNode *newhead = s1.rotateRight(head, 0);
    //ListNode *newhead = s2.rotateRight(head, 6);
    ListNode *newhead = s3.rotateRight(head, 7);

    while (newhead)
    {
        cout << newhead->val << ' ';
        newhead = newhead->next;
    }
    cout << endl;

    return 0;
}
