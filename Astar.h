#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>

using namespace std;

// �O���b�h��̈ʒu��\���\����
struct Point {
    int x, y;

    // �f�t�H���g�R���X�g���N�^��ǉ�
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
};

// A*�A���S���Y���̃N���X
class AStar {
public:
    // �R���X�g���N�^
    AStar();

    // A*�A���S���Y��
    void findPath(const Point& start, const Point& goal);

    // ��Q���������_���ɐݒ肷�郁�\�b�h
    void setRandomObstacles(int obstacleCount);

    // �S�[���n�_��ݒ肷�郁�\�b�h
    void setGoal(const Point& goal);

    // �}�b�v�̃T�C�Y
    static const int rows = 8;
    static const int cols = 8;

    // �}�b�v
    int map[rows][cols];

    // ��Q�����Ȃ����Ƃ������l
    static const int clear = 0;

    // ��Q�������邱�Ƃ������l
    static const int obstacle = 1;


    // �ړ��\�ȕ����i�㉺���E�j
    static const int dx[];
    static const int dy[];
private:
    // �m�[�h�̏���\���\����
    struct Node {
        Point point;
        int g;  // �X�^�[�g����̎��ۂ̃R�X�g
        int h;  // �q���[���X�e�B�b�N�i����R�X�g�j
        int f;  // f = g + h

        Node(const Point& _point, int _g, int _h) : point(_point), g(_g), h(_h), f(_g + _h) {}


        // f�l�Ɋ�Â��Ĕ�r���鉉�Z�q
        bool operator>(const Node& other) const {
            return f > other.f;
        }
    };

    // �����_���ȍ��W���擾���郁�\�b�h
    Point getRandomPoint();

    // �S�[���n�_
    Point goal;
};
