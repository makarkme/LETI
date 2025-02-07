#pragma once

#include "DynamicArray.h"

using namespace DynamicArray;

int Array::length = 0;
int *Array::head = nullptr;

int *Array::creationArray() {
    int *array = new int[length];
    return array;
}

void Array::inputArray(int lengthArray) {
    length = lengthArray;
    head = creationArray();
    for (int i = 0; i < length; ++i) {
        std::cin >> head[i];
    }
}

void Array::printArray() {
    for (int i = 0; i < length; ++i) {
        std::cout << head[i] << " ";
    }
    std::cout << "\n";
}

void Array::deleteArray() {
    delete[] head;
}
