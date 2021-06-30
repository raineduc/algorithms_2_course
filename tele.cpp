#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <utility>
#include <unordered_map>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::unordered_map;

const int MAX_TIME = 10001;

// key - node, value - transmission time
vector<std::pair<int, int>> find_adjacent_nodes(const string& phone, unordered_map<string, int>& phones_map, vector<int>& times) {
    vector<std::pair<int, int>> nodes;
    string temp_string;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (j != i) {
                temp_string = phone;
                temp_string[i] = std::to_string(j).c_str()[0];
                if (phones_map.find(temp_string) != phones_map.end()) {
                    nodes.emplace_back(phones_map[temp_string], times[i]);
                }
                if (phone[i] != phone[j]) {
                    temp_string = phone;
                    temp_string[i] = phone[j];
                    temp_string[j] = phone[i];
                    if (phones_map.find(temp_string) != phones_map.end()) {
                        nodes.emplace_back(phones_map[temp_string], i < j ? times[i] : times[j]);
                    }
                }
            }
        }
    }
    return nodes;
}

int find_min_node(vector<bool>& visited_map, vector<int>& costs) {
    int min_node = -1;
    int min_cost = MAX_TIME;
    for (auto i = 0; i < visited_map.size(); i++) {
        if (!visited_map[i] && (costs[i] < min_cost || min_node == -1)) {
            min_node = i;
            min_cost = costs[i];
        }
    }
    return min_node;
}

int main() {
    int n;
    cin >> n;

    auto transmission_times = vector<int>(10);
    vector<string> phone_numbers;
    unordered_map<string, int> phones_map;
    auto visited_map = vector<bool>(n, false);
    auto graph_costs = vector<int>(n, MAX_TIME);
    auto predecessors = vector<int>(n, -1);
    graph_costs[0] = 0;

    int tt;
    for (auto i = 0; i < 10; i++) {
        cin >> tt;
        transmission_times[i] = tt;
    }

    string pn;
    for (auto i = 0; i < n; i++) {
        cin >> pn;
        phone_numbers.push_back(pn);
        phones_map[pn] = i;
    }

    int current_node = 0;
    for (auto i = 0; i < n; i++) {
        visited_map[current_node] = true;
        for (auto& adj_node: find_adjacent_nodes(phone_numbers[current_node], phones_map, transmission_times)) {
            if (!visited_map[adj_node.first]) {
                if (graph_costs[current_node] + adj_node.second < graph_costs[adj_node.first]) {
                    graph_costs[adj_node.first] = graph_costs[current_node] + adj_node.second;
                    predecessors[adj_node.first] = current_node;
                }
            }
        }
        current_node = find_min_node(visited_map, graph_costs);
    }

    if (graph_costs[n - 1] < MAX_TIME) {
        cout << graph_costs[n - 1] << "\n";
        int count = 0;
        std::deque<int> path;
        int node = n - 1;
        while(true) {
            count += 1;
            path.push_front(node);
            node = predecessors[node];
            if (node == -1) break;

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

