#include "Menu.h"

MenuClass::Menu::Menu(const std::string &inputData) {
    inputString = inputData;
    menuStatus = 1;
}

void MenuClass::Menu::PrintMenu() {
    if (menuStatus == 0) {
        // для ввода из iostream
        while (exitSwitchFirst) {
            std::cout << "Commands: \n"
                    "-- 0) Exit \n"
                    "-- 1) Base binary tree \n"
                    "-- 2) Red-black tree \n";

            std::cin >> conditionFirst;

            BaseTreeClass::BaseTree baseTree;
            RBTreeClass::RBTree rbTree;

            switch (conditionFirst) {
                case 0: {
                    exitSwitchFirst = false;
                    baseTree.deleteTree(&rootBaseTree);
                    rbTree.deleteTree(&rootRBTree);
                    break;
                }
                case 1: {
                    exitSwitchSecond = true;
                    while (exitSwitchSecond) {
                        std::cout << "-- Commands: \n"
                                "-- -- 0) Exit \n"
                                "-- -- 1) Input tree \n"
                                "-- -- 2) Output tree \n"
                                "-- -- 3) Traversing a tree in depth \n";

                        std::cin >> conditionSecond;

                        switch (conditionSecond) {
                            case 0: {
                                exitSwitchSecond = false;
                                break;
                            }
                            case 1: {
                                std::cout << "Input string: " << "\n";

                                std::cin.ignore();
                                std::getline(std::cin, inputString);

                                StringParserClass::StringParser stringParser;
                                vectorInputData = stringParser.vectorInputData(inputString);
                                baseTree.inputTree(vectorInputData, &rootBaseTree);
                                break;
                            }
                            case 2: {
                                baseTree.printTree(rootBaseTree);
                                break;
                            }
                            case 3: {
                                std::cout << "Pre-order: " << "\n";
                                baseTree.printPreOrder(&rootBaseTree);
                                std::cout << "\n";
                                break;
                            }
                            default: {
                                continue;
                            }
                        }
                    }
                    break;
                }
                case 2: {
                    exitSwitchSecond = true;
                    while (exitSwitchSecond) {
                        std::cout << "-- Commands: \n"
                                "-- -- 0) Exit \n"
                                "-- -- 1) Input tree \n"
                                "-- -- 2) Output tree \n"
                                "-- -- 3) Insert data \n"
                                "-- -- 4) Delete data \n"
                                "-- -- 5) Search data \n"
                                "-- -- 6) Traversing a tree \n";

                        std::cin >> conditionSecond;

                        switch (conditionSecond) {
                            case 0: {
                                exitSwitchSecond = false;
                                break;
                            }
                            case 1: {
                                std::cout << "Input string: " << "\n";

                                std::cin.ignore();
                                std::getline(std::cin, inputString);

                                StringParserClass::StringParser stringParser;
                                vectorInputData = stringParser.vectorInputData(inputString);
                                rbTree.inputTree(vectorInputData, &rootRBTree);
                                break;
                            }
                            case 2: {
                                rbTree.printTree(rootRBTree);
                                break;
                            }
                            case 3: {
                                int insertElement;
                                std::cout << "Input insert value: " << "\n";
                                std::cin >> insertElement;
                                rbTree.insert(insertElement, &rootRBTree);
                                break;
                            }
                            case 4: {
                                int deleteElement;
                                std::cout << "Input delete value: " << "\n";
                                std::cin >> deleteElement;
                                rbTree.remove(deleteElement, &rootRBTree);
                                break;
                            }
                            case 5: {
                                int searchElement;
                                std::cout << "Input search value: " << "\n";
                                std::cin >> searchElement;
                                rbTree.search(searchElement, rootRBTree);
                                break;
                            }
                            case 6: {
                                std::cout << "width: " << "\n";
                                rbTree.printWidth(&rootRBTree);
                                std::cout << "\n";
                                std::cout << "depth (pre-order): " << "\n";
                                rbTree.printPreOrder(&rootRBTree);
                                std::cout << "\n";
                                std::cout << "depth (in-order): " << "\n";
                                rbTree.printInOrder(&rootRBTree);
                                std::cout << "\n";
                                std::cout << "depth (post-order): " << "\n";
                                rbTree.printPostOrder(&rootRBTree);
                                std::cout << "\n";
                                break;
                            }
                            default: {
                                continue;
                            }
                        }
                    }
                    break;
                }
                default: {
                    continue;
                }
            }
        }
    }

    if (menuStatus == 1) {
        // для ввода из input.txt
        while (exitSwitchFirst) {
            std::cout << "Commands: \n"
                    "-- 0) Exit \n"
                    "-- 1) Binary tree \n"
                    "-- 2) Red-black tree \n";

            std::cin >> conditionFirst;

            BaseTreeClass::BaseTree baseTree;
            RBTreeClass::RBTree rbTree;

            StringParserClass::StringParser stringParser;
            vectorInputData = stringParser.vectorInputData(inputString);

            baseTree.inputTree(vectorInputData, &rootBaseTree);
            rbTree.inputTree(vectorInputData, &rootRBTree);

            switch (conditionFirst) {
                case 0: {
                    exitSwitchFirst = false;
                    baseTree.deleteTree(&rootBaseTree);
                    rbTree.deleteTree(&rootRBTree);
                    break;
                }
                case 1: {
                    exitSwitchSecond = true;
                    while (exitSwitchSecond) {
                        std::cout << "-- Commands: \n"
                                "-- -- 0) Exit \n"
                                "-- -- 1) Output tree \n"
                                "-- -- 2) Traversing a tree in depth \n";

                        std::cin >> conditionSecond;

                        switch (conditionSecond) {
                            case 0: {
                                exitSwitchSecond = false;
                                break;
                            }
                            case 1: {
                                baseTree.printTree(rootBaseTree);
                                break;
                            }
                            case 2: {
                                std::cout << "Pre-order: " << "\n";
                                baseTree.printPreOrder(&rootBaseTree);
                                std::cout << "\n";
                                break;
                            }
                            default: {
                                continue;
                            }
                        }
                    }
                    break;
                }
                case 2: {
                    exitSwitchSecond = true;
                    while (exitSwitchSecond) {
                        std::cout << "-- Commands: \n"
                                "-- -- 0) Exit \n"
                                "-- -- 1) Output tree \n"
                                "-- -- 2) Insert data \n"
                                "-- -- 3) Delete data \n"
                                "-- -- 4) Search data \n"
                                "-- -- 5) Traversing a tree \n";

                        std::cin >> conditionSecond;

                        switch (conditionSecond) {
                            case 0: {
                                exitSwitchSecond = false;
                                break;
                            }
                            case 1: {
                                rbTree.printTree(rootRBTree);
                                break;
                            }
                            case 2: {
                                int insertElement;
                                std::cout << "Input insert value: " << "\n";
                                std::cin >> insertElement;
                                rbTree.insert(insertElement, &rootRBTree);
                                break;
                            }
                            case 3: {
                                int deleteElement;
                                std::cout << "Input delete value: " << "\n";
                                std::cin >> deleteElement;
                                rbTree.remove(deleteElement, &rootRBTree);
                                break;
                            }
                            case 4: {
                                int searchElement;
                                std::cout << "Input search value: " << "\n";
                                std::cin >> searchElement;
                                rbTree.search(searchElement, rootRBTree);
                                break;;
                            }
                            case 5: {
                                std::cout << "width: " << "\n";
                                rbTree.printWidth(&rootRBTree);
                                std::cout << "\n";
                                std::cout << "depth (pre-order): " << "\n";
                                rbTree.printPreOrder(&rootRBTree);
                                std::cout << "\n";
                                std::cout << "depth (in-order): " << "\n";
                                rbTree.printInOrder(&rootRBTree);
                                std::cout << "\n";
                                std::cout << "depth (post-order): " << "\n";
                                rbTree.printPostOrder(&rootRBTree);
                                std::cout << "\n";
                                break;
                            }
                            default: {
                                continue;
                            }
                        }
                    }
                    break;
                }
                default: {
                    continue;
                }
            }
        }
    }
}
