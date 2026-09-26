#include <iostream>

int main() {
    int n, k;
    std::cin >> n >> k;
    // проблема: в int 10^10 не влезет!
    uint64_t m = 9 * std::pow(10, n - k - 1);  // число уник начал
    uint64_t result = std::pow(10, k) * (m - 1) * m / 2;  // ответ
    std::cout << result << '\n';
    return 0;
}
