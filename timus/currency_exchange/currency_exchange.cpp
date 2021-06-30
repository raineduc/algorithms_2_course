#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::list;

struct ExchangeOp {
    int from;
    int to;
    double rate;
    double commission;
};

typedef vector<list<ExchangeOp>> Graph;
typedef vector<double> GraphCosts;
typedef vector<bool> VisitedMap;

bool DFS_updateCosts(const Graph& graph, GraphCosts& costs, VisitedMap& visited_map, int node) {
    visited_map[node] = true;
    bool result = false;

    for (auto& op: graph[node]) {
        if (costs[node] >= op.commission) {
            auto last = costs[op.to];
            costs[op.to] = std::max(costs[op.to], (costs[node] - op.commission) * op.rate);
            if (last != costs[op.to]) result = true;
        }
        if (!visited_map[op.to] && costs[op.to] >= 0) {
            result = result || DFS_updateCosts(graph, costs, visited_map, op.to);
        }
    }
    return result;
}

bool updateCosts(const Graph& graph, GraphCosts& costs, int node) {
    auto visited_map = VisitedMap(graph.size(), false);
    return DFS_updateCosts(graph, costs, visited_map, node);
}

int main() {
    int n, m, s;
    double v;
    cin >> n >> m >> s;
    cin >> v;

    auto graph = Graph(n, list<ExchangeOp>());
    vector<ExchangeOp> edges;
    auto costs = GraphCosts(n, -1);
    costs[s - 1] = v;

    int a, b;
    double rab, cab, rba, cba;
    for (auto i = 0; i < m; i++) {
        cin >> a >> b;
        cin >> rab >> cab >> rba >> cba;
        graph[a - 1].push_back({ .from = a - 1, .to = b - 1, .rate = rab, .commission = cab });
        graph[b - 1].push_back({ .from = b - 1, .to = a - 1, .rate = rba, .commission = cba });
    }

    bool result;
    for (int i = 0; i < n; i++) {
        result = updateCosts(graph, costs, s - 1) && (i == n - 1);
    }
    cout << (result ? "YES" : "NO");
    return 0;
}
