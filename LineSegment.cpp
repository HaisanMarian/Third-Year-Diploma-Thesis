#include "LineSegment.h"

LineSegment::LineSegment()
{
    p_start = new Point(0, 0);
    p_end   = new Point(1, 1);
    color = "black";
}

LineSegment::LineSegment(const Point& a, const Point& b, const string& col)
{
    p_start = new Point(a);
    p_end   = new Point(b);
    color = col;
}

LineSegment::LineSegment(double x1, double y1, double x2, double y2, const string& col)
{
    p_start = new Point(x1, y1);
    p_end   = new Point(x2, y2);
    color = col;
}

LineSegment::LineSegment(const LineSegment& other)
{
    p_start = new Point(*other.p_start);
    p_end   = new Point(*other.p_end);
    color = other.color;
}

LineSegment::~LineSegment()
{
    delete p_start;
    delete p_end;
}

LineSegment& LineSegment::operator=(const LineSegment& other)
{
    if (this != &other) {
        *p_start = *other.p_start;
        *p_end   = *other.p_end;
        color = other.color;
    }
    return *this;
}

ostream& operator<<(ostream& out, const LineSegment& ls)
{
    out << "[" << *ls.p_start << " -> " << *ls.p_end << ", " << ls.color << "]";
    return out;
}

istream& operator>>(istream& in, LineSegment& ls)
{
    in >> *ls.p_start >> *ls.p_end >> ls.color;
    return in;
}

LineSegment& LineSegment::operator++()
{
    ++(*p_start);
    ++(*p_end);
    return *this;
}

LineSegment LineSegment::operator++(int)
{
    LineSegment temp(*this);
    ++(*p_start);
    ++(*p_end);
    return temp;
}

LineSegment& LineSegment::operator--()
{
    --(*p_start);
    --(*p_end);
    return *this;
}

LineSegment LineSegment::operator--(int)
{
    LineSegment temp(*this);
    --(*p_start);
    --(*p_end);
    return temp;
}

Point& LineSegment::operator[](int index)
{
    return (index == 0) ? *p_start : *p_end;
}

double LineSegment::getLength() const
{
    return (*p_start) || (*p_end);
}

Point LineSegment::getMidpoint() const
{
    return Point(
        (p_start->getX() + p_end->getX()) / 2.0,
        (p_start->getY() + p_end->getY()) / 2.0
    );
}

