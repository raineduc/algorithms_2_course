#include <iostream>
#include <vector>
#include <list>

using std::cin;
using std::cout;
using std::vector;
using std::list;

const int MAX_WEIGHT = 10e9;

enum Color {
    WHITE = 0,
    GRAY,
    BLACK
};

typedef vector<vector<int>> Graph;
typedef vector<Color> VisitedMap;

int doBFS(const Graph& graph, VisitedMap& visited_map, int node, int max_weight) {
    visited_map[node] = GRAY;
    int count = 1;

    for (auto i = 0; i < graph.size(); i++) {
        if (visited_map[i] == WHITE && graph[node][i] <= max_weight) {
            count += doBFS(graph, visited_map, i, max_weight);
        }
    }
    visited_map[node] = BLACK;
    return count;
}

int BFS_count_nodes(const Graph& graph, int node, int max_weight) {
    auto visited_map = VisitedMap(graph.size(), WHITE);
    return doBFS(graph, visited_map, node, max_weight);
}

int search_weight(const Graph& graph, const Graph& inverted_graph, int start_weight, int max_weight) {
    if (start_weight == max_weight) return start_weight;
    const auto n = graph.size();
    const auto half = (max_weight - start_weight) / 2;

    if (BFS_count_nodes(graph, 0, start_weight + half) == n
    && BFS_count_nodes(inverted_graph, 0, start_weight + half) == n) {
        return search_weight(graph, inverted_graph, start_weight, start_weight + half);
    }
    return search_weight(graph, inverted_graph, half == 0 ? max_weight : start_weight + half, max_weight);
}

int main() {
    int n;
    cin >> n;

    auto graph = Graph(n, vector<int>(n));
    auto inverted_graph = Graph(n, vector<int>(n));

    int edge;
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            cin >> edge;
            graph[i][j] = edge;
            inverted_graph[j][i] = edge;
        }
    }

    cout << search_weight(graph, inverted_graph, 0, MAX_WEIGHT);

    return 0;
}
