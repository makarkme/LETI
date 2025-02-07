#include "application.h"
#include "polynom.h"
#include "application.h"

void ApplicationClass::Application::PrintMenu() {
    while (true) {
        std::cout << "Commands: \n"
            "-- 1) Continue with array \n"
            "-- 2) Continue with polynom \n";
        std::cin >> condition;
        switch (condition) {
        case 1:
            while (true) {
                std::cout << "Commands: \n"
                    "-- 1) Input array \n"
                    "-- 2) Output average and average square \n"
                    "-- 3) Output decrease and increase sorts \n"
                    "-- 4) Input resize \n"
                    "-- 5) Change element \n"
                    "-- 6) Print array \n"
                    "-- 7) Exit \n";

                std::cin >> condition2;

                switch (condition2) {
                case 1:
                    std::cout << "Input length array: \n";
                    std::cin >> size;
                    data.Resize(size);
                    std::cout << "Input elements of array: \n";
                    data.InputData();
                    size = NULL;
                    break;
                case 2:
                    std::cout << "Average:  ";
                    data.PrintAvgDev();
                    std::cout << "Average square:   ";
                    data.PrintAvgSqDev();
                    break;
                case 3:
                    std::cout << "Decrease:  ";
                    data.DecreaseSort();
                    data.PrintData();
                    std::cout << "Increase:  ";
                    data.IncreaseSort();
                    data.PrintData();
                    break;
                case 4:
                    std::cout << "Length array: \n";
                    std::cin >> size;
                    data.Resize(size);
                    size = NULL;
                    break;
                case 5:
                    std::cout << "Input old and new element \n";
                    std::cin >> oldElement;
                    std::cin >> newElement;
                    data.ChangeElement(oldElement, newElement);
                    break;
                case 6:
                    data.PrintData();
                    break;
                case 7:
                    exit(0);
                default:
                    continue;
                }
            }
            break;
        case 2:
            system("cls");
            while (true) {
                std::cout << "Commands:\n";
                std::cout << "-- 1) Input coeffs\n";
                std::cout << "-- 2) Input An & roots\n";
                if (key == 'a' || key == 'b')
                    std::cout << "-- 3) Calculate the value of a polynom\n";
                if (key == 'a')
                    std::cout << "-- 4) Print canonical polynom (form 1)\n";
                else if (key == 'b') {
                    std::cout << "-- 4) Change An\n";
                    std::cout << "-- 5) Change the root\n";
                    std::cout << "-- 6) Print classical polynom (form 2)\n";
                }
                std::cout << "-- 0) Exit\n";

                std::cin >> condition2;

                switch (condition2) {
                case 1:
                    std::cout << "Input n: \n";
                    std::cin >> size;
                    data = polinom.getData();
                    data.Resize(size + 1);
                    std::cout << "Input coeffs: \n";
                    data.InputData();
                    polinom.createPolynom(data);
                    size = NULL;
                    key = 'a';
                    break;
                case 2:
                    std::cout << "Input amount of roots: \n";
                    std::cin >> size;
                    data = polinom.getData();
                    data.Resize(size + 1);
                    std::cout << "Input An and " << size << " roots: \n";
                    data.InputData();
                    polinom.createPolynom(data);
                    size = NULL;
                    key = 'b';
                    break;
                case 3:
                    switch (key) {
                    case 'a':
                        std::cout << "Input value: \n";
                        std::cin >> value;
                        std::cout << polinom.countValue(value, key);
                        break;
                    case 'b':
                        std::cout << "Input value: \n";
                        std::cin >> value;
                        std::cout << polinom.countValue(value, key);
                        break;
                    default:
                        std::cout << "error!";
                        exit(0);
                    }
                    break;
                case 4:
                    switch (key) {
                    case 'a':
                        polinom.setPrintMode(PrintModeCanonic);
                        polinom.printPolynom();
                        break;
                    case 'b':
                        std::cout << "Input new An: \n";
                        std::cin >> newElement;
                        data = polinom.getData();
                        data.ChangeElement(data.getElement(0), newElement);
                        polinom.createPolynom(data);
                        break;
                    }
                    break;
                case 5:
                    switch (key) {
                    case 'b':
                        std::cout << "Input old root and new root: \n";
                        std::cin >> oldElement;
                        std::cin >> newElement;
                        data = polinom.getData();
                        data.ChangeElement(oldElement, newElement);
                        polinom.createPolynom(data);
                        break;
                    default:
                        std::cout << "error!";
                        exit(0);
                    }
                    break;
                case 6:
                    switch (key) {
                    case 'b':
                        polinom.setPrintMode(PrintModeClassic);
                        polinom.printPolynom();
                        break;
                    default:
                        std::cout << "error!";
                        exit(0);
                    }
                    break;
                case 0:
                    exit(0);
                    break;
                default:
                    continue;
                }
            }
            break;
        }

    }
}

ApplicationClass::Application::~Application() = default;
