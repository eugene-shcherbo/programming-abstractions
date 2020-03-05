#include <iostream>
using namespace std;

double permutations(int n, int k);

int main()
{
    int count;
    int choose;
    cout << "This programs calculates permutations. " << endl
         << " Enter a number of values: ";
    cin >> count;
    cout << " Enter a number of objects to choose: ";
    cin >> choose;

    cout << "There are " << permutations(count, choose)
         << " ways to choose " << choose << " objects from "
         << count << " items." << endl;

    return 0;
}

double permutations(int n, int k) {
    double result = 1;
    for (int i = n - k + 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}
