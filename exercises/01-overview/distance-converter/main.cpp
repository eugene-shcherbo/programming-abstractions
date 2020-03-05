#include <iostream>

using namespace std;

constexpr double INCH_TO_METERS = 0.0254;
constexpr double FOOT_TO_INCHES = 12;

int main()
{
    double distance;
    cout << "Enter a distance in meters: ";
    cin >> distance;

    double inches = distance / INCH_TO_METERS;
    double feets = inches / FOOT_TO_INCHES;

    cout << "You have entered " << distance << " meters."
         << " It's equal to " << inches << " inches"
         << " and " << feets << " feets"
         << endl;

    return 0;
}
