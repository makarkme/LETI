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

number ArrayClass::Array::SetElement() {
    number value;
    std::cin >> value;
    return value;
}

void ArrayClass::Array::DecreaseSort() {
    std::sort(data.begin(), data.end(), [](const number& c1, const number& c2) {
        return c1 > c2;
    });
}

void ArrayClass::Array::IncreaseSort() {
    std::sort(data.begin(), data.end(), [](const number& c1, const number& c2) {
        return c1 < c2;
    });
}

void ArrayClass::Array::PrintData() const {
    for (auto &element: data) {
        std::cout << element << " ";
    }
    std::cout << "\n";
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

void ArrayClass::Array::Append(number el){
    data.push_back(el);
}

ArrayClass::Array::~Array() = default;
