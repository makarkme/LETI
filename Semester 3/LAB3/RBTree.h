#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stack>
#include <queue>

namespace RBTreeClass {
    struct Node {
        int value = 0;
        bool color = false; // true - красный, false - черный
        Node *left = nullptr;
        Node *right = nullptr;
    };

    class RBTree {
    private:
        Node *newItem(int value);

        Node *rotateToLeft(Node *node);

        Node *rotateToRight(Node *node);

        void balanceInsert(Node **root);

        bool balanceRemoveLeft(Node **root);

        bool balanceRemoveRight(Node **root);

        bool getColorMinRightSubtree(Node **rightDeleteNode, Node **deleteNode);

        void searchInOrderTravers(int value, const Node *node, bool &found); // симметричный обход (in-order)

    public:
        explicit RBTree() = default;

        void insert(int value, Node **root);

        bool remove(int value, Node **root);

        void deleteTree( Node **root);

        void search(int value, const Node *root);

        // void printTree(const Node *node, std::string const & prefix = "", bool root = true, bool last = true);
        void printTree(const Node *node, std::vector<std::string> const &lpref = std::vector<std::string>(),
                       std::vector<std::string> const &cpref = std::vector<std::string>(),
                       std::vector<std::string> const &rpref = std::vector<std::string>(), bool root = true,
                       bool left = true,
                       std::shared_ptr<std::vector<std::vector<std::string> > > lines = nullptr);

        void inputTree(const std::vector<std::string> &vectorInputData, Node **root);

        void printWidth(Node **root);

        void printPreOrder(Node **root);

        void printInOrder(Node **root);

        void printPostOrder(Node **root);

        ~RBTree() = default;
    };
}
