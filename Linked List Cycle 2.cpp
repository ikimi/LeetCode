#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 用vector容器把环内的数据存起来，当下次从head开始遍历时，遇到的第一个在
// vector中的节点就是环头节点
// 时间复杂度O(n) 空间复杂度O(n)
class Solution1
{
private:
    bool findHead(vector<ListNode*> &vec, ListNode *node)
    {
        for (int i = 0; i < vec.size(); i++)
            if (node == vec[i])
                return true;

        return false;
    }

public:
    ListNode *detectCycle(ListNode *head)
    {
        if (!head || !head->next)
            return NULL;

        ListNode *one, *two;
        one = head, two = head->next;

        while (one && two)
        {
            if (one == two)
                break;
            if (two->next)
                two = two->next->next;
            else
                break;
            one = one->next;
        }
        if (one != two)
            return NULL;

        vector<ListNode*> vec;
        one = one->next;
        vec.push_back(one);
        while (one != two)
        {
            vec.push_back(one);
            one = one->next;
        }

        while (!findHead(vec, head))
            head = head->next;

        return head;
    }
};


// 先求出环的大小l 然后让two指针先移动l位置
// 此时one在head 与 two指针相差环长度个位置
// 同时移动one和two 相遇地点即为环的起始节点(因为one第一次进入环中时 two 刚好到达相同的位置)
// 时间复杂度O(n) 空间复杂度O(1)
class Solution2
{
public:
    ListNode *detectCycle(ListNode *head)
    {
        if (!head)
            return NULL;

        ListNode *slow, *fast;
        slow = head, fast = head->next;

        while (slow && fast)
        {
            if (slow == fast)
                break;
            if (fast->next)
                fast = fast->next->next;
            else
                break;
            slow = slow->next;
        }
        if (slow != fast)
            return NULL;

        int len = 0;
        slow = slow->next, len++;
        while (slow != fast)
        {
            slow = slow->next;
            len++;
        }

        slow = head, fast = head;
        while (len--)
            fast = fast->next;
        while (slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }

        return slow;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = head->next;

   // ListNode *res = s1.detectCycle(head);
    ListNode *res = s2.detectCycle(head);
    if (res)
        cout << res->val << endl;
    else
        cout << "no cycle" << endl;

    return 0;
}
