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
    std::string _name;
    std::vector <Point> _PointsStorage;
public:
    virtual void input() = 0;
    virtual std::string getName() = 0;
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

class Triangle : public Figure {
public:
    void input() override {
        std::string name;
        int x, y;
        std::cout << "Enter a name for figure: ";
        std::cin >> _name;
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

    std::string getName() override {
        return _name;
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
        std::cout << "Figure name: " << getName() << std::endl;
        std::cout << "Contains dots: " << std::endl;
        for (int i = 0; i < _PointsStorage.size(); ++i) {
            std::cout << "     " << _PointsStorage[i].getName() << ": (" << _PointsStorage[i].getX() << ":" << _PointsStorage[i].getY() << ")" << std::endl;
        }
        std::cout << "Perimeter: " << perimeter() << std::endl;
        std::cout << "Square: " << square() << std::endl;
    }

    Triangle(){
        input();
    }
};

class Quadrangle : public Figure {
public:
    void input() override {
        std::string name;
        int x, y;
        std::cout << "Enter a name for figure: ";
        std::cin >> _name;
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

    std::string getName() override {
        return _name;
    }

    double perimeter() override {
        return distance(_PointsStorage[0], _PointsStorage[1]) + distance(_PointsStorage[1], _PointsStorage[2]) + distance(_PointsStorage[2], _PointsStorage[3]) + distance(_PointsStorage[3], _PointsStorage[0]);
    }

    double square() override {
        return distance(_PointsStorage[0], _PointsStorage[1]) * distance(_PointsStorage[1], _PointsStorage[2]);
    }

    void output() override {

        std::cout << "Figure name: " << getName() << std::endl;
        std::cout << "Contains dots: " << std::endl;
        for (int i = 0; i < _PointsStorage.size(); ++i) {
            std::cout << "     " << _PointsStorage[i].getName() << ": (" << _PointsStorage[i].getX() << ":" << _PointsStorage[i].getY() << ")" << std::endl;
        }
        std::cout << "Perimeter: " << perimeter() << std::endl;
        std::cout << "Square: " << square() << std::endl;
    }

    Quadrangle(){
        input();
    }
};

class Circle : public Figure {
public:
    void input() override {
        std::string name;
        int x, y;
        std::cout << "Enter a name for figure: ";
        std::cin >> _name;
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

    std::string getName() override {
        return _name;
    }

    double perimeter() override {
        return 2 * distance(_PointsStorage[0], _PointsStorage[1]) * M_PI;
    }

    double square() override {
        return distance(_PointsStorage[0], _PointsStorage[1]) * distance(_PointsStorage[0], _PointsStorage[1]) * M_PI;
    }

    void output() override {

        std::cout << "Figure name: " << getName() << std::endl;
        std::cout << "Contains dots: " << std::endl;
        for (int i = 0; i < _PointsStorage.size(); ++i) {
            std::cout << "     " << _PointsStorage[i].getName() << ": (" << _PointsStorage[i].getX() << ":" << _PointsStorage[i].getY() << ")" << std::endl;
        }
        std::cout << "Radius: " << distance(_PointsStorage[0], _PointsStorage[1]) << std::endl;
        std::cout << "Perimeter: " << perimeter() << std::endl;
        std::cout << "Square: " << square() << std::endl;
    }

    Circle() {
        input();
    }
};

int main() {

    std::vector <Triangle> triangles;
    std::vector <Quadrangle> quadrangles;
    std::vector <Circle> circles;

    int n, type;

    std::cout << "Enter the number of figures: ";
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cout << "Enter shape type (1-Triangle, 2-Quadrangle, 3-Circle): ";
        std::cin >> type;
        switch (type) {
            case 1:
                triangles.emplace_back(Triangle());
                break;
            case 2:
                quadrangles.emplace_back(Quadrangle());
                break;
            case 3:
                circles.emplace_back(Circle());
                break;
            default:
                std::cout << "Input Error!";
                return 0;
                break;
        }
    }

    struct figures{
        int type;
        int index;
        double square;
    };

    int index = 0;
    double maximum;
    std::vector <figures> Figures;
    std::vector <figures> SortedFigures;

    for (int i = 0; i < triangles.size(); ++i) {
        Figures.push_back({1, i, triangles[i].square()});
    }

    for (int i = 0; i < quadrangles.size(); ++i) {
        Figures.push_back({2, i, quadrangles[i].square()});
    }

    for (int i = 0; i < circles.size(); ++i) {
        Figures.push_back({3, i, circles[i].square()});
    }

    do {
        index = 0;
        maximum = 0;
        for (int i = 0; i < Figures.size(); ++i) {
            if(Figures[i].square > maximum){
                index = i;
                maximum = Figures[i].square;
            }
        }
        SortedFigures.push_back(Figures[index]);
        Figures.erase(Figures.begin() + index);
    } while (!Figures.empty());


    for (auto & SortedFigure : SortedFigures) {
        switch (SortedFigure.type) {
            case 1:
                triangles[SortedFigure.index].output();
                break;
            case 2:
                quadrangles[SortedFigure.index].output();
                break;
            case 3:
                circles[SortedFigure.index].output();
                break;
            default:
                break;
        }
    }
    return 0;
}
