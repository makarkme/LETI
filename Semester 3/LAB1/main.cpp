#include <iostream>
#include "DoubleLinkedList.h"
#include "DynamicArray.h"
#include "Stack.h"
#include "ReversePolishNotation.h"

int main() {
    int lenghtList;
    int lenghtArray;
    int lenghtStack;
    std::string directNotation;

    int condition;
    while (true) {
        std::cout << "Commands: \n"
                     "-- 0) Exit \n"
                     "-- 1) Create linked-list \n"
                     "-- 2) Create dynamic-array \n"
                     "-- 3) Create stack \n"
                     "-- 4) Reverse-Polish notation \n";

        std::cin >> condition;
        switch (condition) {
            case 0:
                DoubleLinkedList::Node::deleteList();
                DynamicArray::Array::deleteArray();
                Stack::Node::deleteStack();
                ReversePolishNotation::Notation::deleteNotation();
                exit(0);
            case 1:
                std::cout << "Input lenght: " << "\n";
                std::cin >> lenghtList;
                std::cout << "Input values separated by spaces: " << "\n";
                DoubleLinkedList::Node::inputList(lenghtList);
                DoubleLinkedList::Node::printList();
                break;
            case 2:
                std::cout << "Input lenght: " << "\n";
                std::cin >> lenghtArray;
                std::cout << "Input values separated by spaces: " << "\n";
                DynamicArray::Array::inputArray(lenghtArray);
                DynamicArray::Array::printArray();
                break;
            case 3:
                std::cout << "Input lenght: " << "\n";
                std::cin >> lenghtStack;
                std::cout << "Input values separated by spaces: " << "\n";
                Stack::Node::inputStack(lenghtStack);
                Stack::Node::printStack();
                break;
            case 4:
                // Example input:
                // 12 + 5 * (123 - 34 * 23 - 12) + 12 / 34 * 4 - (234 - 213 * 34 ^ 12) * c (123 - 1)
                std::cout << "Input infix notation: " << "\n";
                std::cin.ignore();
                getline(std::cin, directNotation);
                ReversePolishNotation::Notation::inputString(directNotation);
                ReversePolishNotation::Notation::printNotation();
                break;
            default:
                continue;
        }
    }
}