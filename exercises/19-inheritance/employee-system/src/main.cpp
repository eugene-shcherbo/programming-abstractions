#include <iostream>
#include "vector.h"
#include "console.h"
#include "employee.h"

using namespace std;

int main() {
    Vector<Employee*> payroll;
    payroll.add(Employee::hourly("John K.", 96.153846, 2080));
    payroll.add(Employee::salaried("Peter P.", 1000000));
    payroll.add(Employee::commissioned("Charlie O.", 50000, 0.1, 100000));

    for (Employee* emp : payroll) {
        cout << emp->getName() << ": " << emp->getPay() << endl;
    }

    return 0;
}


