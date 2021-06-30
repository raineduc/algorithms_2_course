#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <queue>
#include <math.h>
#include <unordered_map>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::priority_queue;
using std::pow;
using std::unordered_map;

const int MAX_TIME = 50000 * 10001;

// key - node, value - transmission time
vector<std::pair<int, int>>
find_adjacent_nodes(const int64_t &phone, unordered_map<int64_t, int> &phones_map, vector<int> &times) {
    vector<std::pair<int, int>> nodes;
    string temp_string;
    int64_t num = phone;
    for (int i = 0; i < 10; i++) {
        int digit = num % 10;
        for (int j = 0; j < 10; j++) {
            int64_t new_phone = phone - (digit - j) * pow(10, i);
            if (new_phone != phone && phones_map.find(new_phone) != phones_map.end()) {
                nodes.emplace_back(phones_map[new_phone], times[10 - i - 1]);
            }
        }
        for (int j = i + 1; j < 10; j++) {
            auto d1 = (int64_t) (phone / pow(10, i)) % 10;
            auto d2 = (int64_t) (phone / pow(10, j)) % 10;
            int64_t new_phone = phone - (d1 - d2) * pow(10, i) - (d2 - d1) * pow(10, j);
            if (phones_map.find(new_phone) != phones_map.end()) {
                nodes.emplace_back(phones_map[new_phone], times[10 - j - 1]);
            }
        }
        num = num / 10;
    }
    return nodes;
}

int main() {
    int n;
    cin >> n;

    auto transmission_times = vector<int>(10);
    vector<int64_t> phone_numbers(n);
    unordered_map<int64_t, int> phones_map;
    // key - path len to node, value - node
    priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, std::greater<>> min_nodes;
    auto graph_costs = vector<int>(n, MAX_TIME);
    auto predecessors = vector<int>(n, -1);
    graph_costs[0] = 0;

    int tt;
    for (auto i = 0; i < 10; i++) {
        cin >> tt;
        transmission_times[i] = tt;
    }

    int64_t pn;
    for (auto i = 0; i < n; i++) {
        cin >> pn;
        phone_numbers[i] = pn;
        phones_map[pn] = i;
    }

    min_nodes.emplace(0, 0);
    while (!min_nodes.empty()) {
        int current_node = min_nodes.top().second;
        int cost = min_nodes.top().first;
        min_nodes.pop();
        if (graph_costs[current_node] != cost) {
            continue;
        }
        for (auto &adj_node: find_adjacent_nodes(phone_numbers[current_node], phones_map, transmission_times)) {
            if (graph_costs[current_node] + adj_node.second < graph_costs[adj_node.first]) {
                graph_costs[adj_node.first] = graph_costs[current_node] + adj_node.second;
                predecessors[adj_node.first] = current_node;
                min_nodes.push({graph_costs[adj_node.first], adj_node.first});
            }
        }
    }

    if (graph_costs[n - 1] < MAX_TIME) {
        cout << graph_costs[n - 1] << "\n";
        int count = 0;
        std::deque<int> path;
        int node = n - 1;
        while (node != -1) {
            count += 1;
            path.push_front(node);
            node = predecessors[node];
        }
        cout << count << "\n";
        for (auto elem: path) {
            cout << elem + 1 << " ";
        }
    } else {
        cout << -1;
    }
    return 0;
}
