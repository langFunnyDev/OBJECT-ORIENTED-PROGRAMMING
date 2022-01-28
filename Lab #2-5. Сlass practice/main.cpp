#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

class Point {
private:
    std::string name;
    int _x;
    int _y;
public:
    Point(std::string name, int x, int y) : name(std::move(name)), _x(x), _y(y) {}

    const std::string &getName() const {
        return name;
    }

    int getX() const {
        return _x;
    }

    int getY() const {
        return _y;
    }
};

class Figure {
protected:
    // std::string _name;
    std::vector <Point> _PointsStorage;
public:
    virtual void input() = 0;
    static double distance (Point &A, Point &B) {
        return sqrt(
                (A.getX() - B.getX()) * (A.getX() - B.getX())
                +
                (A.getY() - B.getY()) * (A.getY() - B.getY())
        );
    }
    virtual double perimeter() = 0;
    virtual double square() = 0;
    virtual void output() = 0;
};

class Triangle : Figure {
public:
    void input() override {
        std::string name;
        int x, y;
        for(int i = 0; i < 3; ++i){
            std::cout << "Enter a name for point #" << i + 1 << ": ";
            std::cin >> name;
            std::cout << "    Enter coordinate X:";
            std::cin >> x;
            std::cout << "    Enter coordinate Y:";
            std::cin >> y;
            _PointsStorage.emplace_back(Point(name, x, y));
        }
    }

    double perimeter() override {
        return distance(_PointsStorage[0], _PointsStorage[1]) + distance(_PointsStorage[0], _PointsStorage[2]) + distance(_PointsStorage[2], _PointsStorage[1]);
    }

    double square() override {
        double half_perimeter = perimeter() / 2;
        return sqrt(
                half_perimeter *
                (half_perimeter - distance(_PointsStorage[0], _PointsStorage[1]))
                    *
                (half_perimeter - distance(_PointsStorage[1], _PointsStorage[2]))
                    *
                (half_perimeter - distance(_PointsStorage[0], _PointsStorage[2]))
                );
    }

    void output() override {
        std::cout << "Perimeter: " << perimeter() << std::endl;
        std::cout << "Square: " << square() << std::endl;
    }

};

class Quadrangle : Figure {
public:
    void input() override {
        std::string name;
        int x, y;
        for(int i = 0; i < 4; ++i){
            std::cout << "Enter a name for point #" << i + 1 << ": ";
            std::cin >> name;
            std::cout << "    Enter coordinate X:";
            std::cin >> x;
            std::cout << "    Enter coordinate Y:";
            std::cin >> y;
            _PointsStorage.emplace_back(Point(name, x, y));
        }
    }

    double perimeter() override {
        return distance(_PointsStorage[0], _PointsStorage[1]) + distance(_PointsStorage[1], _PointsStorage[2]) + distance(_PointsStorage[2], _PointsStorage[3]) + distance(_PointsStorage[3], _PointsStorage[0]);
    }

    double square() override {
        return distance(_PointsStorage[0], _PointsStorage[1]) * distance(_PointsStorage[1], _PointsStorage[2]);
    }

    void output() override {
        std::cout << "Perimeter: " << perimeter() << std::endl;
        std::cout << "Square: " << square() << std::endl;
    }
};

class Circle : Figure {
public:
    void input() override {
        std::string name;
        int x, y;
        for(int i = 0; i < 2; ++i){
            std::cout << "Enter a name for point #" << i + 1 << ": ";
            std::cin >> name;
            std::cout << "    Enter coordinate X:";
            std::cin >> x;
            std::cout << "    Enter coordinate Y:";
            std::cin >> y;
            _PointsStorage.emplace_back(Point(name, x, y));
        }
    }

    double perimeter() override {
        return 2 * distance(_PointsStorage[0], _PointsStorage[1]) * M_PI;
    }

    double square() override {
        return distance(_PointsStorage[0], _PointsStorage[1]) * distance(_PointsStorage[0], _PointsStorage[1]) * M_PI;
    }

    void output() override {

        std::cout << "Radius: " << distance(_PointsStorage[0], _PointsStorage[1]) << std::endl;
        std::cout << "Perimeter: " << perimeter() << std::endl;
        std::cout << "Square: " << square() << std::endl;
    }
};

int main() {

    Triangle MyTriangle;
    Quadrangle MyQuadrangle;
    Circle MyCircle;

    std::cout << "Creating triangle: " << std::endl;
    MyTriangle.input();

    std::cout << "Creating quadrangle: " << std::endl;
    MyQuadrangle.input();

    std::cout << "Creating circle: " << std::endl;
    MyCircle.input();

    MyTriangle.output();
    MyQuadrangle.output();
    MyCircle.output();

    return 0;
}
