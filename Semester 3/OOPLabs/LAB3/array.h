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
        static number SetElement();
        number CountAvgComplex(); 
        number CountAvgSqComplex();
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
        std::vector<number> getData();
        number getElement(int i);
        int getLength();
    };
}