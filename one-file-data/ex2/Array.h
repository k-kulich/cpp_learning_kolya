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
template<typename T, size_t N>
class Array {
    public:
    // зададим стандартные имена
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    Array();
    Array(std::initializer_list<value_type> init);

    size_t size() const;
    bool empty() const;   
    
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;

    void fill(const T& value);

    private:
    // надо хранить сам массив и его размер
    T data_[N];  // создаем массив заданного размера
    size_type size_;
};

