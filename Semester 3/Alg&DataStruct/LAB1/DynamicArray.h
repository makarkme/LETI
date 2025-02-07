#pragma once

#include <iostream>

// ����� ���������� array ����������� ����������� � list-� ��� �������� ��������� array/list �����������

namespace DynamicArray {
    class Array {
    private:
        static int length;
        static int *head;

        static int *creationArray();

    public:
        Array() = default;

        static void inputArray(int length);

        static void printArray();

        static void deleteArray();

        ~Array() = default;

    };
}
