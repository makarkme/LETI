#pragma once

#include <iostream>
#include <cmath>
#include <QString>

namespace ComplexClass {
    class Complex {
    private:
        double im; // вещественная и мнимая части
        double re;
    public:

        explicit Complex() = default;
        explicit Complex(const int &r); // constructor для не комплексных чисел
        Complex(double r, double m); // constructor
        QString toQString() const;
        Complex operator*(const Complex &) const; // перегрузка оператора умножения
        Complex operator+(const Complex &) const; // перегрузка оператора сложения
        Complex operator-() const; // перегрузка оператора унарного минуса
        Complex operator-(const Complex &) const; // перегрузка оператора вычитания
        bool operator==(const Complex &) const; // перегрузка оператора равенства
        bool operator>(const Complex &) const; // перегрузка оператора больше
        bool operator<(const Complex &) const; // перегрузка оператора меньше
        Complex operator/(int) const; // перегрузка оператора деления на double
        static Complex sqrt(const Complex &c); // метод взятия квадратного корня из комплексного числа

        double getRe() const; // метод для использования private атрибута
        double getIm() const; // метод для использования private атрибута
        void setRe(double r);
        void setIm(double i);
        ~Complex(); // desctructor
    };
}

inline std::ostream& operator<<(std::ostream& os, const ComplexClass::Complex& c) { // перегрузка оператора ввода
    os << "(" << c.getRe() << "+" << c.getIm() << "i)";
    return os;
}

inline std::istream& operator>>(std::istream& is, ComplexClass::Complex& c) { // перегрузка оператора вывода
    double r, i;
    is >> r >> i;
    c.setRe(r);
    c.setIm(i);
    return is;
}
