#include <iostream>
#include <cmath>

using namespace std;

double calculateAreaOfQuarterCircle(double radius);

int main()
{
    int radius;
    cout << "This program calculates an area of a quarter circle with radius r." << endl
         << " Enter radius of circle: ";
    cin >> radius;

    cout << "Area of a quarter circle is " << calculateAreaOfQuarterCircle(radius) << endl;

    return 0;
}

double calculateAreaOfQuarterCircle(double radius) {
    constexpr int RECTANGLES = 10000;
    double area = 0;
    const double REC_WIDTH = radius / RECTANGLES;

    for (int i = 0; i < RECTANGLES; ++i) {
        double recMidPoint = REC_WIDTH * (i + 1) - REC_WIDTH / 2;
        double recHeight = sqrt(radius * radius - recMidPoint * recMidPoint);
        area += recHeight * REC_WIDTH;
    }

    return area;
}
