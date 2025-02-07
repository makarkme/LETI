#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <memory>
#include <windows.h>

using namespace std;

struct Node { // узел
    int value = 0;
    bool color = false; // true - красный, false - черный
    Node *left = nullptr;
    Node *right = nullptr;

};


Node *newItem(int value) { // добавление узла
    Node *node = new Node;
    node->value = value;
    node->color = true;
    return node;
}

void deleteTree(Node *root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

static string ch_hor = "\u2500", ch_ver = "\u2502", ch_ddia = "\u250C", ch_rddia = "\u2510"; // спец.символы в unicode
void
printTree(Node *node, vector<string> const &lpref = vector<string>(), vector<string> const &cpref = vector<string>(),
          vector<string> const &rpref = vector<string>(), bool root = true, bool left = true,
          shared_ptr<vector<vector<string>>> lines = nullptr) {
    if (node) {
        auto VSCat = [](vector<string> const &a, vector<string> const &b) {
            auto r = a;
            r.insert(r.end(), b.begin(), b.end());
            return r;
        };
        if (root) lines = make_shared<vector<vector<string>>>();
        if (node->left)
            printTree(node->left, VSCat(lpref, vector<string>({" ", " "})),
                      VSCat(lpref, vector<string>({ch_ddia, ch_ver})),
                      VSCat(lpref, vector<string>({ch_hor, " "})), false, true,
                      lines);
        auto sval = to_string(node->value);
        size_t sm = left or sval.empty() ? sval.size() / 2 : ((sval.size() + 1) / 2 - 1);
        for (size_t i = 0; i < sval.size(); ++i)
            lines->push_back(VSCat(i < sm ? lpref : i == sm ? cpref : rpref, {string(1, sval[i])}));
        if (node->right)
            printTree(node->right, VSCat(rpref, vector<string>({ch_hor, " "})),
                      VSCat(rpref, vector<string>({ch_rddia, ch_ver})),
                      VSCat(rpref, vector<string>({" ", " "})), false, false, lines);
        if (root) {
            vector<string> out;
            for (size_t l = 0;; ++l) {
                bool last = true;
                string line;
                for (size_t i = 0; i < lines->size(); ++i)
                    if (l < (*lines).at(i).size()) {
                        line += lines->at(i)[l];
                        last = false;
                    } else line += " ";
                if (last) break;
                out.push_back(line);
            }
            for (size_t i = 0; i < out.size(); ++i)
                cout << out[i] << endl;
        }
    }
}

Node *rotateToLeft(Node *node) { // вращение влево (ситуация 3)
    Node *right = node->right;
    Node *rightLeft = right->left;
    right->left = node;
    node->right = rightLeft;
    return right;
}

Node *rotateToRight(Node *node) { // вращение вправо (ситуация 3)
    Node *left = node->left;
    Node *leftRight = left->right;
    left->right = node;
    node->left = leftRight;
    return left;
}

void balanceInsert(Node **root) {
    Node *left, *right, *nextLeft, *nextRight;
    Node *node = *root;
    if (node->color) {
        return;
    }
    left = node->left;
    right = node->right;

    if (left and left->color) { // находим 2 красные вершины подряд
        nextRight = left->right;
        if (nextRight and nextRight->color) {
            left = node->left = rotateToLeft(left); // поворачиваем
        }
        nextLeft = left->left;
        if (nextLeft and nextLeft->color) {
            node->color = true; // красим, чтоб соответствовало КЧ
            left->color = false;
            if (right and right->color) { // красим оставшуюся часть дерева
                nextLeft->color = true;
                right->color = false;
                return;
            }
            *root = rotateToRight(node);
        }
    }

    // то же самое, только вправо
    if (right and right->color) {
        nextLeft = right->left;
        if (nextLeft and nextLeft->color) {
            right = node->right = rotateToRight(right);
        }
        nextRight = right->right;
        if (nextRight and nextRight->color) {
            node->color = true;
            right->color = false;
            if (left and left->color) {
                nextRight->color = true;
                left->color = false;
                return;
            }
            *root = rotateToLeft(node);
        }
    }
}

void insert(int value, Node **root) {
    Node *node = *root;
    if (node) {
        if (value < node->value) {
            insert(value, &node->left);
        }
        if (value > node->value) {
            insert(value, &node->right);
        }
        balanceInsert(root);
    } else {
        *root = newItem(value);
    }
}

bool balanceRemoveLeft(Node **root) { // балансировка для левой стороны
    Node *node = *root;
    Node *left = node->left;
    Node *right = node->right;
    Node *rightLeft = right->left;
    Node *rightRight = right->right;

    if (left and left->color) { // если была убрана красная вершина (ситуация 0)
        left->color = false;
        return false;
    }
    if (right and right->color) { // если удалённая вершина имеет красного брата (ситуация 1)
        node->color = true;
        right->color = false;
        node = *root = rotateToLeft(node);
        if (balanceRemoveLeft(&node->left)) {
            node->left->color = false;
        }
        return false;
    }

    if ((!rightLeft or !rightLeft->color) and (!rightRight or
                                               !rightRight->color)) { // если удалённая вершина имеет чёрного брата с чёрными потомками (ситуация 2)
        right->color = true;
        return true;
    }

    if (rightLeft and
        rightLeft->color) { // если удалённая вершина имеет чёрного брата, у которого красный левый (ситуация 3)
        right->color = true;
        rightLeft->color = false;
        right = node->right = rotateToRight(right);
        rightRight = right->right;
    }

    if (rightRight and
        rightRight->color) { // если удалённая вершина имеет чёрного брата, у которого красный правый (ситуация 4)
        right->color = node->color;
        rightRight->color = node->color = false;
        *root = rotateToLeft(node);
    }

    return false;
}

bool balanceRemoveRight(Node **root) { // тут всё аналогично
    Node *node = *root;
    Node *left = node->left;
    Node *right = node->right;
    Node *leftLeft = left->left;
    Node *leftRight = left->right;

    if (right and right->color) {
        right->color = false;
        return false;
    }

    if (left and left->color) {
        node->color = true;
        left->color = false;
        node = *root = rotateToRight(node);
        if (balanceRemoveRight(&node->right)) {
            node->right->color = false;
        }
        return false;
    }

    if ((!leftRight or !leftRight->color) and (!leftLeft or !leftLeft->color)) {
        left->color = true;
        return true;
    }

    if (leftRight and leftRight->color) {
        left->color = true;
        leftRight->color = false;
        left = node->left = rotateToLeft(left);
        leftLeft = left->left;
    }

    if (leftLeft and leftLeft->color) {
        left->color = node->color;
        leftLeft->color = node->color = false;
        *root = rotateToRight(node);
    }

    return false;
}

bool getColorMinRightSubtree(Node **rightDeleteNode, Node **deleteNode) {
    Node *node = *rightDeleteNode;
    if (node->left) {
        if (getColorMinRightSubtree(&node->left, deleteNode)) {
            return balanceRemoveLeft(rightDeleteNode);
        }
    } else {
        *rightDeleteNode = node->right;
        *deleteNode = node;
        return !node->color;
    }
    return false; // выполняется, когда left закончились; завершает рекурсию
}

bool remove(int value, Node **root) {
    Node *tempNode, *node = *root;
    if (node) {
        if (value > node->value) {
            if (remove(value, &node->right)) {
                return balanceRemoveRight(root);
            }
        } else if (value < node->value) {
            if (remove(value, &node->left)) {
                return balanceRemoveLeft(root);
            }
        } else {
            bool color; // по-умолчанию false
            if (!node->right) { // используется именно right, ибо при удалении в некоторых случаях берется именно правый элемент на замену
                *root = node->left; // за отсутствием правого сразу берется оставшийся (позже рекурсивно всё перепривязывается)
                color = !node->color;
                delete node;
                return color;
            } else {
                color = getColorMinRightSubtree(&node->right,
                                                root); // нужно для рассмотрения случая с 2 детьми (чтоб выбрать, кто будет на замену)
                tempNode = *root; // теперь tempNode - это нода, которая пришла на замену удаляемой
                tempNode->color = node->color;
                tempNode->left = node->left;
                tempNode->right = node->right;
                delete node;
                if (color) { // по-умолчанию красный - значит нужна балансировка
                    color = balanceRemoveRight(root);
                }
                return color;
            }
        }
        return false;
    } else {
        return false;
    }
}

void searchInOrderTravers(int value, Node *node, bool &found) { // симметричный обход
    if (node) {
        searchInOrderTravers(value, node->left, found);
        if (node->value == value) {
            found = true;
            cout << "Found value." << "\n";
            return;
        }
        searchInOrderTravers(value, node->right, found);
    }
}

void search(int value, Node *root) {
    bool found = false;
    searchInOrderTravers(value, root, found);

    if (!found) {
        cout << "Not found value." << "\n";
    }
}

int main() {
    SetConsoleOutputCP(65001);
    Node *rootTree = nullptr;


    while (true) {
        cout << "Commands: \n"
                "-- 0) Exit \n"
                "-- 1) Input random \n"
                "-- 2) Input data \n"
                "-- 3) Insert value \n"
                "-- 4) Remove value \n"
                "-- 5) Search value \n";

        string inputData;
        int sizeArray;
        int *array;
        string localString;
        int localIndex;
        int inputValue;

        chrono::time_point<chrono::steady_clock, chrono::duration<long long, ratio<1, 1000000000>>> startTime;
        chrono::time_point<chrono::steady_clock, chrono::duration<long long, ratio<1, 1000000000>>> endTime;

        int condition;
        cin >> condition;
        switch (condition) {
            case 0:
                deleteTree(rootTree);
                exit(0);
            case 1: // заполнение кч рандом-числами
                cout << "Input quantity numbers: " << "\n";
                cin >> sizeArray;

                deleteTree(rootTree);
                rootTree = nullptr;

                startTime = chrono::steady_clock::now();
                for (int i = 0; i < sizeArray; ++i) {
                    int value = rand() % (100 - (-100) + 1) + (-100);
                    insert(value, &rootTree);
                    if (rootTree) { // старт балансировки
                        rootTree->color = false;
                    }
                }
                endTime = chrono::steady_clock::now();

                printTree(rootTree);
                cout << "Work time for input: "
                     << chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << "ns\n";

                break;

            case 2: // заполнение кч пользователем через список
                cout << "Input data: " << "\n";

                cin.ignore();
                getline(cin, inputData);
                inputData += " "; // "" - нужно, чтоб записать последний символ

                sizeArray = 0;
                for (int i = 0; i < inputData.size(); ++i) { // узнаём длину массива
                    if (inputData[i] == ' ') {
                        sizeArray += 1;
                    }
                }

                array = new int[sizeArray];
                localIndex = 0;
                for (int i = 0; i < inputData.size(); ++i) {
                    if (inputData[i] != ' ') {
                        localString.push_back(inputData[i]);
                    } else {
                        array[localIndex] = stoi(localString); // преобразование str в int
                        localString = "";
                        localIndex += 1;
                    }
                }

                deleteTree(rootTree);
                rootTree = nullptr;

                startTime = chrono::steady_clock::now();
                for (int i = 0; i < sizeArray; ++i) {
                    insert(array[i], &rootTree);
                    if (rootTree) { // старт балансировки
                        rootTree->color = false;
                    }
                }
                endTime = chrono::steady_clock::now();

                printTree(rootTree);
                cout << "Work time for input: "
                     << chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << "ns\n";

                delete[] array;
                break;

            case 3: // вставка
                cout << "Input value for insert: " << "\n";
                cin >> inputValue;

                startTime = chrono::steady_clock::now();
                insert(inputValue, &rootTree);
                endTime = chrono::steady_clock::now();

                printTree(rootTree);
                cout << "Work time for insert: "
                     << chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << "ns\n";

                break;
            case 4: // удаление
                cout << "Input value for remove: " << "\n";
                cin >> inputValue;

                startTime = chrono::steady_clock::now();
                remove(inputValue, &rootTree);
                endTime = chrono::steady_clock::now();

                printTree(rootTree);
                cout << "Work time for remove: "
                     << chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << "ns\n";

                break;
            case 5: // поиск
                cout << "Input value for search: " << "\n";
                cin >> inputValue;

                startTime = chrono::steady_clock::now();
                search(inputValue, rootTree);
                endTime = chrono::steady_clock::now();

                printTree(rootTree);
                cout << "Work time for search: "
                     << chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << "ns\n";

                break;
            default:
                continue;
        }
    }
}