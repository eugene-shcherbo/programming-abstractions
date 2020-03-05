#include <iostream>
#include <cmath>
#include "error.h"
#include "console.h"

using namespace std;

double windChill(double temp, double windSpeed);
void buildWindChillTable();

int main() {
    setConsoleOutputColor("white");
    cout << windChill(25, 10);
    return 0;
}

void buildWindChillTable() {

}

double windChill(double temp, double windSpeed) {
    if (windSpeed == 0.0) {
        return temp;
    } else if (temp > 40.0) {
        error("The temperature could not be more than 40°F.");
    }
    double speedCoeff = pow(windSpeed, 0.16);
    return 35.74 + 0.6215 * temp - 35.75 * speedCoeff + 0.4275 * temp * speedCoeff;
}
