#pragma once
#include <iostream>
/* Задача 3. Частичная специализация шаблона для указателей

Цель: отработка частичной специализации классов.

Задание:
Напишите шаблон класса IsPointer<T>, который содержит статическую константу value типа bool, равную true,
если T является указателем, и false в противном случае.
Реализуйте это через частичную специализацию для T*.

Дополнительно:
Создайте шаблонную переменную is_pointer_v = IsPointer<T>::value для удобства.

Проверка:
Статически проверьте (через static_assert), что is_pointer_v<int> == false, а is_pointer_v<int*> == true. */

template <typename T>
struct IsPointer
{
    static const bool value = false;
};

template <typename T>
struct IsPointer<T *>
{
    static const bool value = true;
};

template <typename T>
inline constexpr bool is_pointer_v = IsPointer<T>::value;

static_assert(!is_pointer_v<int>, "int не должен быть указателем");
static_assert(is_pointer_v<int *>, "int* должен быть указателем");
