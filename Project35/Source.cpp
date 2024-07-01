#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>

// Константи
const double V = 1.0;  // Швидкість мурах
const double R = 10.0; // Радіус руху мурах-воїнів
const double PI = 3.14159265358979323846;

// Структура для зберігання координат точки
struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// Клас мурахи
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

// Клас мурахи-робочого
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

        // Реверс руху, коли досягає цілі
        if (position.x == destination.x && position.y == destination.y) {
            std::swap(position, destination);
        }
    }
};

// Клас мурахи-воїна
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

    // Додавання мурах-робочих
    ants.push_back(new WorkerAnt(10, 10, V, Point(0, 0)));
    ants.push_back(new WorkerAnt(5, 5, V, Point(0, 0)));

    // Додавання мурах-воїнів
    ants.push_back(new WarriorAnt(0, 0, V, R));

    // Запуск симуляції
    simulate(ants);

    // Очищення пам'яті
    for (Ant* ant : ants) {
        delete ant;
    }

    return 0;
}
