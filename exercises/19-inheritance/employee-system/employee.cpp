#include "employee.h"

Employee::Employee(std::string name) {
    this->name = name;
}

std::string Employee::getName() const {
    return name;
}

Employee* Employee::hourly(std::string name, double hourlyRate, double hoursWorked) {
    HourlyEmployee* hourlyEmp = new HourlyEmployee(name);
    hourlyEmp->setHourlyRate(hourlyRate);
    hourlyEmp->setHoursWorked(hoursWorked);
    return hourlyEmp;
}

Employee* Employee::commissioned(std::string name, double baseSalary, double commissionedRate, double salesVolume) {
    CommissionedEmployee* emp = new CommissionedEmployee(name);
    emp->setBaseSalary(baseSalary);
    emp->setSalesVolume(salesVolume);
    emp->setCommissionRate(commissionedRate);
    return emp;
}

Employee* Employee::salaried(std::string name, double salary) {
    SalariedEmployee* emp = new SalariedEmployee(name);
    emp->setSalary(salary);
    return emp;
}

HourlyEmployee::HourlyEmployee(std::string name)
    : Employee(name)
{}

double HourlyEmployee::getPay() const {
    return hoursWorked * hourlyRate;
}

void HourlyEmployee::setHourlyRate(double rate) {
    hourlyRate = rate;
}

void HourlyEmployee::setHoursWorked(double hours) {
    hoursWorked = hours;
}

CommissionedEmployee::CommissionedEmployee(std::string name)
    : Employee(name)
{}

double CommissionedEmployee::getPay() const {
    return baseSalary + commissionRate * salesVolume;
}

void CommissionedEmployee::setBaseSalary(double dollars) {
    baseSalary = dollars;
}

void CommissionedEmployee::setCommissionRate(double rate) {
    commissionRate = rate;
}

void CommissionedEmployee::setSalesVolume(double dollars) {
    salesVolume = dollars;
}

SalariedEmployee::SalariedEmployee(std::string name)
    : Employee(name)
{}

double SalariedEmployee::getPay() const {
    return salary;
}

void SalariedEmployee::setSalary(double salary) {
    this->salary = salary;
}
