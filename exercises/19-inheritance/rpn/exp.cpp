#include <string>
#include "error.h"
#include "strlib.h"
#include "exp.h"

/* Expression */

Expression::Expression() {}

Expression::~Expression() {}

double Expression::getConstantValue() const {
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

ConstantExp::ConstantExp(double val) {
    this->value = val;
}

double ConstantExp::eval(EvaluationContext& context) const {
    return value;
}

std::string ConstantExp::toString() const {
    return doubleToString(value);
}

double ConstantExp::getConstantValue() const {
    return value;
}

ExpressionType ConstantExp::getType() const {
    return CONSTANT;
}

/* Identifier Expression */

IdentifierExp::IdentifierExp(std::string varName) {
    name = varName;
}

double IdentifierExp::eval(EvaluationContext& context) const {
    if (!context.isDefined(name)) error(name + " is undefined");
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

/* Binary Expression */

BinaryExp::~BinaryExp() {
    delete lhs;
    delete rhs;
}

BinaryExp::BinaryExp(std::string op, Expression* lhs, Expression* rhs) {
    this->op = op;
    this->lhs = lhs;
    this->rhs = rhs;
}

double evalBinaryOperator(double left, double right, std::string op) {
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;

    if (op == "/") {
        if (right == .0) error("Division by 0");
        return left / right;
    }

    if (op == "%") {
        if (right == .0) error("Divistion by 0");
        return static_cast<int>(left) % static_cast<int>(right);
    }

    error("Illegal operator in expression");
    return 0;
}

double BinaryExp::eval(EvaluationContext& context) const {
    double right = rhs->eval(context);
    if (op == "=") {
        context.setValue(lhs->getIdentifierName(), right);
        return right;
    }
    double left = lhs->eval(context);
    return evalBinaryOperator(left, right, op);

}

std::string BinaryExp::toString() const {
    return '(' + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
}

std::string BinaryExp::getOperator() const {
    return op;
}

Expression* BinaryExp::getLhs() const {
    return lhs;
}

Expression* BinaryExp::getRhs() const {
    return rhs;
}

ExpressionType BinaryExp::getType() const {
    return BINARY;
}

/* Unary expression */

UnaryExp::~UnaryExp() {
    delete rhs;
}

UnaryExp::UnaryExp(std::string op, Expression* rhs) {
    this->op = op;
    this->rhs = rhs;
}

double evalUnaryOperator(double operand, std::string op) {
    if (op == "-") return -operand;
    error("Illegal operator in expression");
    return 0;
}

double UnaryExp::eval(EvaluationContext& context) const {
    double right = rhs->eval(context);
    return evalUnaryOperator(right, op);

}

std::string UnaryExp::toString() const {
    return op + rhs->toString();
}

std::string UnaryExp::getOperator() const {
    return op;
}

Expression* UnaryExp::getRhs() const {
    return rhs;
}

ExpressionType UnaryExp::getType() const {
    return UNARY;
}

/* Evaluation Context */
void EvaluationContext::setValue(std::string var, double value) {
    varTable[var] = value;
}

double EvaluationContext::getValue(std::string name) {
    return varTable[name];
}

bool EvaluationContext::isDefined(std::string var) {
    return varTable.containsKey(var);
}
