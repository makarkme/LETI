#pragma once

#include <iostream>

namespace DoubleLinkedList {
    class Node {
    private:
        int value;
        Node *prev;
        Node *next;

        // Зачем нужен static? - Потому что инициализация list-а происходит внутри inputList()
        static Node *head;

        static Node *creationList(int length);

        static int sizeList();

    public:
        Node() = default;

        static void inputList(int length);

        static void printList();

        static void deleteList();

        ~Node() = default;

    };
}
