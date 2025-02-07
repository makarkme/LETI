#pragma once

#include <iostream>

namespace DoubleLinkedList {
    class Node {
    private:
        int value;
        Node *prev;
        Node *next;

        // ����� ����� static? - ������ ��� ������������� list-� ���������� ������ inputList()
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
