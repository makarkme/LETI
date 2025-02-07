// Идея: Пользователь может 1) как ввести эл-ты дерева (iostream),
//                          2) так и передавать их из вне (файл).

#include <fstream>
#include <string>
#include <windows.h>

#include "Menu.h"

int main() {
    SetConsoleOutputCP(65001);


    std::ifstream fin("input.txt");
    std::string inputData;
    std::getline(fin, inputData);
    fin.close();

    MenuClass::Menu menu; // - для 1)
    // MenuClass::Menu menu(inputData); // - для 2)
    menu.PrintMenu();
}
