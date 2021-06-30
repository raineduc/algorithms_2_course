#include <iostream>
#include <numeric>
#include <cmath>

using std::cin;
using std::cout;
using std::accumulate;
using std::abs;

#define MAX_SUM 2000000

static int calc_min_delta_nested(int &combination_size, const int *arr, int &arr_size,
                                 int &arr_sum, int partial_sum, int nesting, int index) {
    int min_delta = MAX_SUM;
    for (index += 1; index < arr_size; index++) {
        int sum = partial_sum + arr[index];
        if (combination_size == nesting) {
            if (abs(sum - (arr_sum - sum)) < min_delta) {
                min_delta = abs(sum - (arr_sum - sum));
            }
        } else {
            int delta = calc_min_delta_nested(combination_size, arr, arr_size,
                                              arr_sum, sum, nesting + 1, index);
            if (delta < min_delta) min_delta = delta;
        }
    }
    return min_delta;
}

int calc_min_delta(int &combination_size, int *arr, int &arr_size, int arr_sum) {
    return calc_min_delta_nested(combination_size, arr, arr_size,
                                 arr_sum, 0, 1, -1);
}

int main() {
    int n;
    cin >> n;
    int *w = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    int arr_sum = 0;
    arr_sum = accumulate(w, w + n, arr_sum);
    int min_delta = MAX_SUM;
    for (int i = 1; i <= n; i++) {
        int delta = calc_min_delta(i, w, n, arr_sum);
        if (delta < min_delta) min_delta = delta;
    }
    cout << min_delta;
    return 0;
}
