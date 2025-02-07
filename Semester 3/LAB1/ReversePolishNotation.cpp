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

// �������� ������� �� ������, infixNotation ����������� � �������: ["(", "1", "+", "2", ")"]
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
        // ���� �����, ��������� � ������
        if (isdigit(token[0])) {
            reversePolishNotation += token + " ";
        }
            // ���� �������� ��� ������
        else if (dictOperators.find(token) != dictOperators.end()) { // ���������, �������� ��.
            // ����������� ��������� �� �����, ���� ��� ����� ����� ������� ��� ������ ����������
            while (Stack::Node::sizeStack() != 0 && Stack::Node::getTopStack() != "(" &&
                   dictOperators.at(Stack::Node::getTopStack()) >= dictOperators.at(token)) {
                reversePolishNotation += Stack::Node::getTopStack() + " ";
                Stack::Node::deleteElement();
            }
            Stack::Node::appendElement(token); // ��������� �������� � ����
        }
            // ���� ����������� ������
        else if (token == "(") {
            Stack::Node::appendElement(token);
        }
            // ���� ����������� ������
        else if (token == ")") {
            // ����������� ��������� �� ����� �� �������� ������
            while (Stack::Node::sizeStack() != 0 && Stack::Node::getTopStack() != "(") {
                reversePolishNotation += Stack::Node::getTopStack() + " ";
                Stack::Node::deleteElement();
            }
            // ������� ����������� ������ �� �����
            if (Stack::Node::sizeStack() != 0 && Stack::Node::getTopStack() == "(") {
                Stack::Node::deleteElement();
            }
        }
    }

    // ������������ ���������� ��������� �� �����
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
    infixNotation.clear(); // ����� �������, ���� ����� ���� �������� � ���������� ��������, �� ������������ �
    reversePolishNotation.clear();
}
