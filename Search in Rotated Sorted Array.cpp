#include <iostream>

using namespace std;

class Solution1
{
public:
    int search(int A[], int n, int target)
    {
        int low, mid, high;

        low = 0, high = n - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;

            if (A[mid] == target)
                return mid;
            else if (A[mid] > target)
            {
                if (A[first] > target)
                    first = mid + 1;
                else
                    high = mid - 1;
            }
            else
            {
                if (A[mid] )
            }
        }

        return -1;
    }
};

int main()
{
    return 0;
}
