#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>

// ���������
const double V = 1.0;  // �������� �����
const double R = 10.0; // ����� ���� �����-����
const double PI = 3.14159265358979323846;

// ��������� ��� ��������� ��������� �����
struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// ���� ������
class Ant {
protected:
    Point position;
    double speed;

public:
    Ant(double x, double y, double speed) : position(x, y), speed(speed) {}

    virtual void move() = 0;

    Point getPosition() const {
        return position;
    }
};

// ���� ������-��������
class WorkerAnt : public Ant {
    Point destination;

public:
    WorkerAnt(double x, double y, double speed, Point destination)
        : Ant(x, y, speed), destination(destination) {}

    void move() override {
        if (position.x < destination.x) {
            position.x += speed;
        }
        else if (position.x > destination.x) {
            position.x -= speed;
        }

        if (position.y < destination.y) {
            position.y += speed;
        }
        else if (position.y > destination.y) {
            position.y -= speed;
        }

        // ������ ����, ���� ������ ���
        if (position.x == destination.x && position.y == destination.y) {
            std::swap(position, destination);
        }
    }
};

// ���� ������-����
class WarriorAnt : public Ant {
    double angle;

public:
    WarriorAnt(double x, double y, double speed, double radius)
        : Ant(x, y, speed), angle(0) {}

    void move() override {
        angle += speed / R;
        position.x = R * cos(angle);
        position.y = R * sin(angle);
    }
};

void simulate(std::vector<Ant*>& ants) {
    while (true) {
        for (Ant* ant : ants) {
            ant->move();
            Point pos = ant->getPosition();
            std::cout << "Ant at (" << pos.x << ", " << pos.y << ")\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::vector<Ant*> ants;

    // ��������� �����-�������
    ants.push_back(new WorkerAnt(10, 10, V, Point(0, 0)));
    ants.push_back(new WorkerAnt(5, 5, V, Point(0, 0)));

    // ��������� �����-����
    ants.push_back(new WarriorAnt(0, 0, V, R));

    // ������ ���������
    simulate(ants);

    // �������� ���'��
    for (Ant* ant : ants) {
        delete ant;
    }

    return 0;
}
