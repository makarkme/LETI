#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n;
    cin >> n;

    int* list = new int[n];
    for (int i = 0; i < n; i++) { // ��������� ������
        cin >> list[i];
    }

    for (int i = 0; i < n / 2; i++) { // ������ �������� ���� ������ ���������.
        int data = list[i]; // ����������� ����������, ���� �������� �� ����������.
        list[i] = list[n - 1 -
                       i]; // �������� �������� �� �������� � ���������� �������� � ������� (n - 1 ������������, ��� ��������� � ������� � 0, � ����� - ���)
        list[n - 1 - i] = data;
    }
    cout << "����������� ������ � ������� �� �����: ";
    for (int i = 0; i < n; i++) {
        cout << list[i] << " "; // �����
    }

    cout << endl;

    int k;
    cin >> k;

    for (int i = 0; i < k; i++) { // ���������� �� k - ������� ��� ����� "������������" ������ �����
        int data = list[0]; // ��� ��� � ��� ���� � �����, �� ������ ����� ���� � ������� 0 ����� �� �����, ������� ��� ����� ��������
        for (int j = 1; j < n; j++) { // �������� � j = 1, �.�. j = 0 - ��� ��� data
            list[j - 1] = list[j]; // ����������� ����������� ������� (�������� �������� "�������������")
        }
        list[n - 1] = data; // ����������� � ����� ������� ��������, ������� "��������������"
    }

    cout << "������� �� ����� ��������� ������� ������� ����� �� k ���������: ";
    for (int i = 0; i < n; i++) {
        cout << list[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < k; i++) { //(�� �������� � ���������� ����)
        int data = list[n - 1]; // ���������� ��������� ��������
        for (int j = n - 1 - 1;
             j >= 0; j--) { // ��� ��������� �� ������� �� ����� �������, � ��������. ��� ����� �������� �� ����������.
            list[j + 1] = list[j];
        }
        list[0] = data;
    }

    cout << "������� �� ����� ��������� ������� ������� ������ �� k ���������: ";
    for (int i = 0; i < n; i++) {
        cout << list[i] << " ";
    }

    cout << endl;

    int index_max_number, index_min_number, max_number = 0, min_number = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (max_number < list[i]) {
            max_number = list[i]; // ���������� �����, ������� ��������, ���������� ��� ������
            index_max_number = i;
        }
        if (min_number > list[i]) {
            min_number = list[i]; // ����������
            index_min_number = i;
        }
    }

    cout << "������� ������� ������������� � ������������ ��������� �������: " << index_max_number << " "
         << index_min_number << endl;

    for (int i = 0; i <
                    n; i++) { // (������� ������������ ������� � ������� - ������ ��� � ������.
        // ������������� ������, �� ��� ��� ������� ��������, ����� ������� ��������� � ������ ��� ����� ������� ���������.
        // ���, ���� �� �������������.
        int index_number = 0, number = 0;
        for (int j = i; j < n; j++) {
            if (number < list[j]) {
                number = list[j];
                index_number = j;
            }
        }
        int data = list[i];
        list[i] = list[index_number];
        list[index_number] = data;
    }

    cout << "������� ��������������� ������ � ������� ��������: ";
    for (int i = 0; i < n; i++) {
        cout << list[i] << " ";
    }

    delete [] list;
}