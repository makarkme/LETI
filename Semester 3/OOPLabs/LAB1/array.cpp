#include "array.h"

ArrayClass::Array::Array(long long size) {
    data.resize(size);
    for (auto &element: data) { // заменяет стандартный цикл с итерацией посредством i; element - сразу итерируемый объект, мы работаем с ним, а не с его копией, поэтому там &
        element = ArrayClass::Array::SetElement();
    }
}

double ArrayClass::Array::SetElement() {
    double value;
    std::cin >> value;
    return value;
}

void ArrayClass::Array::Delete() {
    data.clear();
}

void ArrayClass::Array::Resize(long long newSize) {
    data.resize(newSize);
}

void ArrayClass::Array::ChangeElement(double oldElement, double newElement) {
    for (auto &element: data) {
        if (element == oldElement) {
            element = newElement;
            break;
        }
    }
}

void ArrayClass::Array::InputData() {
    for (auto &element: data) {
        element = ArrayClass::Array::SetElement();
    }
}

double ArrayClass::Array::CountAvgDev() {
    double amount = 0;
    for (auto &element: data) {
        amount += element;
    }
    return amount / (double) this->data.size();
}

double ArrayClass::Array::CountAvgSqDev() {
    double s_under_root = 0;
    for (auto &element: data) {
        s_under_root += pow((element - this->avgDev), 2);
    }

    return sqrt(s_under_root * (1.0 / (double) (this->data.size() - 1)));
}

void ArrayClass::Array::DecreaseSort() {
    std::sort(data.begin(), data.end(), decrease); // про decrease я писал massive.h
}

void ArrayClass::Array::IncreaseSort() {
    std::sort(data.begin(), data.end(), increase);
}

void ArrayClass::Array::PrintData() const {
    for (auto &element: data) {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

void ArrayClass::Array::PrintAvgDev() {
    std::cout << CountAvgDev() << "\n";
}

void ArrayClass::Array::PrintAvgSqDev() {
    std::cout << CountAvgSqDev() << "\n";
}

ArrayClass::Array::~Array() = default;
