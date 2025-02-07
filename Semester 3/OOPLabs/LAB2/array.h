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

        static number SetElement(); //новый метод для Complex чисел

        // double CountAvgDev();

        // double CountAvgSqDev();

        number CountAvgComplex(); // новый метод для Complex чисел

        number CountAvgSqComplex(); // Новый метод для Complex чисел

    public:
        Array() = default;

        [[maybe_unused]] explicit Array(
                long long number); // [[maybe_unused]] - значение дословное (просто чтоб компилятор не ругался)
        ~Array();

        void Delete();

        void Resize(long long newSize);

        void ChangeElement(const number& oldElement, const number& newElement);

        void InputData();

        void PrintData() const;

        void PrintAvgDev();

        void PrintAvgSqDev();

        void DecreaseSort();

        void IncreaseSort();
    };
}