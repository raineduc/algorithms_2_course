#include <iostream>

using std::cin;
using std::cout;

int main() {
    int n;
    cin >> n;
    int p;
    int max_value = 0;
    int partial_value = 0;
    for (int i = 0; i < n; i ++ ) {
        cin >> p;
        if (p < 0 && partial_value > max_value) {
            max_value = partial_value;
        }
        if (partial_value + p < 0) {
            partial_value = 0;
        } else {
            partial_value += p;
        }
    }
    if (partial_value > max_value) max_value = partial_value;
    cout << max_value;
    return 0;
}