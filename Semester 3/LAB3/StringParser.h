#pragma once

#include <iostream>
#include <string>
#include <vector>


namespace StringParserClass {
    class StringParser {
    private:

    public:
        explicit StringParser() = default;

        std::vector<std::string> vectorInputData(const std::string &inputData);

        ~StringParser() = default;
    };
}
