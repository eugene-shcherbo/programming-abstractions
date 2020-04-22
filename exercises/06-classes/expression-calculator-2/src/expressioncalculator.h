
#ifndef _expressioncalculator_
#define _expressioncalculator_

#include <string>
#include "map.h"

class ExpressionCalculator {
public:
    double evaluate(std::string statemet);

private:
    Map<std::string, double> variables;
    double getVariableOrValue(std::string operand);
    double assignVariable(std::string name, std::string expression);
    double calc(std::string op, std::string lOperand, std::string rOperand);
};

#endif
