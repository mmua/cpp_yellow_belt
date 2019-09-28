#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include <cmath>

using namespace std;

class Figure {
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure
{
public:
    Triangle(int a, int b, int c) : a_(a), b_(b), c_(c) {};
    string Name() const override { return "TRIANGLE";}
    double Perimeter() const override { return a_ + b_ + c_;}
    double Area() const override {
        double p = Perimeter() / 2;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }
protected:
    int a_;
    int b_;
    int c_;
};

class Rect : public Figure
{
public:
    Rect(int width, int height): width_(width), height_(height) {};
    string Name() const override { return "RECT";}
    double Perimeter() const override { return 2 * (width_ + height_);}
    double Area() const override { return width_ * height_;}
protected:
    int width_;
    int height_;
};

const double PI = 3.14;

class Circle : public Figure
{
public:
    explicit Circle(int radius): radius_(radius) {};
    string Name() const override { return "CIRCLE";}
    double Perimeter() const override { return 2 * PI * radius_;}
    double Area() const override { return PI * radius_ * radius_;}
protected:
    int radius_;
};

shared_ptr<Figure> CreateFigure(istringstream& is)
{
    string figure;
    int a, b, c;
    is >> figure;
    if(figure == "RECT") {
        is >> a >> b;
        return make_shared<Rect>(a, b);
    } else if (figure == "CIRCLE") {
        is >> a;
        return make_shared<Circle>(a);
    } else if(figure == "TRIANGLE") {
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}