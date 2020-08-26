#ifndef Employee_h
#define Employee_h

#include <string>

class Employee {
public:
    std::string getName() const;
    virtual double getPay() const = 0;

    static Employee* hourly(std::string name, double hourlyRate, double hoursWorked);
    static Employee* commissioned(std::string name, double baseSalary, double commissionedRate, double salesVolume);
    static Employee* salaried(std::string name, double salary);
protected:
    Employee(std::string name);
private:
    std::string name;
};

class HourlyEmployee: public Employee {
public:
    HourlyEmployee(std::string name);

    double getPay() const override;
    void setHourlyRate(double rate);
    void setHoursWorked(double hours);
private:
    double hourlyRate;
    double hoursWorked;
};

class CommissionedEmployee: public Employee {
public:
    CommissionedEmployee(std::string name);

    double getPay() const override;
    void setBaseSalary(double dollars);
    void setCommissionRate(double rate);
    void setSalesVolume(double dollars);

private:
    double baseSalary;
    double commissionRate;
    double salesVolume;
};

class SalariedEmployee: public Employee {
public:
    SalariedEmployee(std::string name);

    double getPay() const override;
    void setSalary(double salary);

private:
    double salary;
};

#endif // Employee_h
