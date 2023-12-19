#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <functional>
#include <algorithm>

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

class AStar {
public:
    AStar(Point src, Point dest);
    void findPath();

private:
    struct Node {
        Point point;
        int f, g, h;
        Node* parent;
    };

    Point src, dest;

    bool isValid(int x, int y) const;
    bool isDestination(int x, int y, Point dest) const;
    int calculateHValue(int x, int y, Point dest) const;
    void printPath(Node* destNode) const;
};