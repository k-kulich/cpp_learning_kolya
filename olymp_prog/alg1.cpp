#include <iostream>
#include <cstdint>

typedef unsigned long long ull;

int main()
{

    long long n;
    std::cin >> n;
    uint64_t const abs_n = std::abs(n);
    for (ull i = 0; i < 1000000; ++i)
    {
        ull i3 = i * i * i;
        if (i3 == abs_n)
        {
            if (n < 0)
            {
                std::cout << '-' << i << '\n';
            }
            else
            {
                std::cout << i << '\n';
            }
            break;
        }
        if (i3 > abs_n)
        {
            if (n < 0)
            {
                std::cout << '-' << i << " -" << i - 1 << '\n';
            }
            else
            {
                std::cout << i - 1 << ' ' << i << '\n';
            }
            break;
        }
    }
    return 0;
}
