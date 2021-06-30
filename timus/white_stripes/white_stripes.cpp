#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <array>

using std::cin;
using std::cout;
using std::vector;
using std::set;
using std::array;
using std::max;
using std::min;

bool has_free_col_neighbours(vector<set<int>> &table, int row, int col) {
    if (row > 0 && table[row - 1].find(col) == table[row - 1].end()) {
        return true;
    }
    if (row < table.size() - 1 && table[row + 1].find(col) == table[row + 1].end()) {
        return true;
    }
    return false;
}

// возвращает длины соседей
array<int, 2> get_free_row_neighbours(vector<set<int>> &table, int row, int col) {
    vector<int> result;
    auto elem = table[row].find(col);

    int left = elem != table[row].begin() ? *std::prev(elem) : -1l;
    int right = *std::next(elem);
    return { *elem - left - 1, right - *elem - 1 };
}

int split_interval(vector<set<int>> &table, int row, int col) {
    auto neighbours = get_free_row_neighbours(table, row, col);
    if (neighbours[0] == 0 && neighbours[1] == 0) {
        return has_free_col_neighbours(table, row, col) ? 0 : -1;
    }
    int result = 1;
    if (neighbours[0] == 0 || neighbours[0] == 1 && has_free_col_neighbours(table, row, col - 1)) {
        result -= 1;
    }
    if (neighbours[1] == 0 || neighbours[1] == 1 && has_free_col_neighbours(table, row, col + 1)) {
        result -= 1;
    }
    return result;
}

int main() {
    int m, n, k;
    cin >> m >> n;
    cin >> k;
    vector<set<int>> rows(m, { n });
    vector<set<int>> columns(n, { m });

    int result = min(m, n) > 1 ? m + n : 1;

    int i, j;
    for (int index = 0; index < k; index++) {
        cin >> i >> j;
        if (n > 1 || m == 1) {
            rows[i - 1].insert(j - 1);
            result += split_interval(rows, i - 1, j - 1);
        }
        if (m > 1) {
            columns[j - 1].insert(i - 1);
            auto neighbours = get_free_row_neighbours(columns, j - 1, i - 1);
            if (neighbours[0] == 0 && neighbours[1] == 0) continue; // уже проверяли в строках
            result += split_interval(columns, j - 1, i - 1);
        }
    }

    cout << result;

    return 0;
}

