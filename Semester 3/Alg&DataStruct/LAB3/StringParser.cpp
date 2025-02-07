#include "StringParser.h"


std::vector<std::string> StringParserClass::StringParser::vectorInputData(const std::string &inputData) {
    std::string inputString = inputData;
    std::vector<std::string> inputVector;

    inputString += " ";
    std::string localString;

    int countLeftBrackets = 0;
    int countRightBrackets = 0;
    for (int i = 0; i < inputString.size(); ++i) {
        if (inputString[i] == '(') {
            countLeftBrackets += 1;
        }
        if (inputString[i] == ')') {
            countRightBrackets += 1;
        }

        if (inputString[i] == '(' or inputString[i] == ')') {
            localString += inputString[i];
            inputVector.push_back(localString);
            localString.clear();
        }

        if (inputString[i] != '(' and inputString[i] != ')' and inputString[i] != ' ') {
            localString += inputString[i];
            if (inputString[i + 1] == '(' or inputString[i + 1] == ')' or inputString[i + 1] == ' ') {
                inputVector.push_back(localString);
                localString.clear();
            }
        }
    }
    if (countLeftBrackets != countRightBrackets) {
        std::cout << "[ERROR]: input.error()" << "\n";
        return {};
    }

    return inputVector;
}
