#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "gwindow.h"

class Shape {
public:
    void setLocation(double x, double y);
    void move(double x, double y);
    void setColor(std::string color);

    virtual void draw(GWindow& window) = 0;
    virtual bool contains(double x, double y) = 0;

    virtual ~Shape();

protected:
    Shape();
    std::string color;
    double x_, y_;
};


class Line : public Shape {
public:
    Line(double x1, double y1, double x2, double y2);

    void draw(GWindow &window) override;
    bool contains(double x, double y) override;

private:
    double dx;
    double dy;

    double distanceFrom(double x, double y);
};


class Rect : public Shape {
public:
    Rect(double x, double y, double width, double height);

    void draw(GWindow &window) override;
    bool contains(double x, double y) override;

private:
    double width, height;
};


class Oval : public Shape {
public:
    Oval(double x, double y, double width, double height);

    void draw(GWindow &window) override;
    bool contains(double x, double y) override;

private:
    double width, height;
};


class Circle : public Oval {
public:
    Circle(double x, double y, double r);
private:
    double radius;
};


class Square : public Shape {
public:
    Square(double x, double y, double size);

    void draw(GWindow &window) override;
    bool contains(double x, double y) override;

private:
    double size;
};

#endif // SHAPE_H
