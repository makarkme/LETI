#include "array.h"

using namespace ArrayClass;

ArrayClass::Array::Array(long long size) {
    data.resize(size);
    for (auto &element: data) { 
        element = ArrayClass::Array::SetElement();
    }
}

void ArrayClass::Array::Delete() {
    data.clear();
}

void ArrayClass::Array::Resize(long long newSize) {
    data.resize(newSize);
}

void ArrayClass::Array::ChangeElement(const number &oldElement, const number &newElement) {
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

number ArrayClass::Array::CountAvgComplex() {
    number sum = {0, 0};
    for (auto &element: data) {
        sum = sum + element;
    }
    return {sum.getRe() / this->data.size(), sum.getIm() / this->data.size()};
}

number ArrayClass::Array::CountAvgSqComplex() {
    number avg = CountAvgComplex();
    number sum = {0, 0};
    double re_sum = 0.0;
    double im_sum = 0.0;
    for (const number& element: data) {
        number deviation = element - avg;
        re_sum += deviation.getRe() * deviation.getRe();
        im_sum += deviation.getIm() * deviation.getIm();
    }
    double re_sko = std::sqrt(re_sum / (data.size() - 1));
    double im_sko = std::sqrt(im_sum / (data.size() - 1));
    return {re_sko, im_sko};
}

number ArrayClass::Array::SetElement() {
    number value;
    std::cin >> value;
    return value;
}

void ArrayClass::Array::DecreaseSort() {
    std::sort(data.begin(), data.end(), [](const Complex& c1, const Complex& c2) {
        return c1 > c2;
    });
}

void ArrayClass::Array::IncreaseSort() {
    std::sort(data.begin(), data.end(), [](const Complex& c1, const Complex& c2) {
        return c1 < c2;
    });
}

void ArrayClass::Array::PrintData() const {
    for (auto &element: data) {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

void ArrayClass::Array::PrintAvgDev() {
    std::cout << CountAvgComplex() << "\n";
}

void ArrayClass::Array::PrintAvgSqDev() {
    std::cout << CountAvgSqComplex() << "\n";
}

std::vector<number> ArrayClass::Array::getData() {
    return data;
}

number ArrayClass::Array::getElement(int i) {
    return data[i];
}

int ArrayClass::Array::getLength() {
    return data.size();
}

ArrayClass::Array::~Array() = default;
