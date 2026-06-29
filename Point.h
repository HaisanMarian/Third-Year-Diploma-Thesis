#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    double x;
    double y;
    static int count;

public:
    Point();
    Point(double xx, double yy);
    Point(const Point& other);
    ~Point();

    Point& operator=(const Point& other);

    friend istream& operator>>(istream& in, Point& p);
    friend ostream& operator<<(ostream& out, const Point& p);

    double getX() const { return x; }
    double getY() const { return y; }

    static int getCount();

    Point& operator++();
    Point operator++(int);
    Point& operator--();
    Point operator--(int);

    friend double operator||(const Point& a, const Point& b);
};

#endif

