#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>
#include "vector"
#include "number.h"

namespace ArrayClass {
    class Array {
    private:
        std::vector<number> data;
        double avgDev = NULL;
        double avgSqDev = NULL;

        static double SetElement();

        double CountAvgDev();

        double CountAvgSqDev();

    public:
        Array() = default;

        [[maybe_unused]] explicit Array(
                long long number); // [[maybe_unused]] - значение дословное (просто чтоб компилятор не ругался)
        ~Array();

        void Delete();

        void Resize(long long newSize);

        void ChangeElement(double oldElement, double newElement);

        void InputData();

        void PrintData() const;

        void PrintAvgDev();

        void PrintAvgSqDev();

        void DecreaseSort();

        void IncreaseSort();
    };
}

static bool decrease(number firstNumber,
                     number secondNumber) { // эта хрень нужна для того, чтобы векторный sort() корректно работал
    // суть в том, что sort() не умеет работать с кастомными типами данных,
    // а эта функция помогает ему понять, как что надо сравнить
    return firstNumber > secondNumber;
}

static bool increase(number firstNumber,
                     number secondNumber) { // эта хрень нужна для того, чтобы векторный sort() корректно работал
    // суть в том, что sort() не умеет работать с кастомными типами данных,
    // а эта функция помогает ему понять, как что надо сравнить
    return firstNumber < secondNumber;
}