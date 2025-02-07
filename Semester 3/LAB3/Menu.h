#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "StringParser.h"
#include "BaseTree.h"
#include "RBTree.h"


namespace MenuClass {
    class Menu {
    private:
        bool exitSwitchFirst = true;
        bool exitSwitchSecond = true;
        int menuStatus = 0;
        int conditionFirst{};
        int conditionSecond{};

        std::string inputString{};
        std::vector<std::string> vectorInputData{};
        BaseTreeClass::Node *rootBaseTree = nullptr;
        RBTreeClass::Node *rootRBTree = nullptr;

    public:
        explicit Menu() = default; // для 1)
        explicit Menu(const std::string &inputData); // для 2)

        void PrintMenu();

        ~Menu() = default;
    };
}
