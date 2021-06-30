#include <iostream>
#include <deque>
#include <utility>

using std::cin;
using std::cout;
using std::deque;
using std::pair;

int main() {
    int n, k;
    cin >> n >> k;

    deque<pair<int, int>> window;
    int current_number;

    for (int i = 0; i < n; i++) {
        cin >> current_number;

        if (!window.empty() && window.front().second <= (i - k)) {
            window.pop_front();
        }

        auto num = window.rbegin();
        while (!window.empty() && num->first >= current_number) {
            window.pop_back();
            num += 1;
        }

        window.emplace_back( current_number, i );
        if (i >= k - 1) {
            cout << window.front().first << " ";
        }
    }
    return 0;
}