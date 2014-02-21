#include <iostream>

using namespace std;

class Solution1
{
    public:
        int removeDuplicates(int A[], int n)
        {
            if (n <= 0)
                return n;

            int next, cur, i;

            for(i = next = cur = 0; i < n; i++)
            {
                if (A[next] == A[cur])
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

    int A[] = {1, 1, 2};
    int B[] = {1, 1, 2, 3, 3, 4, 6, 6, 6};
    cout << s1.removeDuplicates(A, 3) << endl;
    cout << s1.removeDuplicates(B, 9) << endl;
    for(int i = 0; i < 9; i++)
        cout << B[i] << endl;

    return 0;
}
