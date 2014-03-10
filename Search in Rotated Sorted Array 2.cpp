#include <iostream>

using namespace std;

class Solution1
{
public:
    int removeDuplicates(int A[], int n)
    {
        if (n == 0 || n == 1)
            return n;
        int cur, next, count;

        for (cur = next = 0, count = 1; cur < n - 1; cur++)
        {
            if (A[cur + 1] == A[cur])
            {
                count++;
            }
            else
            {
                if (count >= 2)
                {
                    A[next] = A[next + 1] = A[cur];
                    next += 2;
                }
                else
                {
                    A[next] = A[cur];
                    next += 1;
                }
                count = 1;
            }
        }
        if (count >= 2)
        {
            A[next] = A[next + 1] = A[cur];
            next += 2;
        }
        else
            A[next++] = A[cur];

        return next;
    }
};

int main()
{
    // test example
    Solution1 s1;
    int A[] = {1, 1, 2};

    int n = s1.removeDuplicates(A, 3);
    cout << n << endl;

    for (int i = 0; i < n; i++)
        cout << A[i] << ' ';
    cout << endl;

    return 0;
}
