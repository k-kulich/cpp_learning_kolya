#include "Array.h"
#include <iostream>
#include <algorithm> // для std::sort

int main()
{
    try
    {
        // Создание массива из 5 элементов
        Array<int, 5> a1;
        a1.fill(10);
        std::cout << "a1 filled with 10: ";
        for (const auto &x : a1)
        {
            std::cout << x << " ";
        }
        std::cout << std::endl;

        // Создание из initializer_list
        Array<int, 5> a2 = {1, 2, 3, 4, 5};
        std::cout << "a2: ";
        for (const auto &x : a2)
        {
            std::cout << x << " ";
        }
        std::cout << std::endl;

        // Доступ по индексу
        a2[0] = 100;
        std::cout << "a2[0] = " << a2[0] << std::endl;

        // Использование итераторов в алгоритмах STL
        std::sort(a2.begin(), a2.end());
        std::cout << "a2 sorted: ";
        for (const auto &x : a2)
        {
            std::cout << x << " ";
        }
        std::cout << std::endl;

        // Проверка исключений
        try
        {
            int x = a2[10]; // выход за границы
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }

        // Проверка пустого массива (N=0)
        Array<double, 0> empty;
        std::cout << "empty.size() = " << empty.size() << std::endl;
        std::cout << "empty.empty() = " << std::boolalpha << empty.empty() << std::endl;

        // Попытка создать массив с слишком большим initializer_list
        try
        {
            Array<int, 3> bad = {1, 2, 3, 4}; // выбросит исключение
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}