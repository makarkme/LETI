#pragma once

#include "Stack.h"

using namespace Stack;

Node *Node::head = nullptr;
Node *Node::tail = nullptr;

Node *Node::creationStack(int length) {
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

// Почему инициализация stack-а здесь, а не в main.cpp? - Можно и там, просто я захотел ограничить пользовательские возможности,
// чтоб было только взаимодействие, без создания и последующего использования
void Node::inputStack(int length) {
    head = creationStack(length); // head - по-умолчанию указатель на начало списка
    Node *curr = head; // curr - указатель на текущее положение "курсора" списка
    for (int i = 0; i < length; ++i) {
        std::cin >> curr->value;
        tail = curr; // Нужно где-то получить указатель на tail. Чтоб лишний раз не делать новых функций, сделал это здесь
        curr = curr->next;
    }
}

// Использую перегрузку функции inputStack(), чтобы можно было заполнять массив и через length + std::cin и через string
void Node::inputStack(const std::string &data) {
    head = creationStack(int(data.size()));
    Node *curr = head;
    for (char element: data) { // тоже самое что и "for (int i = 0; i < data.size(); ++i)"
        curr->value = element;
        tail = curr;
        curr = curr->next;
    }
}

int Node::sizeStack() {
    int length = 0;
    Node *curr = head;
    while (curr) {
        length += 1;
        curr = curr->next;
    }
    return length;
}

void Node::printStack() {
    Node *curr = tail;
    int length = sizeStack();
    for (int i = 0; i < length; ++i) {
        std::cout << curr->value << " ";
        curr = curr->prev;
    }
    std::cout << "\n";
}

void Node::deleteStack() {
    Node *afterHead;
    while (head) {
        afterHead = head->next;
        delete head;
        head = afterHead;
    }
}

void Node::appendElement(const std::string &data) {
    if (head != nullptr) { // Важная проверка, т.к. head заполняется в inputStack (костыль)
        Node *curr = tail;
        curr->next = new Node;
        Node *temp = curr;
        curr = curr->next;
        curr->prev = temp;
        curr->next = nullptr;
        curr->value = data;
        tail = curr;
    } else {
        inputStack(data);
    }
}

void Node::deleteElement() {
    if (sizeStack() >= 2) { // Важная проверка, т.к. при удалении 1 эл-та важно ссылаться на предыдущий
        Node *curr = tail;
        Node *temp = curr->prev;
        temp->next = nullptr;
        curr->prev = nullptr;
        delete curr;
        tail = temp;
    } else {
        deleteStack(); // Собственно, если предыдущего нет
    }
}

std::string Node::getTopStack() {
    return tail->value;
}
