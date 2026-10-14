cmake_minimum_required(VERSION 3.12)
project(ArrayProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем папку с заголовками
include_directories(lib)

# Исполняемый файл для демонстрации
add_executable(array_demo bin/main.cpp)