#include "application.h"

void ApplicationClass::Application::PrintMenu() {

    while (true) {
        std::cout << "Commands: \n"
                     "-- 1) Input array \n"
                     "-- 2) Output average and average square \n"
                     "-- 3) Output decrease and increase sorts \n"
                     "-- 4) Input resize \n"
                     "-- 5) Change element \n"
                     "-- 6) Print array \n"
                     "-- 7) Exit \n";

        std::cin >> condition;

        switch (condition) {
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
}

ApplicationClass::Application::~Application() = default;
