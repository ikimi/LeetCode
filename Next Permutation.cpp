#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 利用排序
// 84ms
class Solution1
{
public:
    void nextPermutation(vector<int> &num)
    {
        int end, min, i, temp;

        end = num.size() - 1;
        while ((end - 1 >= 0) && (num[end] <= num[end - 1]))
            end--;
        if (end)
        {
            min = end, i = end;
            while (i < num.size())
            {
                if (num[i] > num[end - 1] && num[min] > num[i])
                    min = i;
                i++;
            }
            temp = num[end - 1];
            num[end - 1] = num[min];
            num[min] = temp;
            sort(num.begin() + end, num.end());
        }
        else
            sort(num.begin(), num.end());
    }
};

// 不利用排序
// 56ms
class Solution2
{
private:
    void reverse(vector<int> &num, int low, int high)
    {
        int temp;

        while (low < high)
        {
            temp = num[low];
            num[low] = num[high];
            num[high] = temp;
            low++, high--;
        }
    }

public:
    void nextPermutation(vector<int> &num)
    {
        int end, i, temp;

        end = num.size() - 1;
        while ((end - 1 >= 0) && (num[end] <= num[end - 1]))
            end--;
        i = num.size() - 1;
        if (end)
        {
            while (num[i] <= num[end - 1])
                i--;
            temp = num[end - 1];
            num[end - 1] = num[i];
            num[i] = temp;
            reverse(num, end, num.size() - 1);
        }
        else
            reverse(num, 0, num.size() - 1);
    }
};

int main()
{
    // test example
    Solution1 s1;
    Solution2 s2;

    vector<int> res;
    res.push_back(1), res.push_back(3), res.push_back(2);
    //s1.nextPermutation(res);
    s2.nextPermutation(res);

    for (int i = 0; i < res.size(); i++)
        cout << res[i] << endl;

    return 0;
}
