#include "AStar.h"

int main() {
    AStar astar;

    Point start(0, 0);
    Point goal(7, 7);

    cout << "Map:" << endl;
    for (int i = 0; i < AStar::rows; ++i) {
        for (int j = 0; j < AStar::cols; ++j) {
            cout << (astar.map[i][j] == AStar::clear ? " " : "¡") << ' ';
        }
        cout << endl;
    }

    cout << "Path:" << endl;
    astar.findPath(start, goal);

    return 0;
}
