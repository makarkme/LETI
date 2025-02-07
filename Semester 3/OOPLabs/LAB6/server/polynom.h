#pragma once

#include "array.h"
#include <cmath>
#include <iostream>

enum PrintMode {
    PrintModeClassic = 1,
    PrintModeCanonic = 2,
};

template <class number>
class Polynom {
	PrintMode printMode;
private:
    ArrayClass::Array<number> data;
public:
	explicit Polynom() = default;
    void setPrintMode(PrintMode m) {
        printMode = m;}
    void printPolynom() const{
        ArrayClass::Array<number> arr = data;
        short int length = arr.getLength();
        std::cout << "P(x) = ";
        if (printMode == 2) { //canonic
            for (int i = 0; i < length; i++) {
                if (i == length - 2) {
                    std::cout << arr.getElement(i) << "x ";
                    std::cout << "+ ";
                }
                else if (i != length - 1) {
                    std::cout << arr.getElement(i) << "x^" << length - 1 - i << " ";
                    std::cout << "+ ";
                }
                else {
                    std::cout << arr.getElement(i);
                }
            }
        }
        else if (printMode == 1) { // classic
            std::cout << "P(x) = " << arr.getElement(0) << "(";
            for (int i = 1; i < length; i++) {
                if (i != length - 1) {
                    std::cout << "x - " << arr.getElement(i) << ")(";
                }
                else {
                    std::cout << "x - " << arr.getElement(i) << ")";
                }
            }
        }
        std::cout << std::endl;
        }
    void createPolynom(ArrayClass::Array<number> arr){
        data = arr;}
    ArrayClass::Array<number> getData(){
        return data;
    }
    number countValue(number value){
        int length = data.getLength();
        number temp;
        number result;
        if (printMode == 2) {
            result = data.getElement(length - 1);
            for (int i = 0; i < length - 1; ++i) {
                temp = value;
                int j = length - 2 - i;
                while (j > 0) {
                    temp = temp * value;
                    j--;
                }
                result = result + data.getElement(i)*temp;
            }
        }
        else if (printMode == 1) {
            result = data.getElement(0);
            for (int i = 1; i < length; ++i) {
                temp = value - data.getElement(i);
                result = result * temp;
            }
        }
        else exit(0);
        return result;
    }
    ~Polynom() = default;
};
