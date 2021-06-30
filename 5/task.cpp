#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int find_max_min_range(const int *stalls, int stalls_len, int cow_count, int min_range, int max_range) {
    if (min_range == max_range) {
        return max_range;
    }
    int placed_cow_count = 1;
    int current_stall = stalls[0];
    const int current_range = ((max_range - min_range) / 2) == 0 ? max_range : (max_range + min_range) / 2;
    for (auto i = 0; i < stalls_len; i++) {
        if (stalls[i] - current_stall >= current_range) {
            placed_cow_count += 1;
            current_stall = stalls[i];
        }
    }

    if (placed_cow_count >= cow_count) {
        return find_max_min_range(stalls, stalls_len, cow_count, current_range, max_range);
    }
    return find_max_min_range(stalls, stalls_len, cow_count, min_range, current_range - 1);
}

int main() {
    int n; // стойла
    int k; // коровы
    cin >> n;
    cin >> k;
    int *stalls = new int[n];
    for (auto i = 0; i < n; i++) {
        cin >> stalls[i];
    }
    int max_range = stalls[n - 1] - stalls[0];
    int result = find_max_min_range(stalls, n, k, 1, max_range);
    cout << result;
    delete [] stalls;
    return 0;
}