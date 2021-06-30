#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using std::cin;
using std::cout;
using std::map;
using std::string;
using std::pair;
using std::vector;
using std::pair;
using std::reverse;
using std::make_pair;

int main() {
    int k;
    string line;

    cin >> k;
    cin >> line;

    map<char,int> chars_count;
    // для каждой буквы сопоставляет индекс среди таких же букв
    vector<pair<char,int>> line_indeces;

    for (char c: line) {
        if (chars_count.find(c) == chars_count.end()) {
            chars_count[c] = 1;
        } else {
            chars_count[c] += 1;
        }
        line_indeces.emplace_back(c, chars_count[c] - 1);
    }

    // для каждой буквы указывает начальный индекс, в chars_count хранится количество букв
    map<char, int> ordered_letters;

    int index = 0;
    for (auto const &c: chars_count) {
        ordered_letters[c.first] = index;
        index += c.second;
    }

    string new_line;
    int next_index = k - 1;
    for (int i = 0; i < line.length(); i++) {
        new_line.push_back(line[next_index]);
        next_index = ordered_letters[line[next_index]] + line_indeces[next_index].second;
    }
    reverse(new_line.begin(), new_line.end());
    cout << new_line;

    return 0;
}

