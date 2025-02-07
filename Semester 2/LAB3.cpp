#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

map<string, int> dictOperators = {{"+", 1},
                                  {"-", 1},
                                  {"*", 2},
                                  {"/", 2},
                                  {"(", 0},
                                  {")", 0}};

// -- Реализацию стека писал умалишенный шизойд, поэтому эта реализация представляена огромным рядом кранйне сомнительных решений,
// больше похожий на говнокод. Я как мог, поправил это дело, но я тоже не всесисен. По-хорошему тут надо полностью переписывать реализацию стека.

// UPD: Половина функций переписана, добавлен адекватный нейминг
// UPD 2: В коде наложен полнейший болт на все приниципы ООП


struct Node {
    string value;
    struct Node *next = nullptr;
};

int sizeStack(Node *head) {
    int count = 0;
    while (head) {
        count += 1;
        head = head->next;
    }
    return count;
}

void push(Node **head, string value) {
    Node *tmp = new(malloc(sizeof(Node))) Node;
    tmp->value = value;
    tmp->next = *head;
    *head = tmp;
}

Node *getLast(Node *head) { // Получение ссылки на последний элемент стека
    if (head == nullptr) {
        return nullptr;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

Node *getLastButOne(Node *head) { // На случай, если стэк операций больше двух
    // (я не знаю, что ему не понравилось, и почему он решил отдельно для 2 элементов это написать)
    if (head == nullptr) {
        exit(-2);
    }
    if (head->next == nullptr) {
        return nullptr;
    }
    while (head->next->next) {
        head = head->next;
    }
    return head;
}

void pushBack(Node *head, string value) {
    Node *last = getLast(head);
    Node *tmp = new(malloc(sizeof(Node))) Node;
    tmp->value = value;
    tmp->next = nullptr;
    last->next = tmp;
}

void addStackElement(Node *&stack, string &value) { // Инициализация стека
    if (!stack) {
        push(&stack, value);
    } else {
        pushBack(stack, value);
    }
}

string pop(Node **head) { // Считывание (удаление как следствие) элемента с вершины стека
    Node *prev;
    string value;
    if (head == nullptr) {
        exit(-1); // нахера оно тут надо?
    }
    prev = *head;
    value = prev->value;
    *head = (*head)->next;
    free(prev); // 2024 на дворе - человек free и malloc в с++ пользуется
    return value;
}

string popBack(Node **head) { // Считывание элемента с низа стека (лютейший костыль по обходу механики стека)
    string value;
    Node *lastbn;
    if (!head) {
        exit(-1); // я не знаю, зачем этот бред
    }
    if (!(*head)) {
        exit(-1);
    }

    lastbn = getLastButOne(*head); // По всей видимости решение с "getlastbutone" - это костыль для этой функции
    value = lastbn->next->value;

    //Если в списке один элемент
    if (lastbn == nullptr) { // это вообще никогда не выполнится
        free(*head);
        *head = nullptr;
    } else {
        free(lastbn->next);
        lastbn->next = nullptr;
    }
    return value;
}

void deleteStack(Node *&head) {
    Node *next;
    while (head) {
        next = head->next;
        delete head;
        head = next;
    }
    head = nullptr;
}

void printStack(Node *head) {
    while (head) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << "\n";
}

bool isNumber(const string &data) {
    string::const_iterator it = data.begin();
    while (it != data.end() and isdigit(*it)) {
        it += 1;
    }
    return (!data.empty() and it == data.end());
}

bool isOperation(const string &data, map<string, int> map) {
    auto res = map.find(data);
    return (!(res == map.end()));
}

vector<string> splitIntoArray(string inputString) {
    vector<string> arrayData{};

    inputString += " ";
    string localString;
    for (int i = 0; i < inputString.size(); ++i) {
        if (inputString[i] != ' ') {
            localString.push_back(inputString[i]);
        } else {
            arrayData.push_back(localString);
            localString.clear();
        }
    }

    return arrayData;
}

double action(double &value1, double &value2, string &operation) {
    switch (operation[0]) {
        case '+':
            return value1 + value2;
        case '-':
            return value1 - value2;
        case '*':
            return value1 * value2;
        case '/':
            return value1 / value2;
        default:
            break;
    }
}

// Проверим вес текущего токена с весом вершины стека операций
bool checkWeight(const string &operation, Node *stackOperation, const map<string, int> &map) {
    if (stackOperation == nullptr) {
        // Стек операций пуст, значит текущий токен автоматически имеет больший "вес"
        return true;
    } else {
        // Получим вес текущего токена
        int operationWeight = map.at(operation);
        // Получим вес последней операции в стеке
        int topOpWeight = map.at(stackOperation->value);

        // Возвращаем true, если вес текущего токена больше или равен весу верхнего токена в стеке
        return (operationWeight >= topOpWeight);
    }
}

void polishNotation(vector<string> splitInputArray, Node *&stackNumbers, Node *&stackOperators) {
    string localString;
    int countLeftBrackets = 0;
    int countRightBrackets = 0;
    bool flagBracket = false;
    for (int i = size(splitInputArray) - 1; i > -1; --i) {
        if (isNumber(splitInputArray[i])) {
            addStackElement(stackNumbers, splitInputArray[i]);
            continue;
        }
        if (isOperation(splitInputArray[i], dictOperators)) {
            if (splitInputArray[i] == ")") {
                addStackElement(stackOperators, splitInputArray[i]);
                countRightBrackets += 1;
                flagBracket = true;
                continue;
            }
            if (splitInputArray[i] == "(") {
                if (!flagBracket) {
                    cout << "[ERROR]: lost brackets." << "\n";
                    exit(-1);
                } else {
                    flagBracket = false;
                }

                countLeftBrackets += 1;
                while (stackOperators and localString != ")") {
                    if (sizeStack(stackOperators) >= 2) { // продолжение костыля
                        localString = popBack(&stackOperators);
                    } else {
                        localString = pop(&stackOperators);
                    }
                    addStackElement(stackNumbers, localString); // тут записываются операторы внутри скобок в итоговый стек
                    localString = getLast(stackOperators)->value;
                }
                localString.clear();

                if (sizeStack(stackOperators) >= 2) { // тут чистим скобки
                    popBack(&stackOperators);
                } else {
                    pop(&stackOperators);
                }
                continue;
            }

            if (!stackOperators) {
                push(&stackOperators, splitInputArray[i]);
                continue;
            }
            if (checkWeight(splitInputArray[i], stackOperators, dictOperators)) { // Если вес текущего >= предыдущему
                pushBack(stackOperators, splitInputArray[i]);
            } else {
                if (sizeStack(stackOperators) >= 2) { // если стэк операций больше двух
                    pushBack(stackNumbers, popBack(&stackOperators));
                } else {
                    pushBack(stackNumbers, pop(&stackOperators));
                }

                addStackElement(stackOperators, splitInputArray[i]);
            }
            continue;
        }

        cout << "[ERROR]: unexpected data " << splitInputArray[i] << "\n";
        exit(-1);
    }

    if (countLeftBrackets != countRightBrackets) {
        cout << "[ERROR]: lost brackets." << "\n";
        exit(-1);
    }

    while (stackOperators) {
        if (sizeStack(stackOperators) >= 2) { // если стэк операций больше двух
            pushBack(stackNumbers, popBack(&stackOperators));
        } else {
            pushBack(stackNumbers, pop(&stackOperators));
        }
    }
    cout << "polishNotation: ";
    int lenStack = sizeStack(stackNumbers);
    string outputArray[lenStack];
    for (int i = 0; i < lenStack; ++i) {
        outputArray[i] = pop(&stackNumbers);
    }
    for (int i = lenStack - 1; i > -1; --i) {
        cout << outputArray[i] << " ";
    }

    cout << "\n";
}

void reversePolishNotation(vector<string> splitInputArray, Node *&stackNumbers, Node *&stackOperators) {
    string localString;
    int countLeftBrackets = 0;
    int countRightBrackets = 0;
    bool flagBracket = false;
    for (int i = 0; i < size(splitInputArray); ++i) {
        if (isNumber(splitInputArray[i])) {
            addStackElement(stackNumbers, splitInputArray[i]);
            continue;
        }
        if (isOperation(splitInputArray[i], dictOperators)) {
            if (splitInputArray[i] == "(") {
                addStackElement(stackOperators, splitInputArray[i]);
                countLeftBrackets += 1;
                flagBracket = true;
                continue;
            }
            if (splitInputArray[i] == ")") {
                if (!flagBracket) {
                    cout << "[ERROR]: lost brackets." << "\n";
                    exit(-1);
                } else {
                    flagBracket = false;
                }

                countRightBrackets += 1;
                while (stackOperators and localString != "(") {
                    if (sizeStack(stackOperators) >= 2) { // продолжение костыля
                        localString = popBack(&stackOperators);
                    } else {
                        localString = pop(&stackOperators);
                    }
                    addStackElement(stackNumbers, localString);
                    localString = getLast(stackOperators)->value;
                }
                localString.clear();

                if (sizeStack(stackOperators) >= 2) {
                    popBack(&stackOperators);
                } else {
                    pop(&stackOperators);
                }
                continue;
            }

            if (!stackOperators) {
                push(&stackOperators, splitInputArray[i]);
                continue;
            }
            if (checkWeight(splitInputArray[i], stackOperators, dictOperators)) { // Если вес текущего >= предыдущему
                pushBack(stackOperators, splitInputArray[i]);
            } else {
                if (sizeStack(stackOperators) >= 2) { // если стэк операций больше двух
                    pushBack(stackNumbers, popBack(&stackOperators));
                } else {
                    pushBack(stackNumbers, pop(&stackOperators));
                }

                addStackElement(stackOperators, splitInputArray[i]);
            }
            continue;
        }

        cout << "[ERROR]: unexpected data " << splitInputArray[i] << "\n";
        exit(-1);
    }

    if (countLeftBrackets != countRightBrackets) {
        cout << "[ERROR]: lost brackets." << "\n";
        exit(-1);
    }

    while (stackOperators) {
        if (sizeStack(stackOperators) >= 2) { // если стэк операций больше двух
            pushBack(stackNumbers, popBack(&stackOperators));
        } else {
            pushBack(stackNumbers, pop(&stackOperators));
        }
    }
    cout << "RecersePolishNotation: ";
    printStack(stackNumbers);

}

double calculatePN(Node *stackNumbers) { // Вычисление польской нотации
    Node *tempStack = nullptr;

    while (stackNumbers != nullptr) {
        string data = stackNumbers->value;
        if (isNumber(data)) {
            push(&tempStack, data);
        } else { // Иначе значение - это операция
            double firstValue = stod(pop(&tempStack));
            double secondValue = stod(pop(&tempStack));
            if (isOperation(data, dictOperators)) {
                try {
                    push(&tempStack,to_string(action(firstValue, secondValue, data))); // to_string - преобразует double в string
                }
                catch (...) {
                    cout << "[ERROR]: operation error.";
                    exit(-1);
                }
            }
        }
        stackNumbers = stackNumbers->next;
    }

    return stod(tempStack->value);
}

double calculateRPN(Node *stackNumbers) { // Вычисление обратной польской нотации
    Node *tempStack = nullptr;

    while (stackNumbers != nullptr) {
        string data = stackNumbers->value;
        if (isNumber(data)) {
            push(&tempStack, data);
        } else { // Иначе значение - это операция
            double secondValue = stod(pop(&tempStack));
            double firstValue = stod(pop(&tempStack));
            if (isOperation(data, dictOperators)) {
                try {
                    push(&tempStack,
                         to_string(action(firstValue, secondValue, data))); // to_string - преобразует double в string
                }
                catch (...) {
                    cout << "[ERROR]: operation error.";
                    exit(-1);
                }
            }
        }
        stackNumbers = stackNumbers->next;
    }

    return stod(tempStack->value);
}

int main() {
    Node *stackOperators = nullptr;
    Node *stackNumbers = nullptr;

    int condition;
    while (true) {
        string inputString;
        vector<string> splitInputArray{};
        cout << "Commands: \n"
                "-- 0) Exit \n"
                "-- 1) Input infix form \n" // Перевод в (pre/post)fix form + расчет
                "-- 2) Input prefix (Polish) form \n" // Расчет
                "-- 3) Input postfix (reversePolish) form \n"; // Расчет


        cin >> condition;
        switch (condition) {
            case (0):
                exit(0);
            case (1):
                cout << "Input data: " << "\n";
                cin.ignore();
                getline(cin, inputString);

                splitInputArray = splitIntoArray(inputString);
                polishNotation(splitInputArray, stackNumbers, stackOperators);

                deleteStack(stackNumbers);
                deleteStack(stackOperators);

                reversePolishNotation(splitInputArray, stackNumbers, stackOperators);
                cout << "Result: " << calculateRPN(stackNumbers) << "\n";

                deleteStack(stackNumbers);
                deleteStack(stackOperators);

                break;
            case (2):
                cout << "Input data: " << "\n";
                cin.ignore();
                getline(cin, inputString);

                splitInputArray = splitIntoArray(inputString);
                for (int i = size(splitInputArray) - 1; i > -1; --i) {
                    addStackElement(stackNumbers, splitInputArray[i]);
                }

                cout << "Result: " << calculatePN(stackNumbers) << "\n";
                deleteStack(stackNumbers);

                break;
            case (3):
                cout << "Input data: " << "\n";
                cin.ignore();
                getline(cin, inputString);

                splitInputArray = splitIntoArray(inputString);
                for (int i = 0; i < size(splitInputArray); ++i) {
                    addStackElement(stackNumbers, splitInputArray[i]);
                }

                cout << "Result: " << calculateRPN(stackNumbers) << "\n";
                deleteStack(stackNumbers);

                break;
            default:
                continue;
        }
    }
}