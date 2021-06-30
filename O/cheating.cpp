#include <iostream>
#include <vector>
#include <list>

using std::cin;
using std::cout;
using std::vector;
using std::list;

enum Color {
    WHITE = 0,
    BLUE,
    RED
};

struct VisitedNode {
    Color color;
};

typedef vector<list<int>> Graph;
typedef vector<VisitedNode> VisitedMap;

bool DFS_is_bipartite_graph(const Graph& graph, VisitedMap& visited_map, int node, Color color) {
    visited_map[node].color = color;

    for (const auto& adjacent_node: graph[node]) {
        if (visited_map[adjacent_node].color == visited_map[node].color) {
            return false;
        }
        if (visited_map[adjacent_node].color == WHITE) {
            if (!DFS_is_bipartite_graph(graph, visited_map, adjacent_node, color == BLUE ? RED : BLUE)) {
                return false;
            };
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    auto graph = Graph(n, list<int>());
    auto visited_map = VisitedMap(n, { .color = WHITE });

    int left, right;
    for (auto i = 0; i < m; i++) {
        cin >> left >> right;
        graph[left - 1].push_back(right - 1);
        graph[right - 1].push_back(left - 1);
    }

    bool result = false;
    for (auto i = 0; i < n; i++) {
        if (visited_map[i].color == WHITE) {
            result = DFS_is_bipartite_graph(graph, visited_map, i, RED);
            if (!result) {
                break;
            }
        }
    }
    if (result) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}

