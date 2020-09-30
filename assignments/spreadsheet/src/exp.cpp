/**
 * File: exp.cpp
 * -------------
 * This file implements the exp.h interface.
 */

#include <string>
#include "exp.h"
#include "strlib.h"
#include "error.h"
using namespace std;

/**
 * Implementation notes: Expression
 * --------------------------------
 * The Expression class itself implements only those methods that
 * are not designated as pure virtual.
 */

Expression::Expression() {
   /* Empty */
}

Expression::~Expression() {
   /* Empty */
}

/**
 * Implementation notes: DoubleExp
 * -------------------------------
 * The ConstantExp subclass represents a numeric constant.  The eval
 * method simply returns that value.
 */

DoubleExp::DoubleExp(double value) {
   this->value = value;
}

double DoubleExp::eval(EvaluationContext& /* context */) const {
   return value;
}

string DoubleExp::toString() const {
   return realToString(value);
}

ExpressionType DoubleExp::getType() const {
   return DOUBLE;
}

double DoubleExp::getDoubleValue() const {
   return value;
}

/**
 * Implementation notes: TextStringExp
 * -----------------------------------
 * The IdentifierExp subclass represents a text string constant.  The
 * implementation of eval simply returns 0.0.
 */

TextStringExp::TextStringExp(const string& str) {
    this->str = str;
}

double TextStringExp::eval(EvaluationContext& /* context */) const {
    return 0.0;
}

string TextStringExp::toString() const {
    return str;
}

ExpressionType TextStringExp::getType() const {
    return TEXTSTRING;
}

string TextStringExp::getTextStringValue() const {
    return '"' + str + '"';
}

/**
 * Implementation notes: IdentifierExp
 * -----------------------------------
 * The IdentifierExp subclass represents a variable name.  The
 * implementation of eval looks up that name in the evaluation context.
 */

IdentifierExp::IdentifierExp(const string& name) {
   this->name = name;
}

double IdentifierExp::eval(EvaluationContext& context) const {
   if (!context.isDefined(name)) error("Invalid cell name " + name);
   return context.getValue(name);
}

string IdentifierExp::toString() const {
   return name;
}

ExpressionType IdentifierExp::getType() const {
   return IDENTIFIER;
}

string IdentifierExp::getIdentifierName() const {
   return name;
}

/**
 * Implementation notes: CompoundExp
 * ---------------------------------
 * The implementation of eval for CompoundExp evaluates the left and right
 * subexpressions recursively and then applies the operator.  Assignment is
 * treated as a special case because it does not evaluate the left operand.
 */

CompoundExp::CompoundExp(const string& op, const Expression *lhs, const Expression *rhs) {
   this->op = op;
   this->lhs = lhs;
   this->rhs = rhs;
}

CompoundExp::~CompoundExp() {
   delete lhs;
   delete rhs;
}

double CompoundExp::eval(EvaluationContext & context) const {
   double right = rhs->eval(context);
   double left = lhs->eval(context);
   if (op == "+") return left + right;
   if (op == "-") return left - right;  
   if (op == "*") return left * right;
   if (op == "/") return left / right; // divide by 0.0 gives ±INF
    
   error("Illegal operator in expression.");
}

string CompoundExp::toString() const {
   return '(' + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
}

ExpressionType CompoundExp::getType() const {
   return COMPOUND;
}

string CompoundExp::getOperator() const {
   return op;
}

const Expression *CompoundExp::getLHS() const {
   return lhs;
}

const Expression *CompoundExp::getRHS() const {
   return rhs;
}

/**
 * Implementation notes: FunctionExp
 * ---------------------------------
 * The implementation of eval for FunctionExp asks the model to
 * evaluate the function for a range defined as leftCorner and rightCorner.
 */

FunctionExpression::FunctionExpression(const string& funcName, RangeFn func, Range cellRange)
    : _func(func), _range(cellRange)
{
    _funcName = funcName;
}

double FunctionExpression::eval(EvaluationContext & context) const {
    if (_func == nullptr) return .0;
    Vector<double> values;
    Set<string> variables;
    _range.yieldAllValues(variables);
    context.getValues(variables, values);
    return _func(values);
}

string FunctionExpression::toString() const {
    return _funcName + '(' + _range.leftCorner() + ":" + _range.rightCorner() + ')';
}

ExpressionType FunctionExpression::getType() const {
    return FUNCTION;
}

EvaluationContext::~EvaluationContext() {}
