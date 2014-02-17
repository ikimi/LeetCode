#include <iostream>

using namespace std;

class Solution
{
    public :
        int singleNumber(int A[], int n)
        {
            int i, res = 0;

            for (i = 0; i < n; i++)
                res ^= A[i];
            return res;
        }
};

int main()
{
    int A[5] = {2, 5, 1, 5, 2};
    Solution s;
    cout << s.singleNumber(A, 5) << endl;
    return 0;
}
