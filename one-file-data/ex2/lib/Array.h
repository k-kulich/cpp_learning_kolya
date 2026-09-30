#pragma once
#include <iostream>
#include <initializer_list>
/*
Реализовать шаблон класса Array<T, size_t N>, который:
- Хранит массив из N элементов типа T непосредственно в объекте (без выделения
динамической памяти).
- Предоставляет стандартные методы: конструктор по умолчанию, конструктор от
initializer_list, size(), empty(), operator[], fill().

- Предоставляет итераторы: iterator, const_iterator, методы begin(), end(),
cbegin(), cend().

- Конструктор от initializer_list должен обладать strong guarantee: если переданных
элементов больше N, он должен выбрасывать исключение и не создавать объект в
невалидном состоянии. !! потом разберем

+ Нужна работа с потоками ввода и вывода!
*/
template <typename T, size_t N>
class Array
{
public:
    // зададим стандартные имена
    using value_type = T;
    using size_type = std::size_t;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using iterator = T *;
    using const_iterator = const T *;

    Array();
    Array(std::initializer_list<value_type> init);

    size_t size() const;
    bool empty() const;

    reference operator[](size_type index);
    const_reference operator[](size_type index) const;

    void fill(const T &value);

    iterator begin() noexcept { return data_; }
    iterator end() noexcept { return data_ + N; }
    const_iterator cbegin() const noexcept { return data_; }
    const_iterator cend() const noexcept { return data_ + N; }

private:
    // надо хранить сам массив и его размер
    T data_[N]; // создаем массив заданного размера
    size_type size_;
};

template <typename T, size_t N>
Array<T, N>::Array() : size_(N)
{
    // надо заполнить массив
    for (int i = 0; i < size_; ++i)
    {
        data_[i] = T(); // задаем в пустое значение для данного типа
    }
}

template <typename T, size_t N>
Array<T, N>::Array(std::initializer_list<value_type> init) : size_(N)
{
    // для начала проверим, что размер данных не превышает N
    if (init.size() > size_)
    {
        // выкинем ошибку, потому что так проще по логике
        throw std::out_of_range("Array::Array: initializer list size exceeds capacity");
    }

    // во всех остальных случаях init может быть и меньше, чем надо
    // поэтому мы заполним все, что влезает, а остальное - пустыми значениями типа T
    size_type i = 0;
    for (const value_type &val : init)
    {
        data_[++i] = val; // копируем значения
    }
    // теперь дозаполним, пока i < size_
    for (; i < size_; ++i)
    {
        data_[i] = T();
    }
}

template <typename T, size_t N>
Array<T, N>::size_type Array<T, N>::size() const
{
    return size_;
}

template <typename T, size_t N>
bool Array<T, N>::empty() const
{
    return size_ == 0;
}

template <typename T, size_t N>
Array<T, N>::reference Array<T, N>::operator[](size_type index)
{
    // нам надо проверить, что такой индекс вообще существует
    if (index > size_ || index < 0)
    {
        throw std::out_of_range("Array::operator[] is out of range");
    }
    return data_[index];
}

template <typename T, size_t N>
Array<T, N>::const_reference Array<T, N>::operator[](size_type index) const
{
    if (index > size_ || index < 0)
    {
        throw std::out_of_range("Array::operator[] is out of range");
    }
    return data_[index];
}

template <typename T, size_t N>
void Array<T, N>::fill(const T &value)
{
    // заполнить все 1 значением
    for (size_type i = 0; i < size_; ++i)
    {
        data_[i] = value;
    }
}
