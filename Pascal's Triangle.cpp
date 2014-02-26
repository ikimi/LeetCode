#include <iostream>
#include <vector>

using namespace std;

class Solution1
{
public:
    vector<vector<int> > generate(int numRows)
    {
        int i, j;
        vector<vector<int> > data;
        vector<int> line;

        if (numRows < 1)
            return data;
        if (numRows == 1)
        {
            line.push_back(1);
            data.push_back(line);

            return data;
        }

        line.push_back(1);
        data.push_back(line);
        line.push_back(1);
        data.push_back(line);

        for (i = 3; i <= numRows; i++)
        {
            line.clear();
            line.push_back(1);
            for (j = 1; j < i - 1; j++)
                line.push_back(data[i - 2][j - 1] + data[i - 2][j]);
            line.push_back(1);
            data.push_back(line);
        }

        return data;
    }
};

int main()
{
    //test example
    Solution1 s1;
    vector<vector<int> > data;

    data = s1.generate(5);
    cout << data[0][0] << endl;
    cout << data[1][1] << endl;
    cout << data[4][2] << endl;

    return 0;
}
