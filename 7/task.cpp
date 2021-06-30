#include <iostream>
#include <unordered_map>
#include <map>
#include <string>

using std::cin;
using std::cout;
using std::pair;
using std::multimap;
using std::map;
using std::unordered_map;
using std::string;

bool does_pair_exist(multimap<int, char> &map, int &key, char &value) {
    for (auto pos = map.find(key); pos->first == key && pos != map.end(); pos++) {
        if (pos->second == value) {
            return true;
        }
    }
    return false;
}

int main() {
    unordered_map<char, int> weights;
    map<char, int> letter_count_map;
    multimap<int, char> pairs;
    string str;
    cin >> str;

    int weight;
    char current_letter = 'a';
    for (int i = 0; i < 26; i++) {
        cin >> weight;
        weights[current_letter] = weight;
        current_letter += 1;
    }
    for (auto letter : str) {
        if (letter_count_map.find(letter) != letter_count_map.end()) {
            if (does_pair_exist(pairs, weights[letter], letter)) {
                letter_count_map[letter] += 1;
                continue;
            }
            pairs.insert({ weights[letter], letter });
            letter_count_map[letter] -= 1;
        } else {
            letter_count_map[letter] = 1;
        }
    }
    for (auto pos = pairs.rbegin(); pos != pairs.rend(); pos++) {
        cout << pos->second;
    }
    for (auto & pos : letter_count_map) {
        cout << string(pos.second, pos.first);
    }
    for (auto & pos: pairs) {
        cout << pos.second;
    }
    return 0;
}