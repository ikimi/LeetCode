#include <iostream>
#include <map>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 使用 map 容器 程序简单 但是空间复杂度为O(n)
// 原理：若单链表存在环则比存在一个节点的入度为2
class Solution1
{
    public:
        bool hasCycle(ListNode *head)
        {
            map<ListNode *, int> Lists;

            while (head)
            {
                if (Lists.count(head))
                    return true;
                else
                    Lists.insert(make_pair(head, 1));
                head = head->next;
            }

            return false;
        }
};

// 快慢指针 空间复杂度为O（1） 时间复杂度为O(n)
// 设快指针每次向前移动两个节点 慢指针每次向前移动一个节点 这样：若链表中存在环 则快指针一定会在某一时刻赶上慢指针
//（因为快指针每次追赶慢指针一个单位长度， 所以当慢指针进入环时，快指针距慢指针的节点个数就是迭代次数）
// 同时处理好两种特殊情况：1.链表为空 2.根节点head自己形成环
class Solution2
{
    public:
    bool hasCycle(ListNode *head)
    {
        if (!head)
            return false;
        if (head->next == head)
            return true;

        ListNode *fast, *slow;
        fast = slow = head;

        while (fast)
        {
            fast = fast->next;
            if (!fast)
                return false;
            slow = slow->next;
            if (!slow)
                return false;

            fast = fast->next;
            if (fast == slow)
                return true;
        }
        return false;
    }
};

int main()
{
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
   // head->next->next = new ListNode(3);
    //head->next->next->next = new ListNode(4);
  //  head->next->next->next = head->next;
    head->next->next = head;
    Solution1 s1;
    Solution2 s2;
    if (s2.hasCycle(head))
        cout << "True" << endl;
    else
        cout << "False" << endl;


    return 0;
}
