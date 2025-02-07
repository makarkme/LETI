#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n;
    int length_last = 1; // —охранение длины чисел
    cout << "¬ведите число: " << endl;
    cin >> n;

    if (n >= 2) { // ѕровер€ем "2", т.к. это единственное четное простое число
        cout << 2;
    }

    for (int i = 3; i <= n; i += 2) { // ѕеребираем нечетные числа до n
        bool flag = true; // »значально ставим true, чтобы затем при нахождении составного числа изменить на false

        for (int j = 3; j * j <= i; j += 2) { // ѕеребираем делители до корн€ делимого. ѕровер€ем числа на "составность"
            if (i % j == 0) { // ≈сли остатка нет, значит число поделилось нацело, значит оно составное
                flag = false;
                break;
            }
        }
        if (flag) {

            int length = 0;
            int i_ = i;
            while (i_ > 0) { // Ќаходим длину числа, которое будем выводить
                length++;
                i_ /= 10;
            }

            if (length_last < length) { // ѕровер€ем, совпадает ли длина предыдущего числа с длиной текущего числа
                length_last = i / 10 + 1; // Ќаходим, к какому дес€тку относитс€ число
                cout << endl;
                cout << i;
            }
            else {
                cout << " " << i;
            }
        }
    }
}
