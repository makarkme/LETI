#pragma once

#include <iostream>
#include <string>

#include "Array.h"

namespace MenuClass {
    class Menu {
    private:
        bool exitFlag = true;
        int menuStatus = 0;
        int condition{};

    public:
        long long *link{};
        int length{};

        explicit Menu() = default; // для 2)
        explicit Menu(long long &array, int lengthArray); // для 1)

        void PrintMenu();

        ~Menu() = default;
    };
}
