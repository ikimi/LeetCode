#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 暴力法 两遍遍历 第一遍遍历计算链表的长度 第二遍遍历删除倒数第N的节点
class Solution1
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        if (!head)
            return NULL;

        ListNode *temp = head;
        int i, num = 0;
        while (temp)
        {
           num++;
           temp = temp->next;
        }

        if (n == num)
        {
            head = head->next;
            return head;
        }
        for (i = 1, temp = head; i < num - n; i++)
            temp = temp->next;
        temp->next = temp->next->next;

        return head;
    }
};

// 利用一个vector 存储每个节点的指针
// 遍历一遍 但是空间复杂度为O(n)
class Solution2
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        if (!head)
            return NULL;

        ListNode *temp = head;
        vector<ListNode *> arr;
        int num = 0;

        while (temp)
        {
            num++;
            arr.push_back(temp);
            temp = temp->next;
        }
        if (num == n)
        {
            head = head->next;
            return head;
        }
        arr[num - n - 1]->next = arr[num - n]->next;

        return head;
    }
};

// 采用双指针 first 指针向前移动n个位置 此时second指针才开始移动
// 当first移动到结尾时 second指向 倒数第N个节点的前驱
// 直接操作即可
class Solution3
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        if (!head)
            return NULL;
        ListNode *first, *second;
        first = second = head;

        while (second->next && n--)
        {
            second = second->next;
        }

        if (n > 0)
        {
            head = head->next;
            return head;
        }
        while (second->next)
        {
            first = first->next;
            second = second->next;
        }
        first->next = first->next->next;

        return head;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    ListNode *root = new ListNode(1);
    root->next = new ListNode(2), root->next->next = new ListNode(3);
    root->next->next->next = new ListNode(4), root->next->next->next->next = new ListNode(5);

   // root = s1.removeNthFromEnd(root, 5);
    //root = s2.removeNthFromEnd(root, 1);
    root = s3.removeNthFromEnd(root, 3);

    while (root)
    {
        cout << root->val << ' ';
        root = root->next;
    }
    cout << endl;

    return 0;
}
