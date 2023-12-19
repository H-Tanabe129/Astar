#include "Astar.h"

using namespace std;

const int ROWS = 5;
const int COLS = 5;

vector<vector<int>> obstacleMap = {
    {0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 1},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}
};

const int dx[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
const int dy[] = { 0, 0, -1, 1, -1, 1, -1, 1 };

AStar::AStar(Point src, Point dest) : src(src), dest(dest) {}

void AStar::findPath() {
    priority_queue<Node, vector<Node>, function<bool(Node, Node)>> pq(
        [](Node const& a, Node const& b) {
            return a.f > b.f;
        }
    );

    vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));

    Node startNode = { src, 0, 0, 0, nullptr };
    startNode.h = calculateHValue(src.x, src.y, dest);
    startNode.f = startNode.g + startNode.h;

    pq.push(startNode);

    while (!pq.empty()) {
        Node currentNode = pq.top();
        pq.pop();

        int x = currentNode.point.x;
        int y = currentNode.point.y;

        visited[x][y] = true;

        if (isDestination(x, y, dest)) {
            cout << "Œo˜H‚ªŒ©‚Â‚©‚è‚Ü‚µ‚½B" << endl;
            printPath(&currentNode);
            return;
        }

        for (int i = 0; i < 8; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(newX, newY) && !visited[newX][newY]) {
                Node neighbor = { {newX, newY}, 0, 0, 0, &currentNode };
                neighbor.g = currentNode.g + 1;
                neighbor.h = calculateHValue(newX, newY, dest);
                neighbor.f = neighbor.g + neighbor.h;

                pq.push(neighbor);
            }
        }
    }

    cout << "Œo˜H‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½B" << endl;
}

bool AStar::isValid(int x, int y) const {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && obstacleMap[x][y] == 0;
}

bool AStar::isDestination(int x, int y, Point dest) const {
    return x == dest.x && y == dest.y;
}

int AStar::calculateHValue(int x, int y, Point dest) const {
    return abs(x - dest.x) + abs(y - dest.y);
}

void AStar::printPath(Node* destNode) const {
    vector<Point> path;
    Node* current = destNode;

    while (current != nullptr) {
        path.push_back(current->point);
        current = current->parent;
    }

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            Point currentPoint = { i, j };
            if (currentPoint == destNode->point) {
                cout << "D ";
            }
            else if (currentPoint == path.back()) {
                cout << "S ";
                path.pop_back();
            }
            else if (obstacleMap[i][j] == 1) {
                cout << "¡ ";
            }
            else if (find(path.begin(), path.end(), currentPoint) != path.end()) {
                cout << "  ";
            }
            else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}
