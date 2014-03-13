#include <iostream>

using namespace std;

// 时间复杂度O(n)
// 52ms
class Solution1
{
public:
    bool canJump(int A[], int n)
    {
        if (n <= 0)
            return false;

        if (n == 1)
            return true;

        int i, pos;
        bool flag;

        i = n - 2;
        while (i >= 0)
        {
            flag = true;
            while ((i >= 0) && A[i])
                i--;
            if (i < 0)
                return flag;
            pos = i, flag = false;
            while ((i >= 0) && (A[i] <= (pos - i)))
                   i--;
        }

        return flag;
    }
};

// 别人的DP思路： O(n)
// 20ms
class Solution2
{
public:
    bool canJump(int A[], int n)
    {
        if (n <= 1)
            return true;

        int i, maxPath;

        maxPath = A[0];
        if (!maxPath)
            return false;

        for (i = 1; i < n - 1; i++)
        {
           if (maxPath > i)
           {
               if (i + A[i] > maxPath)
                maxPath = i + A[i];
           }
           else if (maxPath == i)
           {
               if (!A[i])
                  return false;
               maxPath = i + A[i];
           }
           else
            return false;
        }

        return true;
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    int A[] = {2, 3, 1, 1, 4};
    int B[] = {3, 2, 1, 0, 4};
    int C[] = {2, 0, 0};
    int D[] = {5, 4, 0, 0, 0, 0, 0};

    cout << s1.canJump(A, 5) << endl;
    cout << s1.canJump(B, 5) << endl;
    cout << s1.canJump(C, 3) << endl;
    cout << s1.canJump(D, 7) << endl;
    cout << "-------------------" << endl;
    cout << s2.canJump(A, 5) << endl;
    cout << s2.canJump(B, 5) << endl;
    cout << s2.canJump(C, 3) << endl;
    cout << s2.canJump(D, 7) << endl;

    return 0;
}
