
#ifndef _point_h
#define _point_h

#include <string>
#include <iostream>

class Point {
public:
    Point();
    Point(int cx, int cy);
    int getX();
    int getY();
    std::string toString() const;

    friend bool operator==(const Point& pt1, const Point& pt2);

private:
    int x;
    int y;
};

std::ostream& operator<< (std::ostream& os, const Point& pt);
bool operator== (const Point& pt1, const Point& pt2);
bool operator!= (const Point& pt1, const Point& pt2);

#endif
