#include "AStar.h"

using namespace std;

// �ړ��\�ȕ����i�㉺���E�j
const int AStar::dx[] = { -1, 0, 1, 0 };
const int AStar::dy[] = { 0, 1, 0, -1 };

// �R���X�g���N�^
AStar::AStar() {
    // �}�b�v�̏�����
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            map[i][j] = clear;
        }
    }

    // srand ���Ăяo��
    srand(static_cast<unsigned>(time(0)));

    // ��Q���̐ݒ�
   /* map[1][1] = obstacle;
    map[1][3] = obstacle;
    map[3][1] = obstacle;
    map[3][3] = obstacle;*/

    // ��Q���̃����_���Ȑݒ�
    setRandomObstacles(10);
}

// A*�A���S���Y��
void AStar::findPath(const Point& start, const Point& goal) {
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    vector<vector<int>> closedSet(rows, vector<int>(cols, 0));
    vector<vector<Point>> cameFrom(rows, vector<Point>(cols, Point(-1, -1)));

    openSet.push(Node(start, 0, abs(start.x - goal.x) + abs(start.y - goal.y)));

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.point.x == goal.x && current.point.y == goal.y) {
            // �S�[���ɓ��B������o�H��\��
            vector<vector<char>> path(rows, vector<char>(cols, ' '));
            Point pathPoint = goal;

            while (pathPoint.x != -1 && pathPoint.y != -1) {
                path[pathPoint.x][pathPoint.y] = '*';
                pathPoint = cameFrom[pathPoint.x][pathPoint.y];
            }

            // �X�^�[�g�n�_�ƃS�[���n�_�̕\��
            path[start.x][start.y] = 'S';
            path[goal.x][goal.y] = 'G';

            // �o�H���o��
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

    // �S�[���ɓ��B�ł��Ȃ��ꍇ
    cout << "No path found." << endl;
}

// �����_���ȍ��W���擾���郁�\�b�h
Point AStar::getRandomPoint() {
    int randomX = rand() % rows;
    int randomY = rand() % cols;
    return Point(randomX, randomY);
}

// ��Q���������_���ɐݒ肷�郁�\�b�h
void AStar::setRandomObstacles(int obstacleCount) {
    for (int i = 0; i < obstacleCount; ++i) {
        Point obstaclePoint = getRandomPoint();
        map[obstaclePoint.x][obstaclePoint.y] = obstacle;
    }
}

void AStar::setGoal(const Point& _goal)
{
    // �O������w�肳�ꂽ�S�[�����W��ݒ�
    this->goal = _goal;

    // �S�[���n�_�ɏ�Q��������ꍇ�̓N���A�ɕύX
    if (map[this->goal.x][this->goal.y] == obstacle) {
        map[this->goal.x][this->goal.y] = clear;
    }
}
