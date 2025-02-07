#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n;
    cin >> n;

    int* list = new int[n];
    for (int i = 0; i < n; i++) { // «аполн€ем массив
        cin >> list[i];
    }

    for (int i = 0; i < n / 2; i++) { // ƒальше половины нету смысла проходить.
        int data = list[i]; // ќб€зательно запоминаем, чтоб значение не потер€лось.
        list[i] = list[n - 1 -
                       i]; // замен€ем значение на значение с зеркальной позицией в массиве (n - 1 используетс€, ибо нумераци€ в массиве с 0, а длина - нет)
        list[n - 1 - i] = data;
    }
    cout << "ѕеревернуть массив и вывести на экран: ";
    for (int i = 0; i < n; i++) {
        cout << list[i] << " "; // ¬ывод
    }

    cout << endl;

    int k;
    cin >> k;

    for (int i = 0; i < k; i++) { // ѕроходимс€ до k - столько раз будем "прокручивать" массив влево
        int data = list[0]; // “ак как у нас цикл в цикле, то каждое новый цикл в позиции 0 будет то число, которое нам нужно сдвинуть
        for (int j = 1; j < n; j++) { // Ќачинаем с j = 1, т.к. j = 0 - это уже data
            list[j - 1] = list[j]; // ѕрисваиваем предыдущему текущее (основной механизм "прокручивани€")
        }
        list[n - 1] = data; // ѕризваиваем в конец массива значение, которое "прокручиваетс€"
    }

    cout << "¬ывести на экран результат ротации массива влево на k элементов: ";
    for (int i = 0; i < n; i++) {
        cout << list[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < k; i++) { //(по аналогии с алгоритмом выше)
        int data = list[n - 1]; // «апоминаем последнее значение
        for (int j = n - 1 - 1;
             j >= 0; j--) { // “ут двигаемс€ по массиву не слева направо, а наоборот. “ак проще работать со значени€ми.
            list[j + 1] = list[j];
        }
        list[0] = data;
    }

    cout << "¬ывести на экран результат ротации массива вправо на k элементов: ";
    for (int i = 0; i < n; i++) {
        cout << list[i] << " ";
    }

    cout << endl;

    int index_max_number, index_min_number, max_number = 0, min_number = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (max_number < list[i]) {
            max_number = list[i]; // —равниваем числа, находим максимум, записываем его индекс
            index_max_number = i;
        }
        if (min_number > list[i]) {
            min_number = list[i]; // аналогично
            index_min_number = i;
        }
    }

    cout << "¬ывести индексы максимального и минимального элементов массива: " << index_max_number << " "
         << index_min_number << endl;

    for (int i = 0; i <
                    n; i++) { // (Ќаходим максимальный элемент в массиве - ставим его в начало.
        // –ассматриваем массив, но уже без первого элемента, снова находим максимаму и ставим уже после первого максимума.
        // “ак, пока не отсортируетс€.
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

    cout << "¬ывести отсортированный массив в пор€дке убывани€: ";
    for (int i = 0; i < n; i++) {
        cout << list[i] << " ";
    }

    delete [] list;
}