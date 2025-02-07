// Идея: Пользователь может 1) как передавать массив на сортировку из вне, 2) так и ввести набор данных
// Для 1) программа вернет отсортированный массив
// Для 2) программа сама создать массив (через ввод/произвольную генерацию данных), отсортирует его и вернет пользователю

#include "Menu.h"

int main() {
    // long long *array = new long long[5]{1, 2, 3, 4, 5}; // - для дин.массива
    // int lengthArray = 5;
    // long long array[] = {5, 4, 3, 2, 1}; // - для массива
    // constexpr int lengthArray = std::size(array);

    // MenuClass::Menu menu(*array, lengthArray); // - для 1)
    MenuClass::Menu menu; // - для 2)
    menu.PrintMenu();
}
