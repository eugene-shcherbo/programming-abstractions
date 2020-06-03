#include <iostream>
#include <fstream>
#include "console.h"
#include "graphtypes.h"

using namespace std;

int main() {
    SimpleGraph g;
    ifstream infile("airline.txt");
    readGraph(g, infile);
    infile.close();

    writeGraph(g, cout);

    return 0;
}


