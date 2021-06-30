#include <iostream>
#include <list>
#include <vector>

using std::cin;
using std::cout;
using std::list;
using std::iterator;
using std::vector;

int main() {
    list<int> queue;
    int n;
    cin >> n;

    char command;
    int goblin;
    auto current_goblin = queue.end();
    int goblins_count = 0;

    vector<int> results;

    for (auto i = 0; i < n; i++) {
        cin >> command;
        if (command == '+') {
            cin >> goblin;
            queue.push_back(goblin);
            goblins_count += 1;

            if (goblins_count == 2) { // current pointer is queue.end() .
                current_goblin = queue.end();
                current_goblin--;
            } else if (goblins_count == 1) {
                current_goblin = queue.end();
            } else if (goblins_count % 2 == 1) {
                current_goblin++;
            }
        } else if (command == '*') {
            cin >> goblin;
            auto it = queue.insert(current_goblin, goblin);
            goblins_count += 1;

            current_goblin = it;

            if (goblins_count % 2 == 1) {
                current_goblin++;
            }
        } else if (command == '-') {
            results.push_back(queue.front());
            queue.pop_front();
            goblins_count -= 1;

            if (goblins_count % 2 == 1) {
                current_goblin++;
            }
        }
    }
    for (auto &result: results) {
        cout << result << "\n";
    }
    return 0;
}

