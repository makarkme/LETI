#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n;
    int length_last = 1; // ���������� ����� �����
    cout << "������� �����: " << endl;
    cin >> n;

    if (n >= 2) { // ��������� "2", �.�. ��� ������������ ������ ������� �����
        cout << 2;
    }

    for (int i = 3; i <= n; i += 2) { // ���������� �������� ����� �� n
        bool flag = true; // ���������� ������ true, ����� ����� ��� ���������� ���������� ����� �������� �� false

        for (int j = 3; j * j <= i; j += 2) { // ���������� �������� �� ����� ��������. ��������� ����� �� "�����������"
            if (i % j == 0) { // ���� ������� ���, ������ ����� ���������� ������, ������ ��� ���������
                flag = false;
                break;
            }
        }
        if (flag) {

            int length = 0;
            int i_ = i;
            while (i_ > 0) { // ������� ����� �����, ������� ����� ��������
                length++;
                i_ /= 10;
            }

            if (length_last < length) { // ���������, ��������� �� ����� ����������� ����� � ������ �������� �����
                length_last = i / 10 + 1; // �������, � ������ ������� ��������� �����
                cout << endl;
                cout << i;
            }
            else {
                cout << " " << i;
            }
        }
    }
}
