#include "strlib.h"
#include "set.h"
#include "exputil.h"

Expression* changeVariable(Expression* exp, std::string oldName, std::string newName) {
    ExpressionType expType = exp->getType();

    if (expType == IDENTIFIER) {
        std::string currName = exp->getIdentifierName();
        return Expression::identifier(currName == oldName ? newName : currName);
    } else if (expType == BINARY) {
        Expression* changedLhs = changeVariable(exp->getLhs(), oldName, newName);
        Expression* changedRhs = changeVariable(exp->getRhs(), oldName, newName);
        return Expression::binary(exp->getOperator(), changedLhs, changedRhs);
    } else if (expType == UNARY) {
        Expression* changedOperand = changeVariable(exp->getRhs(), oldName, newName);
        return Expression::unary(exp->getOperator(), changedOperand);
    } else {
        return Expression::constant(exp->getConstantValue());
    }
}

bool expMatch(Expression* exp1, Expression* exp2) {
    ExpressionType exp1Type = exp1->getType();
    ExpressionType exp2Type = exp2->getType();

    if (exp1Type != exp2Type) return false;

    if (exp1Type == CONSTANT) return exp1->getConstantValue() == exp2->getConstantValue();

    if (exp1Type == IDENTIFIER) return exp1->getIdentifierName() == exp2->getIdentifierName();

    if (exp1Type == BINARY) {
        return exp1->getOperator() == exp2->getOperator()
               && expMatch(exp1->getLhs(), exp2->getLhs())
               && expMatch(exp1->getRhs(), exp2->getRhs());
    }

    if (exp1Type == UNARY) {
        return exp1->getOperator() == exp2->getOperator()
               && expMatch(exp1->getRhs(), exp1->getRhs());
    }

    return false;
}

Expression* foldConstantsInCompoundExp(const Expression* exp) {
    Expression* lhs = foldConstants(exp->getLhs());
    Expression* rhs = foldConstants(exp->getRhs());

    if (lhs->getType() == CONSTANT && rhs->getType() == CONSTANT) {
        EvaluationContext context;
        return Expression::constant(exp->eval(context));
    }

    if (exp->getType() == BINARY) {
        return Expression::binary(exp->getOperator(), lhs, rhs);
    } else {
        return Expression::unary(exp->getOperator(), rhs);
    }
}

Expression* foldConstants(const Expression* exp) {
    if (exp->getType() == CONSTANT) {
        return Expression::constant(exp->getConstantValue());
    } else if (exp->getType() == IDENTIFIER) {
        return Expression::identifier(exp->getIdentifierName());
    }

    return foldConstantsInCompoundExp(exp);
}

std::string unparse(const Expression* expr, int precedence) {
    if (expr->getType() == CONSTANT) {
        return realToString(expr->getConstantValue());
    } else if (expr->getType() == IDENTIFIER) {
        return expr->getIdentifierName();
    } else if (expr->getType() == BINARY) {
        int currPrecedence = calcPrecedence(expr->getOperator());

        std::string exprStr = unparse(expr->getLhs(), currPrecedence) + " " +
                         expr->getOperator() + " " +
                         unparse(expr->getRhs(), currPrecedence);

        if (precedence > currPrecedence) {
            return "(" + exprStr + ")";
        } else {
            return exprStr;
        }
    }

    return "";
}

void yieldVariables(Expression* exp, Set<std::string>& variables) {
    if (exp->getType() == IDENTIFIER) {
        variables.add(exp->getIdentifierName());
    } else if (exp->getType() == BINARY) {
        yieldVariables(exp->getLhs(), variables);
        yieldVariables(exp->getRhs(), variables);
    } else if (exp->getType() == UNARY) {
        yieldVariables(exp->getRhs(), variables);
    }
}

Expression* differentiateBinary(Expression* exp, std::string varName) {
    std::string op = exp->getOperator();
    Expression* left = differentiate(exp->getLhs(), varName);
    Expression* right = differentiate(exp->getRhs(), varName);

    if (op == "+" || op == "-") {
        return Expression::binary(op, left, right);
    } else if (op == "/" || op == "*") {
        Expression* newLeft = Expression::binary(op, exp->getLhs(), right);
        Expression* newRight = Expression::binary(op, exp->getRhs(), left);

        if (op == "*") {
            return Expression::binary("+", newLeft, newRight);
        } else {
            Expression* num = Expression::binary("-", newLeft, newRight);
            Expression* denum = Expression::binary("*", exp->getRhs(), exp->getRhs());
            return Expression::binary("/", num, denum);
        }
    }

    return nullptr;
}

Expression* differentiate(Expression* exp, std::string varName) {
    if (exp->getType() == CONSTANT) {
        return Expression::constant(0);
    } else if (exp->getType() == IDENTIFIER) {
        std::string identifierName = exp->getIdentifierName();
        return Expression::constant(varName == identifierName ? 1 : 0);
    } else if (exp->getType() == BINARY) {
        return differentiateBinary(exp, varName);
    }

    return nullptr;
}
