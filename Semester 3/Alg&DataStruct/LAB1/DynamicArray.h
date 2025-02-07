#pragma once

#include <iostream>

// Писал реализацию array максимально приближенно к list-у для удобного сравнения array/list компонентов

namespace DynamicArray {
    class Array {
    private:
        static int length;
        static int *head;

        static int *creationArray();

    public:
        Array() = default;

        static void inputArray(int length);

        static void printArray();

        static void deleteArray();

        ~Array() = default;

    };
}
