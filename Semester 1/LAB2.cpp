#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Введите последовательность целых чисел: " << endl;

    int input_data = 0, check = 1, max_number = 0, min_number = 2147483647, count_multiple = 0,
    count_degree = 0, count_succession = 0, previous_number_1 = 0, previous_number_2 = 0;
    float amount = 0, count = 0;
    bool test_for_powers_of_two;

    while (check != 0) { // (В check будут записываться все значения, что и в input_data.) Условие выхода из цикла.

        if (input_data != 0) { // (Подробное объяснение в отчёте)

            amount += input_data; // Сумма всей последовательности.
            count++; // Количество эл-ов последовательности.

            if (input_data > max_number) {  // Находим максимальное число.
                max_number = input_data;
            }

            if (input_data < min_number) {  // Находим минимальное число.
                min_number = input_data;
            }

            if ((input_data > 0) and (input_data % 5 == 0)) { // Находим числа большие 0 кратные 5.
                count_multiple++;
            }

            // (Подробное объяснение в отчёте)
            test_for_powers_of_two = input_data && !(input_data & (input_data - 1)); // Проверка на степень двойки.
            if (test_for_powers_of_two == 1) {
                count_degree++;
            }

            // (Подробное объяснение в отчёте)
            if (count > 2) {
                if (input_data > (previous_number_1 + previous_number_2)) {
                    count_succession++;
                }
            }

            previous_number_2 = previous_number_1;
            previous_number_1 = input_data;

        }

        cin >> input_data; // Каждое введённое число будет записано в input_data.
        check = input_data;
    }


    cout << "а) Среднее арифметическое введенных чисел: " << (amount / count) << endl;
    cout << "б) Разница между максимумом и минимумом: " << max_number - min_number << endl;
    cout << "в) Количество положительных чисел, кратных числу 5: " << count_multiple << endl;
    cout << "г) Количество чисел, являющихся степенью двойки: " << count_degree << endl;
    cout << "д) Количество чисел, превышающих сумму двух предшествующих членов последовательности: " << count_succession
         << endl;
}
