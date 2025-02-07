#pragma once

#include <iostream>
#include <vector>

namespace Stack {
    class Node {
    private:
        std::string value;
        Node *prev{};
        Node *next{};

        // Зачем нужен static? - Потому что инициализация stack-а происходит внутри inputStack()
        static Node *head;
        static Node *tail;

        static Node *creationStack(int length);

    public:
        Node() = default;

        static void inputStack(int length);

        static void inputStack(const std::string& data);

        static int sizeStack();

        static std::string getTopStack();

        static void printStack();

        static void deleteStack();

        static void appendElement(const std::string& data);

        static void deleteElement();

        ~Node() = default;

    };
}
