#include "BaseTree.h"

BaseTreeClass::Node *BaseTreeClass::BaseTree::newItem(const int value) {
    const auto node = new Node;
    node->value = value;
    return node;
}

void BaseTreeClass::BaseTree::deleteTree(Node **root) {
    if (*root) {
        deleteTree(&(*root)->left);
        deleteTree(&(*root)->right);
        delete *root;
        *root = nullptr;
    }
}

// void TreeClass::BaseTree::printTree(const Node *node, std::string const &prefix, const bool root, const bool last) {
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

void BaseTreeClass::BaseTree::printTree(const Node *node, std::vector<std::string> const &lpref,
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
            for (const auto & i : out) {
                std::cout << i << std::endl;
            }
        }
    }
}

void BaseTreeClass::BaseTree::inputTree(const std::vector<std::string> &vectorInputData, Node **root) {
    *root = newItem(stoi(vectorInputData[1]));
    Node *curr = *root;
    std::stack<Node *> stackPrevs{};
    for (int i = 2; i < vectorInputData.size() - 1; ++i) {
        if (vectorInputData[i] == "(") {
            stackPrevs.push(curr);
            if (curr->left == nullptr) {
                curr->left = newItem(stoi(vectorInputData[i + 1]));
                curr = curr->left;
            } else {
                curr->right = newItem(stoi(vectorInputData[i + 1]));
                curr = curr->right;
            }
        }
        if (vectorInputData[i] == ")") {
            curr = stackPrevs.top();
            stackPrevs.pop();
        }
    }
}

void BaseTreeClass::BaseTree::printPreOrder(Node **root) {
    Node *curr = *root;
    if (curr == nullptr) {
        return;
    }
    std::cout << curr->value << " ";
    printPreOrder(&curr->left);
    printPreOrder(&curr->right);
}
