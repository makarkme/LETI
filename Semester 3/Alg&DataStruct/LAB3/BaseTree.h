#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stack>

namespace BaseTreeClass {
    struct Node {
        int value = 0;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    class BaseTree {
    private:
        Node *newItem(int value);

    public:
        explicit BaseTree() = default;

        void deleteTree(Node **root);

        // void printTree(const Node *node, std::string const & prefix = "", bool root = true, bool last = true);
        void printTree(const Node *node, std::vector<std::string> const &lpref = std::vector<std::string>(),
                       std::vector<std::string> const &cpref = std::vector<std::string>(),
                       std::vector<std::string> const &rpref = std::vector<std::string>(), bool root = true,
                       bool left = true,
                       std::shared_ptr<std::vector<std::vector<std::string> > > lines = nullptr);

        void inputTree(const std::vector<std::string> &vectorInputData, Node **root);

        void printPreOrder(Node **root);

        ~BaseTree() = default;
    };
}
