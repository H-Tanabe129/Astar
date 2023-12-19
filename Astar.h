#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>

using namespace std;

// グリッド上の位置を表す構造体
struct Point {
    int x, y;

    // デフォルトコンストラクタを追加
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
};

// A*アルゴリズムのクラス
class AStar {
public:
    // コンストラクタ
    AStar();

    // A*アルゴリズム
    void findPath(const Point& start, const Point& goal);

    // 障害物をランダムに設定するメソッド
    void setRandomObstacles(int obstacleCount);

    // ゴール地点を設定するメソッド
    void setGoal(const Point& goal);

    // マップのサイズ
    static const int rows = 8;
    static const int cols = 8;

    // マップ
    int map[rows][cols];

    // 障害物がないことを示す値
    static const int clear = 0;

    // 障害物があることを示す値
    static const int obstacle = 1;


    // 移動可能な方向（上下左右）
    static const int dx[];
    static const int dy[];
private:
    // ノードの情報を表す構造体
    struct Node {
        Point point;
        int g;  // スタートからの実際のコスト
        int h;  // ヒューリスティック（推定コスト）
        int f;  // f = g + h

        Node(const Point& _point, int _g, int _h) : point(_point), g(_g), h(_h), f(_g + _h) {}


        // f値に基づいて比較する演算子
        bool operator>(const Node& other) const {
            return f > other.f;
        }
    };

    // ランダムな座標を取得するメソッド
    Point getRandomPoint();

    // ゴール地点
    Point goal;
};
