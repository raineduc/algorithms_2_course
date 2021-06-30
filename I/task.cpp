#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <utility>

using std::cin;
using std::cout;
using std::priority_queue;
using std::vector;
using std::unordered_set;
using std::pair;

const int P_MAX = 500000;

struct car_distribution {
    unsigned int next_car_index;
    vector<unsigned int> car_positions;

    void increase_index() {
        next_car_index += 1;
        if (next_car_index == car_positions.size()) {
            car_positions.push_back(P_MAX); // небольшой трюк, обозначаем тот факт, что машинка больше не встретится
        }
    }

    unsigned int get_current_position() {
        return car_positions[next_car_index];
    }
};

int main() {
    int n, k, p;
    cin >> n >> k >> p;

    vector<car_distribution> cars(n, { .next_car_index = 0, .car_positions = {} });
    vector<unsigned int> car_sequence;

    auto min_frequency_compare = [](pair<unsigned int, unsigned int> left, pair<unsigned int, unsigned int> right) {
        return left.second < right.second;
    };

    int current_car;
    for (int i = 0; i < p; i++) {
        cin >> current_car;
        car_sequence.push_back(current_car);
        cars[current_car - 1].car_positions.push_back(i);
    }

    unordered_set<unsigned int> car_on_floor;
    priority_queue<pair<unsigned int, unsigned int>, vector<pair<unsigned int, unsigned int>>, decltype(min_frequency_compare)> order(min_frequency_compare);
    // ключ - номер машинки, значение - следующая позиция в последовательности

    int ops_count = 0;
    for (int i = 0; i < p; i++) {
        cars[car_sequence[i] - 1].increase_index();
        if (car_on_floor.find(car_sequence[i]) == car_on_floor.end()) {
            if (car_on_floor.size() >= k) {
                auto removed_car = order.top();
                order.pop();
                car_on_floor.erase(removed_car.first);
            }
            car_on_floor.insert(car_sequence[i]);
            ops_count += 1;
        }
        order.push({ car_sequence[i], cars[car_sequence[i] - 1].get_current_position() });
    }
    cout << ops_count;

    return 0;
}

