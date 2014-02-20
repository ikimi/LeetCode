#include <iostream>

using namespace std;

class Solution1
{
    public:
        int removeElement(int A[], int n, int elem)
        {
            int cur, next;

            cur = 0, next = -1;
            while(cur < n)
            {
                if (A[cur] == elem)
                    cur++;
                else
                    A[++next] = A[cur++];
            }

            return ++next;
        }
};

int main()
{
    // test example
    Solution1 s1;
    int i, len;
   // int A[7] = {1, 2, 2, 4, 5, 2, 6};
    int A[1] = {1};

    len = s1.removeElement(A, 1, 2);
    for(i = 0; i < len; i++)
        cout << A[i] << endl;

    return 0;
}
