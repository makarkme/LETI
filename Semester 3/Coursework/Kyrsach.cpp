#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Edge {
private:
    char source, destination;
    int weight;

public:
    explicit Edge(const char s, const char d, const int w) : source(s), destination(d), weight(w) {
    }

    ~Edge() = default;

    void printEdge() const {
        std::cout << source << " -> " << destination << " : " << weight << "\n";
    }

    static bool compareEdges(const Edge edgeFirst, const Edge edgeSecond) {
        return edgeFirst.weight < edgeSecond.weight;
    }

    [[nodiscard]] char getSource() const {
        return source;
    }

    [[nodiscard]] char getDestination() const {
        return destination;
    }

    [[nodiscard]] int getWeight() const {
        return weight;
    }
};

std::vector<Edge> convertInputStringToData(const std::vector<std::string> &inputString) {
    std::vector<Edge> edges;
    std::vector<char> nodes;

    for (int i = 0; i < size(inputString); ++i) {
        int indexForDestination = 0;
        for (int j = 0; j < size(inputString[i]); ++j) {
            if (isalpha(inputString[i][j])) {
                nodes.push_back(inputString[i][j]);
            }
            if (isdigit(inputString[i][j])) {
                if (const int weight = inputString[i][j] - '0'; weight != 0) {
                    edges.emplace_back(nodes[i - 1], nodes[indexForDestination], weight);
                }
                indexForDestination += 1;
            }
        }
    }
    return edges;
}

// Функция для нахождения минимального остовного дерева с помощью алгоритма Краскала
void findMinSpanningTree(std::vector<Edge> &edges, const std::vector<std::string> &inputString) {
    int numberVertices = 0;
    for (const auto & i : inputString) {
        for (const char j : i) {
            if (isalpha(j)) {
                numberVertices += 1;
            }
        }
    }

    std::ranges::sort(edges, Edge::compareEdges);
    std::map<char, int> vertexIndex; // Сопоставление каждой вершины с индексом
    int index = 0;
    for (const auto& edge : edges) {
        if (!vertexIndex.contains(edge.getSource())) { // Если вершина еще не map, то добавляем её
            vertexIndex[edge.getSource()] = index++;
        }
        if (!vertexIndex.contains(edge.getDestination())) {
            vertexIndex[edge.getDestination()] = index++;
        }
    }

    std::vector<int> parent(numberVertices, -1); // Создание массива для хранения родителей вершин
    std::vector<Edge> minSpanningTree; // Создание пустого остовного дерева
    int numEdgesAdded = 0;

    for (Edge edge : edges) { // Поиск родителей вершин, соединяемых данным ребром
        const int source = vertexIndex[edge.getSource()];
        const int destination = vertexIndex[edge.getDestination()];

        int sourceParent = source;
        int destinationParent = destination;

        while (parent[sourceParent] != -1) {
            sourceParent = parent[sourceParent];
        }
        while (parent[destinationParent] != -1) {
            destinationParent = parent[destinationParent];
        }

        if (sourceParent != destinationParent) { // Проверка наличия цикла
            minSpanningTree.push_back(edge);
            numEdgesAdded++;

            parent[destinationParent] = sourceParent; // Объединение вершин в одно дерево
        }

        // Прекращение алгоритма после добавления всех вершин в остовное дерево
        if (numEdgesAdded == numberVertices - 1) {
            break;
        }
    }

    // Вывод минимального остовного дерева
    std::cout << "Result:" << "\n";
    int resultWeight = 0;
    for (Edge edge : minSpanningTree) {
        std::cout << edge.getSource() << " -- " << edge.getDestination() << "\n";
        resultWeight += edge.getWeight();
    }
    std::cout << resultWeight << "\n";

}

int main() {
    std::vector<std::string> inputString;
    if (std::ifstream file("E://ClionProjects//input.txt"); file.is_open()) {
        std::string localString;
        while (std::getline(file, localString)) {
            inputString.push_back(localString);
        }
        file.close();
    } else {
        std::cout << "File is not open" << "\n";
    }

    std::vector<Edge> edges = convertInputStringToData(inputString);

    // std::ranges::sort(edges, Edge::compareEdges);
    // for (auto edge : edges) {
    //     edge.printEdge();
    // }

    findMinSpanningTree(edges, inputString);
}