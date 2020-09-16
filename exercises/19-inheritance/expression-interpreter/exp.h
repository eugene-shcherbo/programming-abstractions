#ifndef EXP_H
#define EXP_H

#include <string>
#include "map.h"

class EvaluationContext;

enum ExpressionType { CONSTANT, IDENTIFIER, BINARY, UNARY };

class Expression {
public:
    Expression();
    virtual ~Expression();

    virtual double eval(EvaluationContext& context) const = 0;
    virtual std::string toString() const = 0;
    virtual ExpressionType getType() const = 0;

    virtual double getConstantValue() const;
    virtual std::string getIdentifierName() const;
    virtual std::string getOperator() const;
    virtual Expression* getLhs() const;
    virtual Expression* getRhs() const;

    static Expression* newFrom(Expression* exp);
    static Expression* constant(double val);
    static Expression* binary(std::string op, Expression* lhs, Expression* rhs);
    static Expression* unary(std::string op, Expression* rhs);
    static Expression* identifier(std::string name);
};

class ConstantExp : public Expression {

public:
    ConstantExp(double value);

    double eval(EvaluationContext& context) const override;
    std::string toString() const override;
    ExpressionType getType() const override;
    double getConstantValue() const override;

private:
    double value;
};

class IdentifierExp : public Expression {

public:
    IdentifierExp(std::string name);

    double eval(EvaluationContext& context) const override;
    std::string toString() const override;
    ExpressionType getType() const override;
    std::string getIdentifierName() const override;

private:
    std::string name;
};

class BinaryExp : public Expression {

public:
    BinaryExp(std::string op, Expression* lhs, Expression* rhs);

    ~BinaryExp() override;
    double eval(EvaluationContext& context) const override;
    std::string toString() const override;
    ExpressionType getType() const override;
    std::string getOperator() const override;
    Expression* getLhs() const override;
    Expression* getRhs() const override;
private:
    std::string op;
    Expression* lhs;
    Expression* rhs;
};

class UnaryExp : public Expression {

public:
    UnaryExp(std::string op, Expression* rhs);

    ~UnaryExp() override;
    double eval(EvaluationContext& context) const override;
    std::string toString() const override;
    ExpressionType getType() const override;
    std::string getOperator() const override;
    Expression* getRhs() const override;
    Expression* getLhs() const override;

private:
    std::string op;
    Expression* rhs;
};

class EvaluationContext {

public:
    void setValue(std::string var, double value);
    double getValue(std::string name);
    bool isDefined(std::string var);

private:
    Map<std::string, double> varTable;
};

int calcPrecedence(std::string op);

#endif // EXP_H
