#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;
using std::greater;
using std::pair;

int main() {
    int k;
    int n;
    int n_sum = 0;
    // количество знаков и индекс в исходном списке
    vector<pair<int,int>> signs;
    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> n;
        n_sum += n;
        signs.emplace_back( n, i + 1 );
    }
    int *road = new int[n_sum];

    sort(signs.begin(), signs.end(), greater<>());

    int current_road_index = 0;
    int current_sign_index = 0;
    int last_index = n_sum - 1;
    for (int i = 0; i < 2; i++) {
        while (current_road_index <= last_index) {
            road[current_road_index] = signs[current_sign_index].second;
            signs[current_sign_index].first -= 1;
            current_road_index += 2;
            if (signs[current_sign_index].first == 0) {
                current_sign_index += 1;
            }
        }


        //конец четных позиций
        last_index = n_sum % 2 == 0 ? n_sum - 1 : n_sum - 2;

        // положить еще один такой же элемент справа, чтобы уменьшить количество повторений
        // в случае, если одинаковых знаков слишком много
        if (i == 0 && n_sum % 2 == 0 && current_sign_index == 0 && signs[current_sign_index].first > 0) {
            road[n_sum - 1] = signs[current_sign_index].second;
            signs[current_sign_index].first -= 1;
            last_index = n_sum - 2;
            if (signs[current_sign_index].first == 0) {
                current_sign_index += 1;
            }
        }
        current_road_index = 1;
    }
    for (int i = 0; i < n_sum; i++) {
        cout << road[i];
        cout << " ";
    }
    return 0;
}

