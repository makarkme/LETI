#pragma once

#include <iostream>
#include <string>
#include <random>

#include "Menu.h"

namespace ArrayClass {
    class Array {
    public:
        explicit Array() = default;

        static long long *inputArray(int lengthArray);

        static long long *generateArray(int lengthArray);

        static void printArray(const long long *array, int lengthArray);

        ~Array() = default;
    };
}
