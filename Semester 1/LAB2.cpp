#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "������� ������������������ ����� �����: " << endl;

    int input_data = 0, check = 1, max_number = 0, min_number = 2147483647, count_multiple = 0,
    count_degree = 0, count_succession = 0, previous_number_1 = 0, previous_number_2 = 0;
    float amount = 0, count = 0;
    bool test_for_powers_of_two;

    while (check != 0) { // (� check ����� ������������ ��� ��������, ��� � � input_data.) ������� ������ �� �����.

        if (input_data != 0) { // (��������� ���������� � ������)

            amount += input_data; // ����� ���� ������������������.
            count++; // ���������� ��-�� ������������������.

            if (input_data > max_number) {  // ������� ������������ �����.
                max_number = input_data;
            }

            if (input_data < min_number) {  // ������� ����������� �����.
                min_number = input_data;
            }

            if ((input_data > 0) and (input_data % 5 == 0)) { // ������� ����� ������� 0 ������� 5.
                count_multiple++;
            }

            // (��������� ���������� � ������)
            test_for_powers_of_two = input_data && !(input_data & (input_data - 1)); // �������� �� ������� ������.
            if (test_for_powers_of_two == 1) {
                count_degree++;
            }

            // (��������� ���������� � ������)
            if (count > 2) {
                if (input_data > (previous_number_1 + previous_number_2)) {
                    count_succession++;
                }
            }

            previous_number_2 = previous_number_1;
            previous_number_1 = input_data;

        }

        cin >> input_data; // ������ �������� ����� ����� �������� � input_data.
        check = input_data;
    }


    cout << "�) ������� �������������� ��������� �����: " << (amount / count) << endl;
    cout << "�) ������� ����� ���������� � ���������: " << max_number - min_number << endl;
    cout << "�) ���������� ������������� �����, ������� ����� 5: " << count_multiple << endl;
    cout << "�) ���������� �����, ���������� �������� ������: " << count_degree << endl;
    cout << "�) ���������� �����, ����������� ����� ���� �������������� ������ ������������������: " << count_succession
         << endl;
}
