#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include "Point.h"
#include <iostream>
using namespace std;

class LineSegment {
private:
    Point* p_start;
    Point* p_end;
    string color;

public:
    LineSegment();
    LineSegment(const Point& a, const Point& b, const string& col="black");
    LineSegment(double x1, double y1, double x2, double y2, const string& col="black");

    LineSegment(const LineSegment& other);
    ~LineSegment();

    LineSegment& operator=(const LineSegment& other);

    friend ostream& operator<<(ostream& out, const LineSegment& ls);
    friend istream& operator>>(istream& in, LineSegment& ls);

    LineSegment& operator++();
    LineSegment operator++(int);
    LineSegment& operator--();
    LineSegment operator--(int);

    Point& operator[](int index);

    double getLength() const;
    Point getMidpoint() const;
};

#endif

