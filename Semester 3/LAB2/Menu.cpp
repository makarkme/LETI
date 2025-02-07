#include "Menu.h"

#include "TimSort.h"

MenuClass::Menu::Menu(long long &array, const int lengthArray) {
    link = &array;
    length = lengthArray;
    menuStatus = 1;
}

// два меню для пунктов 1) и 2) соответственно
void MenuClass::Menu::PrintMenu() {
    if (menuStatus == 0) {
        while (exitFlag) {
            std::cout << "Commands: \n"
                    "-- 0) Exit \n"
                    "-- 1) Input array \n"
                    "-- 2) Generate array \n"
                    "-- 3) Sort array \n"
                    "-- 4) Print array \n";
            std::cin >> condition;

            switch (condition) {
                case 0: {
                    exitFlag = false;
                    break;
                }
                case 1: {
                    std::cout << "Input length: " << "\n";
                    std::cin >> length;
                    std::cout << "Input data: " << "\n";
                    link = ArrayClass::Array::inputArray(length);
                    break;
                }
                case 2: {
                    std::cout << "Input length: " << "\n";
                    std::cin >> length;
                    link = ArrayClass::Array::generateArray(length);
                    break;
                }
                case 3: {
                    TimSortClass::TimSort timSort(*link, length);
                    link = timSort.getSortedArray();
                    break;
                }
                case 4: {
                    ArrayClass::Array::printArray(link, length);
                    break;
                }
                default: {
                    continue;
                }
            }
        }
    }
    if (menuStatus == 1) {
        while (exitFlag) {
            std::cout << "Commands: \n"
                    "-- 0) Exit \n"
                    "-- 1) Sort array \n"
                    "-- 2) Print array \n";
            std::cin >> condition;

            switch (condition) {
                case 0: {
                    exitFlag = false;
                    break;
                }
                case 1: {
                    TimSortClass::TimSort timSort(*link, length);
                    link = timSort.getSortedArray();
                    break;
                }
                case 2: {
                    ArrayClass::Array::printArray(link, length);
                    break;
                }
                default: {
                    continue;
                }
            }
        }
    }
}
