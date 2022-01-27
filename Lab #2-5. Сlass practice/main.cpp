#include <iostream>

class point{

private:
    int _x;
    int _y;

public:
    void input(){
        std::cout << "Enter X:";
        std::cin >> _x;
        std::cout << "Enter Y:";
        std::cin >> _y;
    }

    int getX() const {
        return _x;
    }

    int getY() const {
        return _y;
    }

    void output() const{
        std::cout << "Point coordinates is (" << _x << ";" << _y << ")" << std::endl;
    }
};

class triangle{
private:
    point P1{};
    point P2{};
    point P3{};
public:
    float perimeter(){
        return (sqrt((P1.getX() - P2.getX()) * (P1.getX() - P2.getX()) + (P1.getY() - P2.getY()) * (P1.getY() - P2.getY())) +
                sqrt((P2.getX() - P3.getX()) * (P2.getX() - P3.getX()) + (P2.getY() - P3.getY()) * (P2.getY() - P3.getY())) +
                sqrt((P1.getX() - P3.getX()) * (P1.getX() - P3.getX()) + (P1.getY() - P3.getY()) * (P1.getY() - P3.getY())));
    }

    float square(){
        float half_perimeter = 0.5 * perimeter();
        return sqrt(half_perimeter * (half_perimeter - sqrt((P1.getX() - P2.getX()) * (P1.getX() - P2.getX()) + (P1.getY() - P2.getY()) * (P1.getY() - P2.getY()))) * (half_perimeter - sqrt((P2.getX() - P3.getX()) * (P2.getX() - P3.getX()) + (P2.getY() - P3.getY()) * (P2.getY() - P3.getY()))) * (half_perimeter - sqrt((P1.getX() - P3.getX()) * (P1.getX() - P3.getX()) + (P1.getY() - P3.getY()) * (P1.getY() - P3.getY()))));
    }

    triangle(){
        P1.input();
        P2.input();
        P3.input();
        std::cout << perimeter();
        std::cout << std::endl;
        std::cout << square();
    }
};

int main() {
    triangle MyTriangle;
    return 0;
}
