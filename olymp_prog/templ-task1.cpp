#include <iostream>
#include <string>
#include <cstring>
// Шаблон должен работать для любых типов, поддерживающих оператор >.
// Специализация должна быть написана после объявления основного шаблона.
// Напишите простые проверки в main() (или с использованием Google Test), 
// демонстрирующие работу с int, double, std::string и C‑строками.

template<typename T>
const T& max(const T& a, const T& b) {
    // для начала нужна просто универсальная функция
    return (a > b) ? a : b;
}

template<>
const char* const& max<const char*>(const char* const& a, const char* const& b) {
    // это будет специализация для C-строк
    // strcmp: -1, если 1 меньше, 0 если равны и 1 если 1 больше
    return (std::strcmp(a, b) > 0) ? a : b;
}


int main() {
    int a, b;
    a = 14;
    b = 17;
    double n{14.56}, m{14.96};
    std::cout << ::max(a, b) << "\n";
    std::cout << ::max(n, m) << "\n";

    const char* c_line1 = "apple";
    const char* c_line2 = "pineapple";
    std::cout << ::max(c_line1, c_line2) << "\n";

    std::string s1 = "melon";
    std::string s2 = "watermelon";
    std::cout << ::max(s1, s2) << "\n";

    return 0;
}

