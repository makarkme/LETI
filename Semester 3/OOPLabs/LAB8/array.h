#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>
#include "vector"

namespace ArrayClass {
    template <class number>
    class Array {
    private:
        std::vector<number> data;
        double avgDev;
        double avgSqDev;
    public:
        Array(){ }

        void Delete() {
            data.clear();
        }

        void setElement(int index, number value) {
            data[index] = value;
        }

        void Resize(long long newSize) {
            data.resize(newSize);
        }

        void ChangeElement(const number &oldElement, const number &newElement) {
            for (auto &element: data) {
                if (element == oldElement) {
                    element = newElement;
                    break;
                }
            }
        }

        void DecreaseSort() {
            std::sort(data.begin(), data.end(), [](const number& c1, const number& c2) {
                return c1 > c2;
            });
        }

        void IncreaseSort() {
            std::sort(data.begin(), data.end(), [](const number& c1, const number& c2) {
                return c1 < c2;
            });
        }

        void PrintData() const {
            for (auto &element: data) {
                std::cout << element << " ";
            }
            std::cout << "\n";
        }

        std::vector<number> getData() {
            return data;
        }

        number getElement(int i) {
            return data[i];
        }

        int getLength() {

            return data.size();
        }

        void Append(number el){
            data.push_back(el);
        }

        ~Array() = default;
    };
}
