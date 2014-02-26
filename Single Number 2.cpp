#include <iostream>
#include <map>

using namespace std;

// 用 map 时间复杂度为O(n) 空间复杂度为O(n)
// map<num times> times用来存储num出现的次数
class Solution1
{
public:
    int singleNumber(int A[], int n)
    {
        map<int, int> list;
        map<int, int>::iterator iter;
        int i;

        for (i = 0; i < n; i++)
        {
            iter = list.find(A[i]);
            if (iter == list.end())
                list.insert(pair<int, int>(A[i], 1));
            else
                (*iter).second++;
        }
        for (iter = list.begin(); iter != list.end(); iter++)
            if ((*iter).second == 1)
                return (*iter).first;

        return 0;
    }
};

int main()
{
    // test example
    Solution1 s1;

    int A[] = {1, 2, 2, 4, 2, 1, 1};
    cout << s1.singleNumber(A, 7) << endl;

    return 0;
}
