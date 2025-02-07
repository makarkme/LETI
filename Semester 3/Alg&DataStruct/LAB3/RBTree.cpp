#include "RBTree.h"

RBTreeClass::Node *RBTreeClass::RBTree::newItem(const int value) {
    const auto node = new Node;
    node->value = value;
    node->color = true;
    return node;
}

RBTreeClass::Node *RBTreeClass::RBTree::rotateToLeft(Node *node) {
    Node *right = node->right;
    Node *rightLeft = right->left;
    right->left = node;
    node->right = rightLeft;
    return right;
}

RBTreeClass::Node *RBTreeClass::RBTree::rotateToRight(Node *node) {
    Node *left = node->left;
    Node *leftRight = left->right;
    left->right = node;
    node->left = leftRight;
    return left;
}

void RBTreeClass::RBTree::balanceInsert(Node **root) {
    Node *nextLeft, *nextRight;
    Node *node = *root;
    if (node->color) {
        return;
    }
    Node *left = node->left;
    Node *right = node->right;

    if (left and left->color) {
        // находим 2 красные вершины подряд
        nextRight = left->right;
        if (nextRight and nextRight->color) {
            left = node->left = rotateToLeft(left); // поворачиваем
        }
        nextLeft = left->left;
        if (nextLeft and nextLeft->color) {
            node->color = true; // красим, чтоб соответствовало КЧ
            left->color = false;
            if (right and right->color) {
                // красим оставшуюся часть дерева
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

void RBTreeClass::RBTree::insert(const int value, Node **root) {
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

bool RBTreeClass::RBTree::balanceRemoveLeft(Node **root) {
    Node *node = *root;
    Node *left = node->left;
    Node *right = node->right;
    Node *rightLeft = right->left;
    Node *rightRight = right->right;

    if (left and left->color) {
        // если была убрана красная вершина (ситуация 0)
        left->color = false;
        return false;
    }
    if (right and right->color) {
        // если удалённая вершина имеет красного брата (ситуация 1)
        node->color = true;
        right->color = false;
        node = *root = rotateToLeft(node);
        if (balanceRemoveLeft(&node->left)) {
            node->left->color = false;
        }
        return false;
    }

    if ((!rightLeft or !rightLeft->color) and (!rightRight or
                                               !rightRight->color)) {
        // если удалённая вершина имеет чёрного брата с чёрными потомками (ситуация 2)
        right->color = true;
        return true;
    }

    if (rightLeft and
        rightLeft->color) {
        // если удалённая вершина имеет чёрного брата, у которого красный левый (ситуация 3)
        right->color = true;
        rightLeft->color = false;
        right = node->right = rotateToRight(right);
        rightRight = right->right;
    }

    if (rightRight and
        rightRight->color) {
        // если удалённая вершина имеет чёрного брата, у которого красный правый (ситуация 4)
        right->color = node->color;
        rightRight->color = node->color = false;
        *root = rotateToLeft(node);
    }

    return false;
}

bool RBTreeClass::RBTree::balanceRemoveRight(Node **root) {
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

bool RBTreeClass::RBTree::getColorMinRightSubtree(Node **rightDeleteNode, Node **deleteNode) {
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


bool RBTreeClass::RBTree::remove(const int value, Node **root) {
    Node *node = *root;
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
            if (!node->right) {
                // используется именно right, ибо при удалении в некоторых случаях берется именно правый элемент на замену
                *root = node->left;
                // за отсутствием правого сразу берется оставшийся (позже рекурсивно всё перепривязывается)
                color = !node->color;
                delete node;
                return color;
            } else {
                color = getColorMinRightSubtree(&node->right,
                                                root);
                // нужно для рассмотрения случая с 2 детьми (чтоб выбрать, кто будет на замену)
                Node *tempNode = *root; // теперь tempNode - это нода, которая пришла на замену удаляемой
                tempNode->color = node->color;
                tempNode->left = node->left;
                tempNode->right = node->right;
                delete node;
                if (color) {
                    // по-умолчанию красный - значит нужна балансировка
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

void RBTreeClass::RBTree::deleteTree(Node **root) {
    if (*root) {
        deleteTree(&(*root)->left);
        deleteTree(&(*root)->right);
        delete *root;
        *root = nullptr;
    }
}

void RBTreeClass::RBTree::search(const int value, const Node *root) {
    bool found = false;
    searchInOrderTravers(value, root, found);

    if (!found) {
        std::cout << "Not found value." << "\n";
    }
}

void RBTreeClass::RBTree::searchInOrderTravers(const int value, const Node *node, bool &found) {
    if (node) {
        searchInOrderTravers(value, node->left, found);
        if (node->value == value) {
            found = true;
            std::cout << "Found value." << "\n";
            return;
        }
        searchInOrderTravers(value, node->right, found);
    }
}


// void RBTreeClass::RBTree::printTree(const Node *node, std::string const &prefix, const bool root, const bool last) {
//
//     static std::string ch_hor = "\u2500" /*─*/, ch_ver = "\u2502" /*│*/, ch_ddia = "\u250C" /*┌*/, ch_rddia = "\u2510"
//             /*┐*/, ch_udia = "\u2514" /*└*/, ch_ver_hor = "\u251C\u2500" /*├─*/, ch_udia_hor = "\u2514\u2500" /*└─*/,
//             ch_ddia_hor = "\u250C\u2500" /*┌─*/, ch_ver_spa = "\u2502 " /*│ */;
//
//     std::cout << prefix << (root ? "" : (last ? ch_udia_hor : ch_ver_hor)) << (node ? std::to_string(node->value) : "")
//             << std::endl;
//     if (!node || (!node->left && !node->right))
//         return;
//     const std::vector v{node->left, node->right};
//     for (size_t i = 0; i < v.size(); ++i)
//         printTree(v[i], prefix + (root ? "" : (last ? "  " : ch_ver_spa)), false, i + 1 >= v.size());
// }

void RBTreeClass::RBTree::printTree(const Node *node, std::vector<std::string> const &lpref,
                                    std::vector<std::string> const &cpref,
                                    std::vector<std::string> const &rpref, const bool root, const bool left,
                                    std::shared_ptr<std::vector<std::vector<std::string> > > lines) {
    static std::string ch_hor = "\u2500" /*─*/, ch_ver = "\u2502" /*│*/, ch_ddia = "\u250C" /*┌*/, ch_rddia = "\u2510"
            /*┐*/, ch_udia = "\u2514" /*└*/, ch_ver_hor = "\u251C\u2500" /*├─*/, ch_udia_hor = "\u2514\u2500" /*└─*/,
            ch_ddia_hor = "\u250C\u2500" /*┌─*/, ch_ver_spa = "\u2502 " /*│ */;

    if (node) {
        auto VSCat = [](std::vector<std::string> const &a, std::vector<std::string> const &b) {
            auto r = a;
            r.insert(r.end(), b.begin(), b.end());
            return r;
        };
        if (root) lines = std::make_shared<std::vector<std::vector<std::string> > >();
        if (node->left)
            printTree(node->left, VSCat(lpref, std::vector<std::string>({" ", " "})),
                      VSCat(lpref, std::vector<std::string>({ch_ddia, ch_ver})),
                      VSCat(lpref, std::vector<std::string>({ch_hor, " "})), false, true,
                      lines);
        const auto sval = std::to_string(node->value);
        const size_t sm = left or sval.empty() ? sval.size() / 2 : ((sval.size() + 1) / 2 - 1);
        for (size_t i = 0; i < sval.size(); ++i)
            lines->push_back(VSCat(i < sm ? lpref : i == sm ? cpref : rpref, {std::string(1, sval[i])}));
        if (node->right)
            printTree(node->right, VSCat(rpref, std::vector<std::string>({ch_hor, " "})),
                      VSCat(rpref, std::vector<std::string>({ch_rddia, ch_ver})),
                      VSCat(rpref, std::vector<std::string>({" ", " "})), false, false, lines);
        if (root) {
            std::vector<std::string> out;
            for (size_t l = 0;; ++l) {
                bool last = true;
                std::string line;
                for (size_t i = 0; i < lines->size(); ++i)
                    if (l < (*lines).at(i).size()) {
                        line += lines->at(i)[l];
                        last = false;
                    } else line += " ";
                if (last) break;
                out.push_back(line);
            }
            for (const auto &i: out) {
                std::cout << i << std::endl;
            }
        }
    }
}

void RBTreeClass::RBTree::inputTree(const std::vector<std::string> &vectorInputData, Node **root) {
    bool isNumber = false;
    for (const auto &element: vectorInputData) {
        try {
            std::stoi(element);
            isNumber = true;
        } catch (const std::invalid_argument &) {
            isNumber = false;
        } catch (const std::out_of_range &) {
            isNumber = false;
        }

        if (isNumber) {
            insert(stoi(element), root);
            if (*root) {
                // старт балансировки
                (*root)->color = false;
            }
        }
    }
}

void RBTreeClass::RBTree::printWidth(Node **root) {
    if (root == nullptr or *root == nullptr) {
        return;
    }
    std::queue<Node *> rootQueue;
    rootQueue.push(*root);
    while (!rootQueue.empty()) {
        const Node *curr = rootQueue.front();
        rootQueue.pop();
        std::cout << curr->value << " ";
        if (curr->left) {
            rootQueue.push(curr->left);
        }
        if (curr->right) {
            rootQueue.push(curr->right);
        }
    }
}

void RBTreeClass::RBTree::printPreOrder(Node **root) {
    Node *curr = *root;
    if (curr == nullptr) {
        return;
    }
    std::cout << curr->value << " ";
    printPreOrder(&curr->left);
    printPreOrder(&curr->right);
}

void RBTreeClass::RBTree::printInOrder(Node **root) {
    Node *curr = *root;
    if (curr == nullptr) {
        return;
    }
    printInOrder(&curr->left);
    std::cout << curr->value << " ";
    printInOrder(&curr->right);
}

void RBTreeClass::RBTree::printPostOrder(Node **root) {
    Node *curr = *root;
    if (curr == nullptr) {
        return;
    }
    printPostOrder(&curr->left);
    printPostOrder(&curr->right);
    std::cout << curr->value << " ";
}
