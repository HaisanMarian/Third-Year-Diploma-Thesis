#include "Point.h"
#include <iostream>
using namespace std;

int Point::count = 0;

Point::Point() : x(0), y(0) {
    count++;
}

Point::Point(double xx, double yy) : x(xx), y(yy) {
    count++;
}

Point::Point(const Point& other) : x(other.x), y(other.y) {
    count++;
}

Point::~Point() {
    count--;
}

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator<<(ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

int Point::getCount() {
    return count;
}

Point& Point::operator++() {
    x += 10;
    return *this;
}

Point Point::operator++(int) {
    Point temp(*this);
    x += 10;
    return temp;
}

Point& Point::operator--() {
    x -= 10;
    return *this;
}

Point Point::operator--(int) {
    Point temp(*this);
    x -= 10;
    return temp;
}

double operator||(const Point& a, const Point& b) {
    double dx = b.getX() - a.getX();
    double dy = b.getY() - a.getY();
    return sqrt(dx*dx + dy*dy);
}

