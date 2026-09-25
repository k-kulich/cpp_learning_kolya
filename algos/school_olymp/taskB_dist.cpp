#include <iostream>

int main() {
    // надо считать все гирьки - 4 штуки
    int weights[4];
    for (int i = 0; i < 4; ++i) {
        std::cin >> weights[i];
    }
    // можем ручками отсортировать спокойно
    // хоть пузырьком
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (weights[i] > weights[j]) {
                std::swap(weights[i], weights[j]);
            }
        }
    }
    // быстро отсортировали пузырьком

    // на одну чашу - сразу самое тяжелое
    // а дальше на уменьшение: смотрим, какая сумма перевешивает
    int first{1};  // хранение гирек:   0000
    int second{1};
    int sum1{0};  // для удобного сравнения
    int sum2{0};

    for (int i = 3; i >= 0; --i) {
        if (sum1 <= sum2) {
            first += (1 << i);  // запоминаем, что гирьку положили на первые весы
            sum1 += weights[i];
        } else {
            second += (1 << i);  // запоминаем, что гирьку положили на вторые весы
            sum2 += weights[i];
        }
    }
    if (sum1 != sum2) std::cout << -1 << "\n";
    else {
        for (int s = 0; s < 4; ++s) {
            if (first & (1 << s) != 0) {
                std::cout << weights[s];
            }
        }
        for (int s = 0; s < 4; ++s) {
            if (second & (1 << s) != 0) {
                std::cout << weights[s];
            }
        }
    }


    return 0;
}
