#pragma once

#include <iostream>
#include <map>

#include "Stack.h"

namespace ReversePolishNotation {
    class Notation {
    private:

        static std::vector<std::string> infixNotation;
        static std::string reversePolishNotation;

        static std::map<std::string, int> dictOperators;

    public:
        Notation() = default;

        static void inputString(std::string data);

        static void infixToRPNotation();

        static void printNotation();

        static void deleteNotation();

        ~Notation() = default;

    };
}
