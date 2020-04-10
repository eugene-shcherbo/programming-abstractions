#ifndef GRECTANGLE_H
#define GRECTANGLE_H

#include <iostream>
#include "gtypes.h"

namespace graphics {

    class GRectangle {
    public:
        GRectangle();
        GRectangle(double x, double y, double width, double height);

        double getX() const;
        double getY() const;
        double getHeigh() const;
        double getWidth() const;

        bool isEmpty() const;

        std::string toString() const;

        bool contains(GPoint point) const;
        bool contains(double x, double y) const;

    private:
        GPoint _point;
        double _height;
        double _width;
    };

    std::ostream& operator<< (std::ostream& os, const GRectangle& gr);
}

#endif // GRECTANGLE_H
