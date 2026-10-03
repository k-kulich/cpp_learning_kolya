#include <iostream>
#include <vector>

int main()
{
    std::cout << "Ввод данных:\n";
    // ввод всех данных
    int n;
    std::cin >> n;
    std::vector<int> x(n);
    std::vector<int> h(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> x[i];
    }
    for (int i = 0; i < n; ++i)
    {
        std::cin >> h[i];
    }
    // теперь обходы - переделаем, лучше пойдем раздельно
    // пожалуй будем прямо смотреть на то, как падают доминошки
    // так как это проще и понятнее, а работать должно точно
    // будем хранить на каждой позиции логическое значение: упала ли доминошка
    std::vector<bool> fell_right(n, false);
    std::vector<bool> fell_left(n, false);
    
    // обход справа (Гарри)
    fell_right[0] = true;  // устанавливаем, что первая упала, а дальше по координатам
    int max_reach = x[0] + h[0];  // устанавливаем максимальное расстояние, до куда достаем
    for (int i = 1; i < n; ++i) {
        if (x[i] <= max_reach) {  // если дотягиваемся, то роняем доминошку
            fell_right[i] = true;
            max_reach = std::max(max_reach, x[i] + h[i]);
        } else {
            break;  // не дотянулись - падение завершилось
        }
    }

    // обход слева (Гермиона)
    fell_left[n - 1] = true;  // так как идем с конца теперь
    int min_reach = x[n - 1] - h[n - 1];  // по условию теперь такое расстояние падения
    for (int i = n - 2; i >= 0; --i) {
        if (x[i] >= min_reach) {
            fell_left[i] = true;
            min_reach = std::min(min_reach, x[i] - h[i]);  // новое расстояние
        } else {
            break;  // падение окончилось
        }
    }

    // остается только посчитать по обоим спискам, сколько всего упало доминошек
    int total_count = 0;
    for (int i = 0; i < n; ++i) {
        if (fell_left[i] || fell_right[i]) {
            total_count += 1;
        }
    }
    std::cout << "Вывод:\n";
    std::cout << total_count << "\n";

    return 0;
}