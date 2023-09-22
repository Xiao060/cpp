#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

class Circle {
public:

    Circle() 
    : _radius(0) {}

    Circle(double r) 
    : _radius(r) {}

    double getArea() {
        return M_PI * _radius * _radius; 
    }

    double getPerimeter() {
        return 2 * M_PI * _radius;
    }

    void show() {
        cout << "radius: " << _radius << endl 
             << "area: " << getArea() << endl
             << "perimeter: " << getPerimeter() << endl;
    }

private:
    double _radius;
};


class Cylinder 
: public Circle {

public:
    Cylinder(double r, double h)
    : Circle(r)
    , _height(h) {}

    double getVolume() {
        return getArea() * _height;
    }

    void showVolume() {
        cout << "volume: " << getVolume() << endl;
    }

private:
    double _height;
};




int main(int argc, char* argv[]) {

    Circle a;
    a.show();
    cout << endl;

    Circle b(2);
    b.show();
    cout << endl;

    Cylinder c(2, 4);
    c.show();
    c.showVolume();
    cout << endl;

    return 0;
}




