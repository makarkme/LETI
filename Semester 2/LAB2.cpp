#include <iostream>
#include <string>
#include <chrono>

using namespace std;

struct Node {
    int data;
    Node *head;
    Node *tail;
};

Node *createList(int length) {
    Node *curr = nullptr, *next = nullptr;
    for (int i = 0; i < length; ++i) {
        curr = new Node;
        curr->tail = next;
        if (next != nullptr)
            next->head = curr;
        next = curr;
    }
    curr->head = nullptr;
    return curr;
}

int lengthList(Node *curr) { // curr должен указывать на начало списка
    int length = 0;
    while (curr) {
        length += 1;
        curr = curr->tail;
    }
    return length;
}

void outputList(Node *curr) {
    int length = lengthList(curr);
    for (int i = 0; i < length; ++i) {
        cout << curr->data << " ";
        curr = curr->tail;
    }
}

Node *listItem(Node *curr, int index) { // возвращает указатель на текущую ноду
    int length = lengthList(curr);
    for (int i = 0; i < length; ++i) {
        if (index == i) {
            return curr;
        }
        curr = curr->tail;
    }
    return nullptr;
}

// создание элемента всегда происходит "левее". При index = 0, новая Node появится в начале списка
void listInsertItem(Node *&curr, int index, int insertItem) { // строго передавать curr, который указывает на начало
    Node *localCurr = curr;
    Node *newNode = new Node;
    if (index == 0) {
        curr->head = newNode;
        curr = curr->head;
        curr->head = nullptr;
        curr->tail = localCurr;
        localCurr = curr;
    } else if (index == lengthList(localCurr)) {
        curr = listItem(localCurr, index - 1);
        Node *beforeNewNode = curr;
        curr->tail = newNode;
        curr = curr->tail;
        curr->head = beforeNewNode;
        curr->tail = nullptr;
    } else {
        curr = listItem(localCurr, index - 1);
        Node *beforeNewNode = curr;
        Node *afterNewNode = curr->tail;
        curr->tail = newNode;
        curr = curr->tail;
        curr->head = beforeNewNode;
        curr->tail = afterNewNode;
        curr = curr->tail;
        curr->head = newNode;
        curr = curr->head;
    }
    curr->data = insertItem;
    curr = listItem(localCurr, 0);
}

void arrayInsertItem(int *&array, int &lengthArray, int index, int insertItem)
{
    int *newArray = new int[lengthArray + 1];
    for (int i = 0; i < index; ++i) // заполнение массива до index
        newArray[i] = array[i];
    newArray[index] = insertItem;

    for (int i = index + 1; i < lengthArray + 1; ++i) // заполнение массива после index
        newArray[i] = array[i - 1];
    lengthArray += 1;

    delete[] array;
    array = newArray;
}

void swapItem(Node *&curr, int firstIndex, int secondIndex) {
    Node *firstItem = listItem(curr, firstIndex);
    Node *secondItem = listItem(curr, secondIndex);
    int localData = secondItem->data;
    secondItem->data = firstItem->data;
    firstItem->data = localData;
}

void listDeleteItem(Node *&curr, int index) { // строго передавать curr, который указывает на начало
    Node *localCurr = curr;
    if (index == 0) {
        Node *Temp = curr;
        curr = curr->tail;
        curr->head = nullptr;
//        delete Temp; почему-то при удалении возникает exit code -1073740940 (0xC0000374)
    } else if (index == lengthList(localCurr) - 1) {
        curr = listItem(localCurr, index);
        Node *Temp = curr;
        curr = curr->head;
        curr->tail = nullptr;
        delete Temp;
        curr = listItem(localCurr, 0);
    } else {
        curr = listItem(localCurr, index);
        Node *Temp = curr;
        curr = curr->head;
        curr->tail = curr->tail->tail;
        curr = curr->tail;
        curr->head = curr->head->head;
        delete Temp;
        curr = listItem(localCurr, 0);
    }
}

void arrayDeleteItem(int *&array, int &lengthArray, int index)
{
    int *newArray = new int[lengthArray - 1];
    for (int i = 0; i < index; ++i) // заполнение массива до index
        newArray[i] = array[i];

    for (int i = index; i < lengthArray - 1; ++i) // заполнение массива после index
        newArray[i] = array[i + 1];
    lengthArray -= 1;

    delete[] array;
    array = newArray;
}

void deleteList(Node *&curr) {
    Node *next;
    while (curr) {
        next = curr->tail;
        delete curr;
        curr = next;
    }
}

int main() {
    Node *list = nullptr;
    int condition;

    long long listInputTimeA = 0, listInputTimeB = 0, listInsertTime = 0, listDeleteTime = 0, listSwapTime = 0, listOutputItemTime = 0;
    long long arrayInputTimeA = 0, arrayInputTimeB = 0, arrayInsertTime = 0, arrayDeleteTime = 0, arraySwapTime = 0, arrayOutputItemTime = 0;
    long long listSortTime = 0, arraySortTime = 0;

    int sizeList = 0;
    int *array = new int[sizeList];

    while (true) {
        cout << "Commands: \n"
                "-- 0) Exit \n"
                "-- 1) Input list \n"
                "-- 2) Speed for (1) \n"
                "-- 3) Insert/Delete/Swap/Output item \n"
                "-- 4) Speed for (3) \n"
                "-- 5) Output list \n"
                "-- 6) (IDZ) BubbleSort for list and array \n";
        cin >> condition;
        switch (condition) {
            case 0:
                deleteList(list);
                delete[] array;
                exit(-1);
            case 1:
                char firstResponse;
                cout << "Method input: (a) or (b)" << "\n";
                cin >> firstResponse;
                if (firstResponse == 'a') {
                    cout << "Size list: " << "\n";
                    cin >> sizeList;

                    // --реализация динамического массива--
                    auto arrayBegin = chrono::steady_clock::now();
                    array = new int[sizeList];
                    for (int i = 0; i < sizeList; ++i) {
                        array[i] = rand() % 100; // диапазон [0 - 99]
                    }
                    auto arrayEnd = chrono::steady_clock::now();
                    arrayInputTimeA = chrono::duration_cast<std::chrono::nanoseconds>(arrayEnd - arrayBegin).count();

                    // --реализация двусвязного списка
                    auto listBegin = chrono::steady_clock::now();
                    list = createList(sizeList); // инициализация
                    Node *curr = list; // курсор (указатель на текущий эл-т списка)
                    for (int i = 0; i < sizeList; ++i) {
                        curr->data = array[i];
                        curr = curr->tail;
                    }
                    auto listEnd = chrono::steady_clock::now();
                    listInputTimeA = chrono::duration_cast<std::chrono::nanoseconds>(listEnd - listBegin).count();

                } else if (firstResponse == 'b') {
                    string inputData;
                    cout << "Input data: " << "\n";
                    cin.ignore();
                    getline(cin, inputData);
                    string localString;
                    sizeList = 1;
                    for (int i = 0; i < inputData.size(); ++i) {
                        if (inputData[i] == ' ') {
                            sizeList += 1; // узнаём длину списка
                        }
                    }

                    // --реализация двусвязного списка
                    auto listBegin = chrono::steady_clock::now();
                    list = createList(sizeList);
                    Node *curr = list;
                    for (int i = 0; i < inputData.size(); ++i) {
                        if (inputData[i] != ' ') {
                            localString.push_back(inputData[i]);
                        } else {
                            curr->data = stoi(localString);
                            curr = curr->tail;
                            localString = "";
                        }
                    }
                    if (!localString.empty()) { // Ввод последнего элемента
                        curr->data = stoi(localString);
                    }
                    auto listEnd = chrono::steady_clock::now();
                    listInputTimeB = chrono::duration_cast<std::chrono::nanoseconds>(listEnd - listBegin).count();

                    // --реализация динамического массива--
                    auto arrayBegin = chrono::steady_clock::now();
                    array = new int[sizeList];
                    localString = "";
                    int localIndex = 0;
                    for (int i = 0; i < inputData.size(); ++i) {
                        if (inputData[i] != ' ') {
                            localString.push_back(inputData[i]);
                        } else {
                            array[localIndex] = stoi(localString);
                            localString = "";
                            localIndex += 1;
                        }
                    }
                    if (!localString.empty()) { // Ввод последнего элемента
                        array[localIndex] = stoi(localString);
                    }
                    auto arrayEnd = chrono::steady_clock::now();
                    arrayInputTimeB = chrono::duration_cast<std::chrono::nanoseconds>(arrayEnd - arrayBegin).count();

                } else {
                    cout << "Input error" << "\n";
                }
                break;
            case 2:
                cout << "Work time for inputList (a) | (b): " << listInputTimeA << "ns | " << listInputTimeB << "ns\n";
                cout << "Work time for inputArray (a) | (b): " << arrayInputTimeA << "ns | "<< arrayInputTimeB << "ns\n";
                break;
            case 3:
                if (list != nullptr) {
                    Node *curr = list;
                    char secondResponse;
                    cout << "Method input: (i/d/s/o)" << "\n";
                    cin >> secondResponse;
                    cin.ignore();
                    if (secondResponse == 'i') {
                        cout << "Input insert index: " << "\n";
                        int index;
                        cin >> index;
                        if (index > lengthList(list) or index < 0) {
                            cout << "Index error" << "\n";
                        } else {
                            int insertItem;
                            cout << "Input data: " << "\n";
                            cin >> insertItem;
                            // --реализация для двусвязного списка
                            auto listBegin = chrono::steady_clock::now();
                            listInsertItem(list, index, insertItem);
                            auto listEnd = chrono::steady_clock::now();
                            listInsertTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                    listEnd - listBegin).count();

                            // --реализация для динамического массива
                            auto arrayBegin = chrono::steady_clock::now();
                            arrayInsertItem(array, sizeList, index, insertItem);
                            auto arrayEnd = chrono::steady_clock::now();
                            arrayInsertTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                    arrayEnd - arrayBegin).count();
                        }
                    } else if (secondResponse == 'd') {
                        char thirdResponse;
                        cout << "Method input index or element: (i) or (e)" << "\n";
                        cin >> thirdResponse;
                        if (thirdResponse == 'i') {
                            cout << "Input delete index: " << "\n";
                            int index;
                            cin >> index;

                            if (index > lengthList(list) - 1 or index < 0) {
                                cout << "Index error" << "\n";
                            } else {
                                // --реализация для двусвязного списка
                                auto listBegin = chrono::steady_clock::now();
                                listDeleteItem(list, index);
                                auto listEnd = chrono::steady_clock::now();
                                listDeleteTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                        listEnd - listBegin).count();

                                // --реализация для динамического массива
                                auto arrayBegin = chrono::steady_clock::now();
                                arrayDeleteItem(array, sizeList, index);
                                auto arrayEnd = chrono::steady_clock::now();
                                arrayDeleteTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                        arrayEnd - arrayBegin).count();
                            }
                        } else if (thirdResponse == 'e') {
                            cout << "Input delete element: " << "\n";
                            int element;
                            cin >> element;

                            // --реализация для двусвязного списка
                            auto listBegin = chrono::steady_clock::now();
                            curr = list;
                            bool flag = false;
                            int length = lengthList(curr);
                            for (int i = 0; i < length; ++i) {
                                if (element == curr->data) {
                                    flag = true;
                                    listDeleteItem(list, i);
                                    break;
                                }
                                curr = curr->tail;
                            }
                            if (!flag) {
                                cout << "List item not found" << "\n";
                            }
                            auto listEnd = chrono::steady_clock::now();
                            listDeleteTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                    listEnd - listBegin).count();

                            // --реализация для динамического массива
                            auto arrayBegin = chrono::steady_clock::now();
                            flag = false;
                            for (int i = 0; i < sizeList; ++i) {
                                if (element == array[i]) {
                                    flag = true;
                                    arrayDeleteItem(array, sizeList, i);
                                    break;
                                }
                            }
                            if (!flag) {
                                cout << "Array item not found" << "\n";
                            }
                            auto arrayEnd = chrono::steady_clock::now();
                            arrayDeleteTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                    arrayEnd - arrayBegin).count();
                        } else {
                            cout << "Input error" << "\n";
                        }

                    } else if (secondResponse == 's') {
                        cout << "Input 2 swap index: " << "\n";
                        int firstIndex, secondIndex;
                        cin >> firstIndex >> secondIndex;
                        if (firstIndex > lengthList(list) - 1 or firstIndex < 0) {
                            cout << "Index error" << "\n";
                        } else if (secondIndex > lengthList(list) - 1 or secondIndex < 0) {
                            cout << "Index error" << "\n";
                        } else {
                            // --реализация для двусвязного списка
                            auto listBegin = chrono::steady_clock::now();
                            swapItem(list, firstIndex, secondIndex);
                            auto listEnd = chrono::steady_clock::now();
                            listSwapTime = chrono::duration_cast<std::chrono::nanoseconds>(listEnd - listBegin).count();

                            // --реализация для динамического массива
                            auto arrayBegin = chrono::steady_clock::now();
                            swap(array[firstIndex], array[secondIndex]);
                            auto arrayEnd = chrono::steady_clock::now();
                            arraySwapTime = chrono::duration_cast<std::chrono::nanoseconds>(arrayEnd - arrayBegin).count();
                        }
                    } else if (secondResponse == 'o') {
                        char thirdResponse;
                        cout << "Method input index or element: (i) or (e)" << "\n";
                        cin >> thirdResponse;
                        if (thirdResponse == 'i') {
                            cout << "Input index: " << "\n";
                            int index;
                            cin >> index;
                            if (index > lengthList(list) - 1 or index < 0) {
                                cout << "Index error" << "\n";
                            } else {
                                // --реализация для двусвязного списка
                                auto listBegin = chrono::steady_clock::now();
                                cout << "Element: " << listItem(list, index)->data << "\n";
                                auto listEnd = chrono::steady_clock::now();
                                listOutputItemTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                        listEnd - listBegin).count();

                                // --реализация для динамического массива
                                auto arrayBegin = chrono::steady_clock::now();
                                for (int i = 0; i < sizeList; ++i) {
                                    if (index == i) {
                                        cout << "Element:" << array[i] << "\n";
                                        break;
                                    }
                                }
                                auto arrayEnd = chrono::steady_clock::now();
                                arrayOutputItemTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                        arrayEnd - arrayBegin).count();
                            }
                        } else if (thirdResponse == 'e') {
                            cout << "Input element: " << "\n";
                            int element;
                            cin >> element;

                            // --реализация для двусвязного списка
                            auto listBegin = chrono::steady_clock::now();
                            curr = list;
                            bool flag = false;
                            int length = lengthList(curr);
                            for (int i = 0; i < length; ++i) {
                                if (element == curr->data) {
                                    cout << "Index: " << i << "\n";
                                    flag = true;
                                    break;
                                }
                                curr = curr->tail;
                            }
                            if (!flag) {
                                cout << "List index not found" << "\n";
                            }
                            auto listEnd = chrono::steady_clock::now();
                            listOutputItemTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                    listEnd - listBegin).count();

                            // --реализация для динамического массива
                            auto arrayBegin = chrono::steady_clock::now();
                            flag = false;
                            for (int i = 0; i < sizeList; ++i) {
                                if (element == array[i]) {
                                    cout << "Index:" << i << "\n";
                                    flag = true;
                                    break;
                                }
                            }
                            if (!flag) {
                                cout << "Array index not found" << "\n";
                            }
                            auto arrayEnd = chrono::steady_clock::now();
                            arrayOutputItemTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                    arrayEnd - arrayBegin).count();
                        } else {
                            cout << "Input error" << "\n";
                        }
                    } else {
                        cout << "Input error" << "\n";
                    }
                } else {
                    cout << "Error! Input list!" << "\n";
                }
                break;
            case 4:
                cout << "Work time for insert (list) and (array): " << listInsertTime << "ns | " << arrayInsertTime << "ns\n";
                cout << "Work time for delete (list) and (array): " << listDeleteTime << "ns | " << arrayDeleteTime << "ns\n";
                cout << "Work time for swap (list) and (array): " << listSwapTime << "ns | " << arraySwapTime << "ns\n";
                cout << "Work time for output (list) and (array): " << listOutputItemTime << "ns | " << arrayOutputItemTime << "ns\n";
                break;
            case 5:
                if (list != nullptr) {
                    Node *curr = list;
                    cout << "List: \t";
                    outputList(curr);

                    cout << "\nArray: \t";
                    for (int i = 0; i < sizeList; ++i) {
                        cout << array[i] << " ";
                    }
                    cout << "\n";
                } else {
                    cout << "Error! Input list!" << "\n";
                }
                break;
            case 6:
                // ИДЗ №1

                if (list != nullptr) {
                    // --реализация для двусвязного списка
                    auto listBegin = chrono::steady_clock::now();
                    Node *curr = list;
                    int length = lengthList(curr);
                    for (int i = 0; i < length; ++i) {
                        for (int j = 0; j < length - i - 1; ++j) {
                            if (listItem(curr, j)->data > listItem(curr, j + 1)->data) {
                                int buffer = listItem(curr, j + 1)->data;
                                listItem(curr, j + 1)->data = listItem(curr, j)->data;
                                listItem(curr, j)->data = buffer;
                            }
                        }
                    }
                    auto listEnd = chrono::steady_clock::now();
                    listSortTime = chrono::duration_cast<std::chrono::nanoseconds>(
                            listEnd - listBegin).count();

                    // --реализация для динамического массива
                    auto arrayBegin = chrono::steady_clock::now();
                    for (int i = 0; i < sizeList; ++i) {
                        for (int j = 0; j < sizeList - i - 1; ++j) {
                            if (array[j] > array[j + 1]) {
                                swap(array[j], array[j + 1]);
                            }
                        }
                    }
                    auto arrayEnd = chrono::steady_clock::now();
                    arraySortTime = chrono::duration_cast<std::chrono::nanoseconds>(
                            arrayEnd - arrayBegin).count();
                }
                cout << "Sort time for (list) and (array): " << listSortTime << "ns | " << arraySortTime << "ns\n";
                break;
            default:
                continue;
        }
    }
}