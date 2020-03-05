#include "cube.h"
#include "string.h"
#include <iostream>

Cube::Cube()
    : Cube(WHITE, WHITE, WHITE, WHITE, WHITE, WHITE)
{
}

Cube::Cube(Colour top, Colour bottom, Colour left, Colour right, Colour front, Colour back)
    : top(top), bottom(bottom), left(left), right(right), front(front), back(back)
{
}

void Cube::rotateUntilFace(int face) {
    if (face > 4) {
        rotateZ(face);
    } else {
        rotateX(face);
    }
}

void Cube::rotateZ(int rotateCount) {
    for (int i = 0; i < rotateCount; i++) {
        Colour tmp = bottom;
        bottom = left;
        left = top;
        top = right;
        right = tmp;
    }
}

void Cube::rotateX(int rotateCount) {
    for (int i = 0; i < rotateCount; i++) {
        Colour tmp = front;
        front = top;
        top = back;
        back = bottom;
        bottom = tmp;
    }
}

void Cube::rotateY(int rotateCount) {
    for (int i = 0; i < rotateCount; i++) {
        Colour tmp = front;
        front = right;
        right = back;
        back = left;
        left = tmp;
    }
}

bool Cube::isIntersected(const Cube& other) const {
    return top == other.top
            || back == other.back
            || bottom == other.bottom
            || front == other.front;
}

std::string color(Colour c) {
    switch (c) {
        case RED:
            return "R";
        case BLACK:
            return "B";
        case WHITE:
            return "W";
        case GREEN:
            return "G";
        default:
            return "W";
    }
}

void Cube::print() const {
    std::cout << "    " << color(back) << std::endl;
    std::cout << color(bottom) << " " << color(left) << " " << color(top) << " " << color(right) << std::endl;
    std::cout << "    " << color(front) << std::endl;
}
