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

// -- ���������� ����� ����� ����������� ������, ������� ��� ���������� ������������� �������� ����� ������� ������������ �������,
// ������ ������� �� ��������. � ��� ���, �������� ��� ����, �� � ���� �� ��������. ��-�������� ��� ���� ��������� ������������ ���������� �����.

// UPD: �������� ������� ����������, �������� ���������� �������
// UPD 2: � ���� ������� ��������� ���� �� ��� ��������� ���


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

Node *getLast(Node *head) { // ��������� ������ �� ��������� ������� �����
    if (head == nullptr) {
        return nullptr;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

Node *getLastButOne(Node *head) { // �� ������, ���� ���� �������� ������ ����
    // (� �� ����, ��� ��� �� �����������, � ������ �� ����� �������� ��� 2 ��������� ��� ��������)
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

void addStackElement(Node *&stack, string &value) { // ������������� �����
    if (!stack) {
        push(&stack, value);
    } else {
        pushBack(stack, value);
    }
}

string pop(Node **head) { // ���������� (�������� ��� ���������) �������� � ������� �����
    Node *prev;
    string value;
    if (head == nullptr) {
        exit(-1); // ������ ��� ��� ����?
    }
    prev = *head;
    value = prev->value;
    *head = (*head)->next;
    free(prev); // 2024 �� ����� - ������� free � malloc � �++ ����������
    return value;
}

string popBack(Node **head) { // ���������� �������� � ���� ����� (�������� ������� �� ������ �������� �����)
    string value;
    Node *lastbn;
    if (!head) {
        exit(-1); // � �� ����, ����� ���� ����
    }
    if (!(*head)) {
        exit(-1);
    }

    lastbn = getLastButOne(*head); // �� ���� ��������� ������� � "getlastbutone" - ��� ������� ��� ���� �������
    value = lastbn->next->value;

    //���� � ������ ���� �������
    if (lastbn == nullptr) { // ��� ������ ������� �� ����������
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

// �������� ��� �������� ������ � ����� ������� ����� ��������
bool checkWeight(const string &operation, Node *stackOperation, const map<string, int> &map) {
    if (stackOperation == nullptr) {
        // ���� �������� ����, ������ ������� ����� ������������� ����� ������� "���"
        return true;
    } else {
        // ������� ��� �������� ������
        int operationWeight = map.at(operation);
        // ������� ��� ��������� �������� � �����
        int topOpWeight = map.at(stackOperation->value);

        // ���������� true, ���� ��� �������� ������ ������ ��� ����� ���� �������� ������ � �����
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
                    if (sizeStack(stackOperators) >= 2) { // ����������� �������
                        localString = popBack(&stackOperators);
                    } else {
                        localString = pop(&stackOperators);
                    }
                    addStackElement(stackNumbers, localString); // ��� ������������ ��������� ������ ������ � �������� ����
                    localString = getLast(stackOperators)->value;
                }
                localString.clear();

                if (sizeStack(stackOperators) >= 2) { // ��� ������ ������
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
            if (checkWeight(splitInputArray[i], stackOperators, dictOperators)) { // ���� ��� �������� >= �����������
                pushBack(stackOperators, splitInputArray[i]);
            } else {
                if (sizeStack(stackOperators) >= 2) { // ���� ���� �������� ������ ����
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
        if (sizeStack(stackOperators) >= 2) { // ���� ���� �������� ������ ����
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
                    if (sizeStack(stackOperators) >= 2) { // ����������� �������
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
            if (checkWeight(splitInputArray[i], stackOperators, dictOperators)) { // ���� ��� �������� >= �����������
                pushBack(stackOperators, splitInputArray[i]);
            } else {
                if (sizeStack(stackOperators) >= 2) { // ���� ���� �������� ������ ����
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
        if (sizeStack(stackOperators) >= 2) { // ���� ���� �������� ������ ����
            pushBack(stackNumbers, popBack(&stackOperators));
        } else {
            pushBack(stackNumbers, pop(&stackOperators));
        }
    }
    cout << "RecersePolishNotation: ";
    printStack(stackNumbers);

}

double calculatePN(Node *stackNumbers) { // ���������� �������� �������
    Node *tempStack = nullptr;

    while (stackNumbers != nullptr) {
        string data = stackNumbers->value;
        if (isNumber(data)) {
            push(&tempStack, data);
        } else { // ����� �������� - ��� ��������
            double firstValue = stod(pop(&tempStack));
            double secondValue = stod(pop(&tempStack));
            if (isOperation(data, dictOperators)) {
                try {
                    push(&tempStack,to_string(action(firstValue, secondValue, data))); // to_string - ����������� double � string
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

double calculateRPN(Node *stackNumbers) { // ���������� �������� �������� �������
    Node *tempStack = nullptr;

    while (stackNumbers != nullptr) {
        string data = stackNumbers->value;
        if (isNumber(data)) {
            push(&tempStack, data);
        } else { // ����� �������� - ��� ��������
            double secondValue = stod(pop(&tempStack));
            double firstValue = stod(pop(&tempStack));
            if (isOperation(data, dictOperators)) {
                try {
                    push(&tempStack,
                         to_string(action(firstValue, secondValue, data))); // to_string - ����������� double � string
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
                "-- 1) Input infix form \n" // ������� � (pre/post)fix form + ������
                "-- 2) Input prefix (Polish) form \n" // ������
                "-- 3) Input postfix (reversePolish) form \n"; // ������


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