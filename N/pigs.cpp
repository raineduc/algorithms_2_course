#include <iostream>
#include <vector>
#include <list>

using std::cin;
using std::cout;
using std::vector;
using std::list;

enum Color {
    WHITE = 0,
    GRAY,
    BLACK
};

struct VisitedNode {
    Color color;
    int in_time;
};

typedef vector<list<int>> Graph;
typedef vector<VisitedNode> VisitedMap;

void DFS(const Graph& graph, VisitedMap& visited_map, int node, int& in_counter, int& components_counter) {
    visited_map[node].color = GRAY;
    visited_map[node].in_time = in_counter++;

    for (const auto& adjacent_node: graph[node]) {
        if (visited_map[adjacent_node].color == BLACK
        && visited_map[adjacent_node].in_time < visited_map[node].in_time) {
            components_counter -= 1;
        }
        if (visited_map[adjacent_node].color == WHITE) {
            DFS(graph, visited_map, adjacent_node, in_counter, components_counter);
        }
    }
    visited_map[node].color = BLACK;
}

int main() {
    int n;
    cin >> n;

    auto graph = Graph(n, list<int>());
    auto visited_map = VisitedMap(n, { .color = WHITE, .in_time = -1 });

    int bank;
    for (auto i = 0; i < n; i++) {
        cin >> bank;
        graph[bank - 1].push_back(i);
    }

    int in_counter = 0;
    int components_counter = 0;

    for (auto i = 0; i < n; i++) {
        if (visited_map[i].color == WHITE) {
            components_counter += 1;
            DFS(graph, visited_map, i, in_counter, components_counter);
        }
    }
    cout << components_counter;
    return 0;
}