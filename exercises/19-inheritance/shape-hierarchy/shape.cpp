#include "shape.h"

Shape::Shape() {
    setColor("BLACK");
}

Shape::~Shape()
{}

void Shape::setLocation(double x, double y) {
    x_ = x;
    y_ = y;
}

void Shape::move(double dx, double dy) {
    x_ += dx;
    y_ += dy;
}

void Shape::setColor(std::string color) {
    this->color = color;
}

Line::Line(double x1, double y1, double x2, double y2) {
    x_ = x1;
    y_ = y1;
    dx = x2 - x1;
    dy = y2 - y1;
}

void Line::draw(GWindow& window) {
    window.setColor(color);
    window.drawLine(x_, y_, x_ + dx, y_ + dy);
}

bool Line::contains(double x, double y) {
    constexpr double halfPixel = 5;
    double distance = distanceFrom(x, y);
    return abs(distance) <= halfPixel;
}

// https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line

double Line::distanceFrom(double x, double y) {
    double x1 = x_;
    double y1 = y_;
    double x2 = x_ + dx;
    double y2 = y_ + dy;

    double numerator = abs((dy * x) - (dx * y) + (x2 * y1) - (y2 * x1));
    double denumerator = sqrt(dy * dy + dx * dx);

    return numerator/denumerator;
}

Rect::Rect(double x, double y, double width, double height) {
    x_ = x;
    y_ = y;
    this->width = width;
    this->height = height;
}

void Rect::draw(GWindow& window) {
    window.setColor(color);
    window.fillRect(x_, y_, width, height);
}

bool Rect::contains(double x, double y) {
    return x >= x_ && x <= x_ + width
           && y >= y_ && y <= y + height;
}

Oval::Oval(double x, double y, double width, double height) {
    x_ = x;
    y_ = y;
    this->width = width;
    this->height = height;
}

void Oval::draw(GWindow& window) {
    window.setColor(color);
    window.fillOval(x_, y_, width, height);
}

// using an ellipse equation
// https://math.stackexchange.com/questions/76457/check-if-a-point-is-within-an-ellipse

bool Oval::contains(double x, double y) {
    double hCenter = x_ + width / 2;
    double vCenter = y_ + height / 2;

    double rX = pow(width / 2, 2);
    double rY = pow(height / 2, 2);

    return pow((x - hCenter), 2) * rY + pow((y - vCenter), 2) * rX <= rX * rY;
}

Circle::Circle(double x, double y, double r)
    : Oval(x - r, y - r, 2 * r, 2 * r) {
}

Square::Square(double x, double y, double size) {
    x_ = x;
    y_ = y;
    this->size = size;
}

void Square::draw(GWindow& window) {
    window.setColor(color);
    window.fillRect(x_, y_, size, size);
}

bool Square::contains(double x, double y) {
    return x >= x_ && x <= x_ + size
           && y >= y_ && y <= y + size;
}
