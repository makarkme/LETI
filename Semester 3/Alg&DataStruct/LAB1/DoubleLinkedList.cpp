#pragma once

#include "DoubleLinkedList.h"

using namespace DoubleLinkedList;

Node *Node::head = nullptr;

Node *Node::creationList(int length) {
    Node *curr = nullptr, *afterCurr = nullptr;
    for (int i = 0; i < length; ++i) {
        curr = new Node;
        curr->next = afterCurr;
        if (afterCurr != nullptr) {
            afterCurr->prev = curr;
        }
        afterCurr = curr;
    }
    curr->prev = nullptr;
    return curr;
}

// Почему инициализация list-а здесь, а не в main.cpp? - Можно и там, просто я захотел ограничить пользовательские возможности,
// чтоб было только взаимодействие, без создания и последующего использования
void Node::inputList(int length) {
    head = creationList(length); // head - по-умолчанию указатель на начало списка
    Node *curr = head; // curr - указатель на текущее положение "курсора" списка
    for (int i = 0; i < length; ++i) {
        std::cin >> curr->value;
        curr = curr->next;
    }
}

int Node::sizeList() {
    int length = 0;
    Node *curr = head;
    while (curr) {
        length += 1;
        curr = curr->next;
    }
    return length;
}

void Node::printList() {
    Node *curr = head;
    int length = sizeList();
    for (int i = 0; i < length; ++i) {
        std::cout << curr->value << " ";
        curr = curr->next;
    }
    std::cout << "\n";
}

void Node::deleteList() {
    Node *afterHead;
    while (head) {
        afterHead = head->next;
        delete head;
        head = afterHead;
    }
}
