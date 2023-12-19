#include "Astar.h"

int main() {
    Point src = { 0, 0 };
    Point dest = { 4, 4 };

    AStar astar(src, dest);
    astar.findPath();

    return 0;
}
