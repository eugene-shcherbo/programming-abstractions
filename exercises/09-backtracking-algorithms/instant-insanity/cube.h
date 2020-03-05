#ifndef CUBE_H
#define CUBE_H

enum Colour {
    RED, GREEN, WHITE, BLACK, NO_COLOR
};

class Cube
{
public:
    Cube();
    Cube(Colour top, Colour bottom, Colour left, Colour right, Colour front, Colour back);

    void rotateUntilFace(int face);
    void rotateX(int rotateCount);
    void rotateZ(int rotateCount);
    void rotateY(int rotateCount);
    bool isIntersected(const Cube& other) const;
    void print() const;

private:
    Colour top;
    Colour bottom;
    Colour left;
    Colour right;
    Colour front;
    Colour back;
};

#endif // CUBE_H
