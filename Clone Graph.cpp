#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct UndirectedGraphNode
{
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {}
};

// 采用DFS 递归方式实现
// 将有向图想象成K叉树的变种 在DFS中，遍历完节点后，要递归遍历其每一个邻居节点
// 对于某一个节点node,我们使用一个hash map来存储该节点是否遍历过，如果map中没有该Node的创建新的node, 并将其加入到map中
// 然后遍历其所有的字节点，若字节点是其自身，直接返回，否则创建（map中不存在）节点，并建立邻居关系
// 有几点要注意：1）对于成环的情况：0-->1 并且1-->0 所以我们应该判断每一条边是否遍历过
// 例子中每一个节点node的邻居中，可以有相同的邻居，即：0-->1 ,同时0-->1 还可可以
// 所以在标记某一条边是否遍历过的时候，需要在其邻居游遍历过之后标记
// 348ms
class Solution1
{
private:
    map<UndirectedGraphNode *, UndirectedGraphNode *> table;
    map<pair<UndirectedGraphNode *, UndirectedGraphNode *>, int>status;
    void cloneGraphHelper(UndirectedGraphNode *node)
    {
        if (!node)
            return ;

        map<UndirectedGraphNode *, UndirectedGraphNode *> :: iterator it;
        UndirectedGraphNode *fresh;

        if ((it = table.find(node)) == table.end())
        {
            fresh = new UndirectedGraphNode(node->label);
            table.insert(make_pair(node, fresh));
        }
        fresh = table.find(node)->second;

        for (int i = 0; i < node->neighbors.size(); i++)
        {
            map<pair<UndirectedGraphNode *, UndirectedGraphNode *>, int> :: iterator ite;
            pair<UndirectedGraphNode *, UndirectedGraphNode*> tmp = make_pair(node, node->neighbors[i]);

            if ((ite = status.find(tmp)) != status.end())
                continue;

            if (node->neighbors[i] == node)
            {
                fresh->neighbors.push_back(fresh);
                continue;
            }
            else
            {
                UndirectedGraphNode *neighbor;
                if ((it = table.find(node->neighbors[i])) == table.end())
                {
                    neighbor = new UndirectedGraphNode(node->neighbors[i]->label);
                    table.insert(make_pair(node->neighbors[i], neighbor));
                }
                neighbor = table.find(node->neighbors[i])->second;
                fresh->neighbors.push_back(neighbor);
                cloneGraphHelper(node->neighbors[i]);
            }
        }
        for (int i = 0; i < node->neighbors.size(); i++)
        {
            pair<UndirectedGraphNode *, UndirectedGraphNode*> tmp = make_pair(node, node->neighbors[i]);
            status.insert(make_pair(tmp, 1));
        }
    }

public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
    {
        if (!node)
            return NULL;
        cloneGraphHelper(node);

        return table.find(node)->second;
    }
};

// 在上面的解法中 在判断某一条边是是否已经遍历过的时候，需要使用额外的map造成了空间浪费
// 同时额外的遍历一遍 node 的子节点
// 新的方法不用额外的空间，在node邻居的一遍遍历后就能完成
// WA
 class Solution2
{
private:
    map<UndirectedGraphNode *, UndirectedGraphNode *> table;
    void cloneGraphHelper(UndirectedGraphNode *node)
    {
        map<UndirectedGraphNode *, UndirectedGraphNode *> :: iterator it;
        UndirectedGraphNode *fresh;
        if ((it = table.find(node)) == table.end())
        {
            fresh = new UndirectedGraphNode(node->label);
            table.insert(make_pair(node, fresh));
        }
        else
            return ;
        for (int i = 0; i < node->neighbors.size(); i++)
        {
            UndirectedGraphNode *neighbor;
            if ((it = table.find(node->neighbors[i])) == table.end())
            {
                neighbor = new UndirectedGraphNode(node->neighbors[i]->label);
                cloneGraphHelper(node->neighbors[i]);
                table.insert(make_pair(node->neighbors[i], neighbor));
            }
            else
            {
                if (node == node->neighbors[i])
                    neighbor = fresh;
                else
                    neighbor = it->second;
            }
            fresh->neighbors.push_back(neighbor);
        }
    }

public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
    {
        if (!node)
            return NULL;

        cloneGraphHelper(node);

        return table.find(node)->second;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    UndirectedGraphNode *node0 = new UndirectedGraphNode(0);
    UndirectedGraphNode *node1 = new UndirectedGraphNode(0);
    UndirectedGraphNode *node2 = new UndirectedGraphNode(0);

    node0->neighbors.push_back(node0);
    node0->neighbors.push_back(node0);
  //  node0->neighbors.push_back(node2);
 //   node1->neighbors.push_back(node0);
   // node2->neighbors.push_back(node2);

   // UndirectedGraphNode *node = s1.cloneGraph(node0);
    UndirectedGraphNode *node  = s2.cloneGraph(node0);

    cout << node->label << endl;
    for (int i = 0; i < node->neighbors.size(); i++)
        cout << node->neighbors[i]->label << endl;
  //  UndirectedGraphNode *temp = node->neighbors[1];
  //  cout << temp->label << endl;
  //  cout << temp->neighbors[0]->label << endl;

    return 0;
}
