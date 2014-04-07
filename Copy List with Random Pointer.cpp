#include <iostream>
#include <map>

using namespace std;

struct RandomListNode
{
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

// 暴力法
// 第一次沿着链表的next指针生成所有节点
// 第二遍遍历针对原链表的每一个元素的random指针 从头查找其指向的指针
// 时间复杂度为O(n^2)
// TLE 超时了
class Solution1
{
public:
    RandomListNode *copyRandomList(RandomListNode *head)
    {
        RandomListNode *x, *y, *newhead;

        x = head, newhead = new RandomListNode(0), y = newhead;
        while (x)
        {
            y->next = new RandomListNode(x->label);
            x = x->next;
            y = y->next;
        }

        x = head, y = newhead->next;
        while (x)
        {
            if (x->random)
            {
                RandomListNode *tmp1 = head, *tmp2 = newhead->next;
                while (tmp1 && (tmp1 != x->random))
                {
                    tmp1 = tmp1->next;
                    tmp2 = tmp2->next;  // 没有在这里指向新链表的元素 而是指向了原来的元素 WA了一次
                }
                y->random = tmp2;
            }
            x = x->next;
            y = y->next;
        }

        return newhead->next;
    }
};

// 利用HASH表
// 在原始链表中 每遍历到一个节点时，若节点在table中，则不创建新的节点 否则创建新的节点，新的链表指向新的节点
// 时间复杂度为O(n) 空间复杂度为O(n)
// 348ms
class Solution2
{
public:
    RandomListNode *copyRandomList(RandomListNode *head)
    {
        map<RandomListNode*, RandomListNode*> table;    // HASH表的类型选错 WA了一次

        RandomListNode *newhead = new RandomListNode(0);
        RandomListNode *cur = newhead;
        while (head)
        {
            map<RandomListNode*, RandomListNode*> :: iterator it = table.find(head);
            if (it == table.end())
            {
                cur->next = new RandomListNode(head->label);
                table[head] = cur->next;
            }
            else
                cur->next = it->second;
            if (head->random)
            {
                it = table.find(head->random);
                if (it == table.end())
                {
                    cur->next->random = new RandomListNode(head->random->label);
                    table[head->random] = cur->next->random;
                }
                else
                    cur->next->random = it->second;
            }
            head = head->next;
            cur = cur->next;
        }

        return newhead->next;
    }
};

// 还是利用map
// 第一遍遍历保存 原始链表的next指针映射关系 并创建新的节点
// 第二遍遍历恢复原始链表的next指针映射
// 时间复杂度O(n) 空间复杂度O(n)
// 328ms
class Solution3
{
public:
    RandomListNode *copyRandomList(RandomListNode *head)
    {
        map<RandomListNode*, RandomListNode*> table;
        RandomListNode *newhead = new RandomListNode(0), *tmp1, *tmp2;

        tmp1 = head, tmp2 = newhead;
        while (tmp1)
        {
            table[tmp1] = tmp1->next;
            tmp2->next = new RandomListNode(tmp1->label);
            tmp2->next->random = tmp1;
            tmp1->next = tmp2->next;
            tmp1 = table[tmp1];
            tmp2 = tmp2->next;
        }

        tmp1 = head, tmp2 = newhead->next;
        while (tmp1)
        {
            map<RandomListNode*, RandomListNode*> :: iterator it;
            if (tmp2->random->random)
                tmp2->random = tmp2->random->random->next;
            else
                tmp2->random = NULL;
            it = table.find(tmp1);
            tmp1 = it->second;
            tmp2 = tmp2->next;
        }

        tmp1 = head;
        while (tmp1)
        {
            map<RandomListNode*, RandomListNode*> :: iterator it;
            it = table.find(tmp1);
            tmp1->next = it->second;
            tmp1 = tmp1->next;
        }

        return newhead->next;
    }
};

// 以上两种方法都是要用到 空间复杂度为O(n) 的hash表 下面的方法仅仅需要O(1)的空间复杂度
// 分三次遍历 设原始的链表为A->B->C->D 那么，第一次遍历后链表变为A->A'->B->B'->C->C'->D->D'
// 第二次遍历确定A' B‘ C’ D'的random指针指向
// 第三次遍历则恢复新旧链表的next指针指向
// 280ms
class Solution4
{
public:
    RandomListNode *copyRandomList(RandomListNode *head)
    {
        RandomListNode *newhead, *cur, *next, *tmp;

        cur = head;
        while (cur)
        {
            next = cur->next;
            cur->next = new RandomListNode(cur->label);
            cur->next->next = next;
            cur = next;
        }

        cur = head;
        while (cur)
        {
            next = cur->next;
            if (cur->random)
                next->random = cur->random->next;
            cur = next->next;
        }

        cur = head;
        newhead = new RandomListNode(0), tmp = newhead;

        while (cur)
        {
            next = cur->next;
            cur->next = next->next;
            cur = cur->next;
            tmp->next = next;
            tmp = tmp->next;
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

    RandomListNode *head = new RandomListNode(1);
    head->next = new RandomListNode(2);
    head->next->next = new RandomListNode(3);
    head->next->next->next = new RandomListNode(4);
    head->random = head->next->next;
    head->next->random = head;

    //RandomListNode *newhead = s1.copyRandomList(head);
   // RandomListNode *newhead = s2.copyRandomList(head);
    //RandomListNode *newhead = s3.copyRandomList(head);
    RandomListNode *newhead = s4.copyRandomList(head);

    while (newhead)
    {
        cout << newhead->label << ' ';
        if (newhead->random)
            cout << newhead->random->label;
        cout << endl;
        newhead = newhead->next;
    }

    return 0;
}
