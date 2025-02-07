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
        double avgDev;
        double avgSqDev;
        static number SetElement();
    public:
        Array() = default;
        explicit Array(long long number);
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
        void Append(number el);
        std::vector<number> getData();
        number getElement(int i);
        int getLength();

    };
}
