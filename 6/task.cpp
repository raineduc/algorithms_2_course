#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::min;
using std::sort;

//зачем я все это делал...
bool compareLines(const string & line1, const string & line2) {
    auto min_len = min(line1.length(), line2.length());
    // проверяем, что начало бОльшей строки содержит меньшую
    for (auto i = 0; i < min_len; i++) {
        if (line1[i] != line2[i]) {
            return line1[i] > line2[i];
        }
    }
    if (line1.length() > min_len) {
        for (auto i = min_len; i < line1.length(); i++) {
            if (line1[i] != line1[i - min_len]) {
                return line1[i] > line1[i - min_len]; // если true, то line1 + line2 - большее число
            }
        }
        auto line1_len = line1.length();
        // проверяем остаток строки line1 + line2 (остаток line2)
        for (auto i = 0; i < min_len; i++) {
            if (line2[i] != line1[line1_len - (min_len - i)]) {
                return line2[i] > line1[line1_len - (min_len - i)];
            }
        }
    }
    if (line2.length() > min_len) {
        for (auto i = min_len; i < line2.length(); i++) {
            if (line2[i] != line2[i - min_len]) {
                return line2[i] < line2[i - min_len]; // если true, то line1 + line2 - большее число
            }
        }
        auto line2_len = line2.length();
        // проверяем остаток строки line2 + line1 (остаток line1)
        for (auto i = 0; i < min_len; i++) {
            if (line1[i] != line2[line2_len - (min_len - i)]) {
                return line1[i] < line2[line2_len - (min_len - i)];
            }
        }
    }
    return false;
}

int main() {
    string line;
    vector<string> lines;
    while (cin >> line) {
        lines.push_back(line);
    }
    sort(lines.begin(), lines.end(), compareLines);
    for (const auto& l : lines) {
        cout << l;
    }
    cout << "\n";
    return 0;
}

