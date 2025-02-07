#include "array.h"

using namespace ArrayClass;

ArrayClass::Array::Array(long long size) {
    data.resize(size);
    for (auto &element: data) { // заменяет стандартный цикл с итерацией посредством i; element - сразу итерируемый объект, мы работаем с ним, а не с его копией, поэтому там &
        element = ArrayClass::Array::SetElement();
    }
}

/*double ArrayClass::Array::SetElement() {
    double value;
    std::cin >> value;
    return value;
}
*/

void ArrayClass::Array::Delete() {
    data.clear();
}

void ArrayClass::Array::Resize(long long newSize) {
    data.resize(newSize);
}

/*void ArrayClass::Array::ChangeElement(double oldElement, double newElement) {
    for (auto &element: data) {
        if (element == oldElement) {
            element = newElement;
            break;
        }
    }
}
*/

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

/*
double ArrayClass::Array::CountAvgDev() {
    double amount = 0;
    for (auto &element: data) {
        amount += element;
    }
    return amount / (double) this->data.size();
}
*/
number ArrayClass::Array::CountAvgComplex() {
    number sum = {0, 0};
    for (auto &element: data) {
        sum = sum + element;
    }
    return {sum.getRe() / this->data.size(), sum.getIm() / this->data.size()};
}

/*Complex ArrayClass::Array::CountAvgSqComplex() {
    Complex avg = CountAvgComplex();
    Complex s_under_root = { 0,0 };
    for (auto& element : data) {
        s_under_root = s_under_root + (element - avg) * (element - avg);
    }
    return Complex::sqrt(Complex(s_under_root.re / (this->data.size() - 1), s_under_root.im / (this->data.size()-1)));
}
*/

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

/*
double ArrayClass::Array::CountAvgSqDev() {
    double s_under_root = 0;
    for (auto &element: data) {
        s_under_root += pow((element - this->avgDev), 2);
    }

    return sqrt(s_under_root * (1.0 / (double) (this->data.size() - 1)));
}
*/
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


ArrayClass::Array::~Array() = default;
