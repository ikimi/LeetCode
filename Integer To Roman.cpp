#include <iostream>
#include <string>

using namespace std;

// ŽÓ1000,500£¬£¬£¬µœ1 ²»¶Ï±éÀú
// ŽúÂëœÏ³€
class Solution1
{
public:
    string intToRoman(int num)
    {
        string str;
        while (num >= 1000)
        {
            str += 'M';
            num -= 1000;
        }
        if (num >= 900)
        {
            str += "CM";
            num -= 900;
        }
        if (num >= 500)
        {
            str += 'D';
            num -= 500;
        }
        if (num >= 400)
        {
            str += "CD";
            num -= 400;
        }
        while (num >= 100)
        {
            str += 'C';
            num -= 100;
        }
        if (num >= 90)
        {
            str += "XC";
            num -= 90;
        }
        if (num >= 50)
        {
            str += 'L';
            num -= 50;
        }
        if (num >= 40)
        {
            str += "XL";
            num -= 40;
        }
        while (num >= 10)
        {
            str += 'X';
            num -= 10;
        }
        if (num >= 9)
        {
            str += "IX";
            num -= 9;
        }
        if (num >= 5)
        {
            str += 'V';
            num -= 5;
        }
        if (num >= 4)
        {
            str += "IV";
            num -= 4;
        }
        while (num > 0)
        {
            str += 'I';
            num--;
        }

        return str;
    }
};

// ŽúÂë±ÈœÏÕûœà
class Solution2
{
public:
    string intToRoman(int num)
    {
        string res;

        string symbol[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        int value[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

        int i = 0;
        while (num != 0)
        {
            if (num >= value[i])
            {
                res += symbol[i];
                num -= value[i];
            }
            else
                i++;
        }

        return res;
    }
};

int main()
{
    // test example
    Solution1 s1;
    int num;

    while (1)
    {
        cin >> num;
        cout << s1.intToRoman(num) << endl;
    }
    return 0;
}
