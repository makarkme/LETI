#pragma once

#include "ReversePolishNotation.h"

using namespace ReversePolishNotation;

std::vector<std::string> Notation::infixNotation;
std::string Notation::reversePolishNotation;
std::map<std::string, int> Notation::dictOperators = {{"+", 1},
                                                      {"-", 1},
                                                      {"*", 2},
                                                      {"/", 2},
                                                      {"^", 3},
                                                      {"s", 3}, // sin
                                                      {"c", 3}}; // cos

// Отделяем пробелы из строки, infixNotation заполняется в формате: ["(", "1", "+", "2", ")"]
void Notation::inputString(std::string data) {
    data += " ";
    std::string localString;
    for (char element: data) {
        if (element != ' ' and element != '(' and element != ')') {
            localString.push_back(element);
        }
        else if (element == '(') {
            localString.push_back(element);
            infixNotation.push_back(localString);
            localString.clear();
        }
        else if (element == ')') {
            infixNotation.push_back(localString);
            localString.clear();
            localString.push_back(element);
            infixNotation.push_back(localString);
            localString.clear();
        } else if (!localString.empty()) {
            infixNotation.push_back(localString);
            localString.clear();
        }
    }
}

void Notation::infixToRPNotation() {
    for (const std::string &token: infixNotation) {
        // Если число, добавляем в строку
        if (isdigit(token[0])) {
            reversePolishNotation += token + " ";
        }
            // Если оператор или скобки
        else if (dictOperators.find(token) != dictOperators.end()) { // Проверяем, оператор ли.
            // Выталкиваем операторы из стека, пока они имеют более высокий или равный приоритеты
            while (Stack::Node::sizeStack() != 0 && Stack::Node::getTopStack() != "(" &&
                   dictOperators.at(Stack::Node::getTopStack()) >= dictOperators.at(token)) {
                reversePolishNotation += Stack::Node::getTopStack() + " ";
                Stack::Node::deleteElement();
            }
            Stack::Node::appendElement(token); // Добавляем оператор в стек
        }
            // Если открывающая скобка
        else if (token == "(") {
            Stack::Node::appendElement(token);
        }
            // Если закрывающая скобка
        else if (token == ")") {
            // Выталкиваем операторы из стека до открытия скобки
            while (Stack::Node::sizeStack() != 0 && Stack::Node::getTopStack() != "(") {
                reversePolishNotation += Stack::Node::getTopStack() + " ";
                Stack::Node::deleteElement();
            }
            // Удаляем открывающую скобку из стека
            if (Stack::Node::sizeStack() != 0 && Stack::Node::getTopStack() == "(") {
                Stack::Node::deleteElement();
            }
        }
    }

    // Высталкиваем оставшиеся операторы из стека
    while (Stack::Node::sizeStack() != 0) {
        reversePolishNotation += Stack::Node::getTopStack() + " ";
        Stack::Node::deleteElement();
    }
}

void Notation::printNotation() {
    infixToRPNotation();
    std::cout << reversePolishNotation << "\n";
    deleteNotation();
}

void Notation::deleteNotation() {
    Stack::Node::deleteStack();
    infixNotation.clear(); // Важно сделать, чтоб можно было работать с программой повторно, не перезапуская её
    reversePolishNotation.clear();
}
