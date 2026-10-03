#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> x{n};
    std::vector<int> h{n};
    for (int i = 0; i < n; ++i)
    {
        std::cin >> x[i];
    }
    for (int i = 0; i < n; ++i)
    {
        std::cin >> h[i];
    }
    int l = 0;
    int r = n - 1;
    int r_imp = x[r], l_imp = 0;
    while (l != n - 1)
    {
        if (l == 0)
        {
            l_imp += h[l] + x[l];
            ++l;
            r_imp -= h[r];
            --r;
        }
        else
        {
            l_imp += h[l];
            ++l;
            r_imp -= h[r];
            --r;
        }
    }

    return 0;
}