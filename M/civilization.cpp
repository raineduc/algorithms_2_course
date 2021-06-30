#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <string>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::list;
using std::queue;
using std::string;

struct Point {
    int x;
    int y;
    int weight;
};

struct VisitedCell {
    Point point;
    bool visited;
    VisitedCell *predecessor;
};

typedef vector<vector<VisitedCell>> VisitedMap;

class Table {
private:
    vector<vector<int>> world_table;
    int row_size;
    int col_size;

    void addAdjacentPoint(list<Point> &points_list, int x, int y) {
        if (world_table[x][y] > 0) {
            points_list.push_back({ .x = x, .y = y, .weight = world_table[x][y] });
        }
    }

    list<Point> getAdjacentPoints(Point p) {
        list<Point> adjacent_points;
        if (p.x > 0) addAdjacentPoint(adjacent_points, p.x - 1, p.y);
        if (p.x < row_size - 1) addAdjacentPoint(adjacent_points, p.x + 1, p.y);
        if (p.y > 0) addAdjacentPoint(adjacent_points, p.x, p.y - 1);
        if (p.y < col_size - 1) addAdjacentPoint(adjacent_points, p.x, p.y + 1);
        return adjacent_points;
    }

    void visitCell(VisitedMap &visited_map, Point point, VisitedCell *predecessor) {
        visited_map[point.x][point.y].point = point;
        visited_map[point.x][point.y].visited = true;
        visited_map[point.x][point.y].predecessor = predecessor;
    }

    int calcPathWeight(VisitedCell &cell, int current_weight) {
        auto predecessor = cell.predecessor;
        if (predecessor != nullptr) {
            return calcPathWeight(*predecessor, current_weight + world_table[cell.point.x][cell.point.y]);
        }
        return current_weight;
    }

    string buildPath(VisitedCell &cell, string current_path) {
        auto predecessor = cell.predecessor;
        if (predecessor != nullptr) {
            if (predecessor->point.x != cell.point.x) {
                return buildPath(*predecessor,
                                 (predecessor->point.x < cell.point.x ? "S" : "N") + current_path);
            }
            if (predecessor->point.y != cell.point.y) {
                return buildPath(*predecessor,
                                 (predecessor->point.y < cell.point.y ? "E" : "W") + current_path);
            }
        }
        return current_path;
    }

public:
    Table(int row_size, int col_size) {
        world_table = vector<vector<int>>(row_size, vector<int>(col_size));
        this->row_size = row_size;
        this->col_size = col_size;
    }

    void setPoint(int row, int col, int val) {
        world_table[row][col] = val;
    }

    Point getPoint(int row, int col) {
        return { .x = row, .y = col, .weight = world_table[row][col] };
    }

    void tableBFS(Point start_point, Point finish_point) {
        auto visited_map = VisitedMap(row_size, vector<VisitedCell>(col_size));
        queue<Point> points_queue;
        points_queue.push(start_point);
        visitCell(visited_map, start_point, nullptr);
        while (!points_queue.empty()) {
            auto current_point = points_queue.front();
            if (current_point.weight > 1) {
                current_point.weight -= 1;
                points_queue.push(current_point);
                points_queue.pop();
                continue;
            }
            auto adjacentPoints = getAdjacentPoints(current_point);
            for (auto &p : adjacentPoints) {
                if (!visited_map[p.x][p.y].visited) {
                    points_queue.push(p);
                    visitCell(visited_map, p, &visited_map[current_point.x][current_point.y]);
                    if (p.x == finish_point.x && p.y == finish_point.y) {
                        cout << calcPathWeight(visited_map[p.x][p.y], 0) << "\n";
                        cout << buildPath(visited_map[p.x][p.y], "");
                        return;
                    }
                }
            }
            points_queue.pop();
        }
        cout << -1;
    }
};

int main() {
    int n, m;
    int start_x, start_y;
    int finish_x, finish_y;
    cin >> n >> m;
    cin >> start_x >> start_y;
    cin >> finish_x >> finish_y;

    Table world_table = Table(n, m);

    char read_cell;
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < m; j++) {
            cin >> read_cell;
            if (read_cell == '.') {
                world_table.setPoint(i, j, 1);
            } else if (read_cell == 'W') {
                world_table.setPoint(i, j, 2);
            } else {
                world_table.setPoint(i, j, 0);
            }
        }
    }
    world_table.tableBFS(world_table.getPoint(start_x - 1, start_y - 1),
                         world_table.getPoint(finish_x - 1, finish_y - 1));

    return 0;
}