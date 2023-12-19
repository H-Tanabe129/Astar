#include "AStar.h"

using namespace std;

// 移動可能な方向（上下左右）
const int AStar::dx[] = { -1, 0, 1, 0 };
const int AStar::dy[] = { 0, 1, 0, -1 };

// コンストラクタ
AStar::AStar() {
    // マップの初期化
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            map[i][j] = clear;
        }
    }

    // srand を呼び出す
    srand(static_cast<unsigned>(time(0)));

    // 障害物の設定
   /* map[1][1] = obstacle;
    map[1][3] = obstacle;
    map[3][1] = obstacle;
    map[3][3] = obstacle;*/

    // 障害物のランダムな設定
    setRandomObstacles(10);
}

// A*アルゴリズム
void AStar::findPath(const Point& start, const Point& goal) {
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    vector<vector<int>> closedSet(rows, vector<int>(cols, 0));
    vector<vector<Point>> cameFrom(rows, vector<Point>(cols, Point(-1, -1)));

    openSet.push(Node(start, 0, abs(start.x - goal.x) + abs(start.y - goal.y)));

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.point.x == goal.x && current.point.y == goal.y) {
            // ゴールに到達したら経路を表示
            vector<vector<char>> path(rows, vector<char>(cols, ' '));
            Point pathPoint = goal;

            while (pathPoint.x != -1 && pathPoint.y != -1) {
                path[pathPoint.x][pathPoint.y] = '*';
                pathPoint = cameFrom[pathPoint.x][pathPoint.y];
            }

            // スタート地点とゴール地点の表示
            path[start.x][start.y] = 'S';
            path[goal.x][goal.y] = 'G';

            // 経路を出力
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    cout << path[i][j] << ' ';
                }
                cout << endl;
            }

            return;
        }

        closedSet[current.point.x][current.point.y] = 1;

        for (int i = 0; i < (rows-1); ++i) {
            int newX = current.point.x + dx[i];
            int newY = current.point.y + dy[i];

            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                map[newX][newY] == clear && !closedSet[newX][newY]) {
                int newG = current.g + 1;
                int newH = abs(newX - goal.x) + abs(newY - goal.y);
                int newF = newG + newH;

                if (cameFrom[newX][newY].x == -1 || newF < current.f) {
                    openSet.push(Node(Point(newX, newY), newG, newH));
                    cameFrom[newX][newY] = current.point;
                }
            }
        }
    }

    // ゴールに到達できない場合
    cout << "No path found." << endl;
}

// ランダムな座標を取得するメソッド
Point AStar::getRandomPoint() {
    int randomX = rand() % rows;
    int randomY = rand() % cols;
    return Point(randomX, randomY);
}

// 障害物をランダムに設定するメソッド
void AStar::setRandomObstacles(int obstacleCount) {
    for (int i = 0; i < obstacleCount; ++i) {
        Point obstaclePoint = getRandomPoint();
        map[obstaclePoint.x][obstaclePoint.y] = obstacle;
    }
}

void AStar::setGoal(const Point& _goal)
{
    // 外部から指定されたゴール座標を設定
    this->goal = _goal;

    // ゴール地点に障害物がある場合はクリアに変更
    if (map[this->goal.x][this->goal.y] == obstacle) {
        map[this->goal.x][this->goal.y] = clear;
    }
}
