#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned long long ull;

ull count_valid(ull n)
{
    if (n <= 0)
        return 0;

    string s = to_string(n);
    int L = s.length();
    ull count = 0;

    vector<ull> p10(20, 1);
    for (int i = 1; i < 20; ++i)
    {
        p10[i] = p10[i - 1] * 10;
    }

    for (int l = 1; l < L; ++l)
    {
        if (l == 1)
        {
            count += 9;
        }
        else
        {
            count += 9 * p10[l - 2];
        }
    }

    if (L == 1)
    {
        count += n;
    }
    else
    {
        int first = s[0] - '0';
        int last = s[L - 1] - '0';

        count += (first - 1) * p10[L - 2];

        string mid = s.substr(1, L - 2);
        ull candidate = stoull(to_string(first) + mid + to_string(first));

        if (candidate <= n)
        {
            count += 1;
        }
    }

    return count;
}

int main()
{
    ull n = 100;
    cout << count_valid(n) << endl;
    return 0;
}