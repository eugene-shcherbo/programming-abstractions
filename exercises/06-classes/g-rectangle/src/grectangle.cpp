#include "grectangle.h"
#include "strlib.h"

namespace graphics {

    GRectangle::GRectangle() {
        _point = GPoint(0, 0);
        _height = _width = 0;
    }

    GRectangle::GRectangle(double x, double y, double width, double height) {
        if (x < 0 || y < 0) {
            throw "error while creating a rectangle: coordinates of the left point can't negative";
        } else if (width < 0 || height < 0) {
            throw "error while creating a rectangle: coordinates of the left point can't negative";
        }

        _point = GPoint(x, y);
        _width = width;
        _height = height;
    }

    bool GRectangle::isEmpty() const {
        return _height == .0 || _width == .0;
    }

    bool GRectangle::contains(GPoint point) const {
        return contains(point.getX(), point.getY());
    }

    bool GRectangle::contains(double x, double y) const {
        double leftX = _point.getX();
        double leftY = _point.getY();

        return x >= leftX && x <= leftX + _width
                && y >= leftY && y <= leftY + _height;
    }

    double GRectangle::getX() const {
        return _point.getX();
    }

    double GRectangle::getY() const {
        return _point.getY();
    }

    double GRectangle::getHeigh() const {
        return _height;
    }

    double GRectangle::getWidth() const {
        return _width;
    }

    std::string GRectangle::toString() const {
        return "(" + doubleToString(_point.getX()) + ", "
                + doubleToString(_point.getY()) + ", "
                + doubleToString(_width) + ", "
                + doubleToString(_height) + ")";
    }

    std::ostream& operator<< (std::ostream& os, const GRectangle& gc) {
        return os << gc.toString();
    }

}
