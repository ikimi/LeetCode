#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode (int x) : val(x), next(NULL) {}
};

// k个链表 从第0个链表开始，合并(0,1), 可到新的0,然后合并(0，2) 得到新的0,依次类推到第n-1个链表
// 当每个链表的元素都与n成正比时，第一次合并需要2*n次操作， 第二次合并需要3*n次操作...第n-1次合并需要k*n次操作
// 所以算法最终需要(2*n + 3*n + ... + k*n)次合并 即时间复杂度为O(k*k*n)
// 64ms
class Solution1
{
private:
    ListNode *mergeTwoLists(ListNode *first, ListNode *second)
    {
        ListNode *pre, *i, *j, *next;

        pre = first, i = pre->next, j = next = second;
        while (i && j)
        {
            if (i->val <= j->val)
                i = i->next;
            else
            {
                pre->next = j;
                next = j->next;
                j->next = i;
                j = next;
            }
            pre = pre->next;
        }
        if (j)
            pre->next = j;

        return first;
    }

public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        int k = lists.size();
        if (k == 0)
            return NULL;
        if (k == 1)
            return lists[0];

        ListNode *cur, *head = NULL;
        int i = 0;
        while (i < k)      // 没有处理都是空链表的情况 WA了一次
        {
            if (lists[i])
            {
                head = lists[i];
                i++;
                break;
            }
            i++;
        }
        while (i < k)
        {
            while (i < k && !lists[i])
                i++;
            if (i == k)
                break;
            if (head->val > lists[i]->val)
            {
                cur = head;
                head = lists[i];
            }
            else
                cur = lists[i];
            head = mergeTwoLists(head, cur);
            i++;
        }

        return head;
    }
};

// 采用归并排序的思路
// 将k个链表分为两部分，每一部分分别求解
// 这样时间复杂度可表示为：T(k) = 2*T(k/2) + f(n*k)
// 应用master-method可以得出其时间复杂度为O(k*n*log(k))
// 72ms(时间复杂度反而升高了...orz)
class Solution2
{
private:
    ListNode *merge(ListNode *first, ListNode *second)
    {
        ListNode *newhead = new ListNode(0);
        newhead->next = first;
        ListNode *pre, *next;
        pre = newhead, next = second;
        while (first && second)
        {
            if (first->val <= second->val)
                first = first->next;
            else
            {
                pre->next = second;
                next = second->next;
                second->next = first;
                second = next;
            }
            pre = pre->next;
        }
        if(second)
            pre->next = second;

        return newhead->next;
    }

    ListNode *helper(vector<ListNode *> &lists, int low, int high)
    {
        if (low >= high)
            return lists[low];

        int mid = (low + high) / 2;
        return merge(helper(lists, low, mid), helper(lists, mid + 1, high));
    }
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        if (!lists.size())
            return NULL;

        return helper(lists, 0, lists.size() - 1);
    }
};

// 利用最小堆实现
// 建立k大小的最小堆 所需时间为O(k)
// 每次获得堆的最小值O(1)，将堆首元素所在链表的下一个元素入堆，并维护最小堆性质O(log(k))
// 因为k个链表的每一个元素的都要入堆,出堆 共k*n个元素，所以总的时间复杂度O(k*n*log(k))
// 76ms
class Solution3
{
private:
    vector<ListNode *> heap;
    void build_heap(vector<ListNode *> &lists)
    {
        int i, n;

        n = lists.size();
        for (i = 0; i < n; i++)
            if (lists[i])
                heap.push_back(lists[i]);

        n = heap.size();
        for (i = n / 2 - 1; i >= 0; i--)
            helper(i);
    }

    void helper(int index)
    {
        int left, right, n, min;

        min = index, n = heap.size(), left = 2 * index + 1, right = 2 * index + 2;
        if (left < n)
        {
            if (heap[left]->val < heap[min]->val)
                min = left;
        }
        if (right < n)
        {
            if (heap[right]->val < heap[min]->val)
                min = right;
        }
        if (min != index)
        {
            ListNode *temp = heap[index];
            heap[index] = heap[min];
            heap[min] = temp;
            helper(min);
        }
    }

    ListNode *getTop()
    {
        return heap[0];
    }

    bool isEmpty(vector<ListNode *> &heap)
    {
        if (heap.size())
            return false;
        return true;
    }

public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        if (!lists.size())
            return NULL;

        ListNode *head = new ListNode(0);
        ListNode *top, *cur = head;

        build_heap(lists);
        while (!isEmpty(heap))
        {
            top = getTop();
            cur->next = top;
            cur = cur->next;
            if (top->next)
                heap[0] = top->next;
            else
            {
                heap[0] = heap[heap.size() - 1];
                heap.pop_back();
            }
            helper(0);
        }

        return head->next;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;
    vector<ListNode *> lists;

    lists.push_back(NULL);
    lists.push_back(NULL);
/*
    lists.push_back(new ListNode(1));
    lists.push_back(new ListNode(2));
    lists.push_back(new ListNode(3));
    lists[0]->next = new ListNode(3);
    lists[0]->next->next = new ListNode(5);
    lists[1]->next = new ListNode(4);
    lists[1]->next->next = new ListNode(7);
    lists[2]->next = new ListNode(5);
*/
    //ListNode *head = s1.mergeKLists(lists);
    //ListNode *head = s2.mergeKLists(lists);
    ListNode *head = s3.mergeKLists(lists);

    while (head)
    {
        cout << head->val << ' ';
        head = head->next;
    }
    cout << endl;

    return 0;
}
