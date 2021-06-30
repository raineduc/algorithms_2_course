#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <list>

using std::vector;
using std::multimap;
using std::unordered_map;
using std::array;
using std::cin;
using std::cout;
using std::pair;
using std::list;

struct memory_node {
    bool is_free;
    unsigned int size;
    unsigned int start;
};

typedef list<memory_node>::iterator mem_iterator;

class MemoryState {
private:
    list<memory_node> nodes;

public:
    MemoryState() {};

    mem_iterator Init(bool is_free, unsigned int start, unsigned int size) {
        return nodes.insert(nodes.end(), {
            .is_free = is_free,
            .size = size,
            .start = start
        });
    }

    // возвращает итератор на выделенную память и на оставшуюся от блока память
    array<mem_iterator, 2> Allocate(mem_iterator it, unsigned int required_size) {
        if (!it->is_free || it->size < required_size) {
            throw std::logic_error("Can not be allocated");
        }
        if (it->size > required_size) {
            auto next_node = std::next(it);
            auto free = nodes.insert(next_node, { .is_free =  true , .size =  it->size - required_size, .start =  it->start + required_size });
            auto allocated = nodes.insert(free, { .is_free = false, .size = required_size, .start = it->start });
            nodes.erase(it);
            return { allocated, free };
        }
        it->is_free = false;
        return { it, nodes.end() };
    }

    list<memory_node>& getList() {
        return nodes;
    }


    // возвращает вектор указателей на объединенные узлы (которых больше нет в списке)
    // а также итератор итогового узла
    pair<vector<memory_node*>, mem_iterator> Free(mem_iterator it) {
        vector<memory_node*> merged_free_blocks;
        if (it->is_free) {
            throw std::logic_error("Block is already free");
        }
        auto left = it == nodes.begin() ? nodes.begin() : std::prev(it);
        auto right = it == nodes.end() ? nodes.end() : std::next(it);
        auto new_size = it->size;
        auto next = right;
        auto start = it->start;
        if (left->is_free) {
            new_size += left->size;
            start = left->start;
            merged_free_blocks.push_back(&(*left));
            nodes.erase(left);
        }
        if (right != nodes.end() && right->is_free) {
            new_size += right->size;
            next = std::next(right);
            merged_free_blocks.push_back(&(*right));
            nodes.erase(right);
        }
        if (it->size != new_size) {
            auto new_block = nodes.insert(next, { .is_free = true, .size = new_size, .start = start });
            nodes.erase(it);
            return { merged_free_blocks, new_block };
        }
        it->is_free = true;
        return { merged_free_blocks, it };
    }
};

int main() {
    unsigned int n, m;
    cin >> n;
    cin >> m;

    auto memory_state = MemoryState();
    auto initial_block = memory_state.Init(true, 0, n);
    multimap<unsigned int, mem_iterator> free_blocks;
    unordered_map<unsigned int, mem_iterator> insertion_order;
    // сопоставляет указатели на узлы памяти и итераторы мапы свободных блоков
    unordered_map<memory_node*, multimap<unsigned int, mem_iterator>::iterator> tree_blocks_matching;

    auto it = free_blocks.emplace(initial_block->size, initial_block);
    tree_blocks_matching[&(*initial_block)] = it;

    vector<int> results;

    int request;
    for (auto i = 0; i < m; i++) {
        cin >> request;
        if (request > 0) {
            auto equal_elem = free_blocks.find(request);
            auto elem = equal_elem == free_blocks.end() ? free_blocks.upper_bound(request) : equal_elem;
            if (elem != free_blocks.end()) {
                free_blocks.erase(elem);
                auto allocated = memory_state.Allocate(elem->second, request);
                if (allocated[1] != memory_state.getList().end()) {
                    it = free_blocks.emplace(allocated[1]->size, allocated[1]);
                    tree_blocks_matching[&(*allocated[1])] =  it;
                }
                insertion_order.emplace(i + 1, allocated[0]);
                results.push_back(allocated[0]->start + 1);
                continue;
            }
            results.push_back(-1);
        } else {
            if (insertion_order.find(-request) == insertion_order.end()) {
                continue;
            }
            auto requested_node = insertion_order[-request];
            auto free_info = memory_state.Free(requested_node);
            auto merged_free_blocks = free_info.first;
            auto final_block = free_info.second;
            for (auto & elem: merged_free_blocks) {
                free_blocks.erase(tree_blocks_matching[elem]);
            }
            it = free_blocks.emplace(final_block->size, final_block);
            tree_blocks_matching[&(*final_block)] = it;
        }
    }

    for (const auto & elem: results) {
        cout << elem << "\n";
    }

    return 0;
}
