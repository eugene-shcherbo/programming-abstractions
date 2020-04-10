
#ifndef _domino_h
#define _domino_h

#include <string>

class Domino {
public:
    Domino();
    Domino(int left, int right);

    std::string toString() const;
    int getLeftDots() const;
    int getRightDots() const;

    friend bool operator== (const Domino& d1, const Domino& d2);

private:
    int _left;
    int _right;
};

std::ostream& operator<< (std::ostream& os, const Domino& d);
bool operator== (const Domino& d1, const Domino& d2);
bool operator!= (const Domino& d1, const Domino& d2);

#endif
