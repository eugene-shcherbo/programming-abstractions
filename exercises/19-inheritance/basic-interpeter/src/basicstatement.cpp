#include "basicstatement.h"

Statement::~Statement() {}

Statement* Statement::print(std::string varName, std::ostream& os) {
    return new PrintStatement(varName, os);
}

Statement* Statement::let(std::string varName, Expression* expr) {
    return new LetStatement(varName, expr);
}

Statement* Statement::ifThen(std::string op, Expression* lhs, Expression* rhs, uint branchNum) {
    return new IfThenStatement(op, lhs, rhs, branchNum);
}

PrintStatement::~PrintStatement() {}

void PrintStatement::execute(EvaluationContext& context) {
    if (!context.isDefined(varName)) {
        error(varName + " is undefined");
    }
    os << context.getValue(varName) << std::endl;
}

PrintStatement::PrintStatement(std::string varName, std::ostream& oss) : os(oss) {
    this->varName = varName;
}

LetStatement::~LetStatement() {}

void LetStatement::execute(EvaluationContext& context) {
    context.setValue(varName, value->eval(context));
}

LetStatement::LetStatement(std::string varName, Expression* expr) {
    this->varName = varName;
    value = expr;
}

IfThenStatement::~IfThenStatement() {}

void IfThenStatement::execute(EvaluationContext& context) {
    double left = lhs->eval(context);
    double right = rhs->eval(context);

    if (op == "<" && left < right) {
        context.setLineNum(branchNum);
    } else if (op == "<=" && left <= right) {
        context.setLineNum(branchNum);
    } else if (op == "==" && left == right) {
        context.setLineNum(branchNum);
    } else if (op == ">=" && left >= right) {
        context.setLineNum(branchNum);
    } else if (op == ">" && left > right) {
        context.setLineNum(branchNum);
    }
}

IfThenStatement::IfThenStatement(std::string op, Expression* lhs, Expression* rhs, uint branchNum) {
    this->op = op;
    this->lhs = lhs;
    this->rhs = rhs;
    this->branchNum = branchNum;
}

Line* Line::create(uint number, Statement* stm) {
    return new Line(number, stm);
}

Line::Line(uint number, Statement* stm) {
    this->number = number;
    this->statement = stm;
}

