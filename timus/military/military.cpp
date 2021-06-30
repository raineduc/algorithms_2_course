#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::pair;

struct node {
    unsigned int value;
    bool is_leaf;
};

// узлы дерева отрезков хранят длины отрезков, а листы - значения массива
class IntervalTree {
private:
    vector<node> *elements;
    unsigned int data_length;

    void build_tree(unsigned int current_node, unsigned int left, unsigned int right) {
        if (left == right) {
            (*elements)[current_node - 1] = { .value = left + 1, .is_leaf = true };
            return;
        }
        auto middle = (right + left) / 2;
        build_tree(2 * current_node, left, middle);
        build_tree(2 * current_node + 1, middle + 1, right);
        (*elements)[current_node - 1] = { .value = right - left + 1, .is_leaf = false }; // current length
    }

    // Возвращает элемент и индекс листа в дереве
    pair<node, unsigned int> get_element(unsigned int index, unsigned int current_node, unsigned int incoming_index) {
        if ((*elements)[current_node - 1].is_leaf) {
            return { (*elements)[current_node - 1], current_node };
        }
        auto left_elem = (*elements)[2 * current_node - 1];
        auto left_len = left_elem.is_leaf ? 1 : left_elem.value;
        if (index < incoming_index + left_len) {
            return get_element(index, 2 * current_node, incoming_index);
        }
        return get_element(index, 2 * current_node + 1, incoming_index + left_len);
    }

    void decrease_len(unsigned int node) {
        (*elements)[node - 1].value -= 1;
        if (node == 1) return;
        decrease_len(node / 2);
    }
public:
    IntervalTree(unsigned int sz) {
        elements = new vector<node>(sz * 4);
        data_length = sz;
    }

    IntervalTree* build() {
        build_tree(1, 0, data_length - 1);
        return this;
    }

    unsigned int delete_element(unsigned int index) {
        auto elem = get_element(index, 1, 0);
        if (elem.second % 2 == 0) { // левый ли это лист
            (*elements)[elem.second - 1] = (*elements)[elem.second]; // положить на его место соседний лист
        }
        if (elem.second > 1) {
            decrease_len(elem.second / 2);
        }
        return elem.first.value;
    }
};

int main() {
    unsigned int n, k;
    cin >> n;
    cin >> k;

    IntervalTree tree(n);
    tree.build();

    auto current_index = k - 1;
    auto len = n;
    for (auto i = 0; i < n; i++) {
        cout << tree.delete_element(current_index) << " ";
        len -= 1;
        if (len > 0) {
            current_index = (current_index + k - 1) % len;
        }
    }
    return 0;
}
