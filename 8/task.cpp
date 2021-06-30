#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;

int main() {
    int n;
    int k;
    cin >> n;
    cin >> k;
    vector<int> prices;
    int price;
    int sum = 0;
    for (auto i = 0; i < n; i++) {
        cin >> price;
        sum += price;
        prices.push_back(price);
    }
    sort(prices.begin(), prices.end());
    for (auto i = n - k; i >= 0; i -= k) {
        sum -= prices[i];
    }
    cout << sum;
    return 0;
}