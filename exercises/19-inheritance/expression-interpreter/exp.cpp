#include <string>
#include "error.h"
#include "strlib.h"
#include "exp.h"

/* Expression */

Expression::Expression() {}

Expression::~Expression() {}

int Expression::getConstantValue() const {
    error("getConstantValue: Illegal expression type");
    return 0;
}

std::string Expression::getIdentifierName() const {
    error("getIdentifierName: Illegal expression type");
    return "";
}

std::string Expression::getOperator() const {
    error("getOperator: Illegal expression type");
    return "";
}

Expression* Expression::getLhs() const {
    error("getConstantValue: Illegal expression type");
    return nullptr;
}

Expression* Expression::getRhs() const {
    error("getConstantValue: Illegal expression type");
    return nullptr;
}

/* Constant Expression */

ConstantExp::ConstantExp(int val) {
    this->value = val;
}

int ConstantExp::eval(EvaluationContext& context) const {
    return value;
}

std::string ConstantExp::toString() const {
    return integerToString(value);
}

int ConstantExp::getConstantValue() const {
    return value;
}

ExpressionType ConstantExp::getType() const {
    return CONSTANT;
}

/* Identifier Expression */

IdentifierExp::IdentifierExp(std::string name) {
    this->name = name;
}

int IdentifierExp::eval(EvaluationContext& context) const {
    if (!context.isDefined(name)) error(name + "is undefined");
    return context.getValue(name);
}

std::string IdentifierExp::toString() const {
    return name;
}

std::string IdentifierExp::getIdentifierName() const {
    return name;
}

ExpressionType IdentifierExp::getType() const {
    return IDENTIFIER;
}

/* Compound Expression */

CompoundExp::~CompoundExp() {
    delete lhs;
    delete rhs;
}

CompoundExp::CompoundExp(std::string op, Expression* lhs, Expression* rhs) {
    this->op = op;
    this->lhs = lhs;
    this->rhs = rhs;
}

int evalOperator(int left, int right, std::string op) {
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;

    if (op == "/") {
        if (right == 0) error("Division by 0");
        return left / right;
    }

    if (op == "%") {
        if (right == 0) error("Divistion by 0");
        return left % right;
    }

    error("Illegal operator in expression");
    return 0;
}

int CompoundExp::eval(EvaluationContext& context) const {
    int right = rhs->eval(context);
    if (op == "=") {
        context.setValue(lhs->getIdentifierName(), right);
        return right;
    }
    int left = lhs->eval(context);
    return evalOperator(left, right, op);

}

std::string CompoundExp::toString() const {
    return '(' + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
}

std::string CompoundExp::getOperator() const {
    return op;
}

Expression* CompoundExp::getLhs() const {
    return lhs;
}

Expression* CompoundExp::getRhs() const {
    return rhs;
}

ExpressionType CompoundExp::getType() const {
    return COMPOUND;
}

/* Evaluation Context */
void EvaluationContext::setValue(std::string var, int value) {
    varTable[var] = value;
}

int EvaluationContext::getValue(std::string name) {
    return varTable[name];
}

bool EvaluationContext::isDefined(std::string var) {
    return varTable.containsKey(var);
}
