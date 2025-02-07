#include "Array.h"

long long *ArrayClass::Array::inputArray(const int lengthArray) {
    long long *array = new long long[lengthArray];
    for (int i = 0; i < lengthArray; ++i) {
        std::cin >> array[i];
    }
    return array;
}


long long *ArrayClass::Array::generateArray(const int lengthArray) {
    std::random_device rd; // Используется для получения случайного начального значения
    std::mt19937 gen(rd()); // Создание генератора mt19937 с начальными значениями от random_device
    std::uniform_int_distribution<> distrib(0, 9999); // Определение диапазона

    long long *array = new long long[lengthArray];
    for (int i = 0; i < lengthArray; ++i) {
        array[i] = distrib(gen); // Генерация случайного числа
    }
    return array;
}

void ArrayClass::Array::printArray(const long long *array, const int lengthArray) {
    for (int i = 0; i < lengthArray; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}
