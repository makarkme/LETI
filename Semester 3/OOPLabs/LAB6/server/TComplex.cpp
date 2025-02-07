#include "TComplex.h"

using namespace ComplexClass;

Complex::~Complex() = default;

Complex::Complex(const int &r) {
    re = r;
    im = 0;
}

Complex::Complex(double r, double m) {
    re = r;
    im = m;
}

QString Complex::toQString() const{
    QString qRe = QString::number(re);
    QString qIm = QString::number(im);
    if (im != 0 && re != 0)
        return (QString("(") + qRe + QString(" + ") + qIm + QString("i)"));
    else if (re != 0)
        return qRe;
    else if (im != 0)
        return (qIm + "i");
    else
        return QString::number(0);
}

Complex Complex::operator*(const Complex &c) const {
    Complex t{};
    t.re = re * c.re - im * c.im;
    t.im = re * c.im - im * c.re;
    return t;
}

Complex Complex::operator+(const Complex &c) const {
    Complex t{};
    t.re = re + c.re;
    t.im = im + c.im;
    return t;
}

Complex Complex::operator-() const {
    Complex t{};
    t.re = -re;
    t.im = -im;
    return t;
}

Complex Complex::operator-(const Complex &c) const {
    Complex t{};
    t.re = re - c.re;
    t.im = im - c.im;
    return t;
}

bool Complex::operator==(const Complex &c) const {
    return ((re == c.re) && (im == c.im));
}

bool Complex::operator>(const Complex &c) const {
    if (std::sqrt(re * re + im + im) > std::sqrt(c.re * c.re + c.im * c.im))
        return true;
    else if (std::sqrt(re * re + im + im) == std::sqrt(c.re * c.re + c.im * c.im)) {
        if (std::atan2(im, re) > std::atan2(c.im, c.re)) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool Complex::operator<(const Complex &c) const {
    if (std::sqrt(re * re + im + im) < std::sqrt(c.re * c.re + c.im * c.im))
        return true;
    else if (std::sqrt(re * re + im + im) == std::sqrt(c.re * c.re + c.im * c.im)) {
        if (std::atan2(im, re) < std::atan2(c.im, c.re)) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

Complex Complex::operator/(int a) const {
    Complex t{};
    t.re = re / a;
    t.im = im / a;
    return t;
}

Complex Complex::sqrt(const Complex &c) {
    Complex t{};
    t.re = std::sqrt((std::sqrt(c.re * c.re + c.im * c.im) + c.re) / 2);
    t.im = std::sqrt((std::sqrt(c.re * c.re + c.im * c.im) - c.re) / 2);
    return t;
}

double Complex::getRe() const {
    return re;
}

double Complex::getIm() const {
    return im;
}

void Complex::setRe(double r) {
    re = r;
}

void Complex::setIm(double i) {
    im = i;
}
