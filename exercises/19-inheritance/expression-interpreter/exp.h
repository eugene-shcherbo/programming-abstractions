#ifndef EXP_H
#define EXP_H

#include <string>
#include "map.h"

class EvaluationContext;

enum ExpressionType { CONSTANT, IDENTIFIER, COMPOUND };

class Expression {
public:
    Expression();
    virtual ~Expression();

    virtual int eval(EvaluationContext& context) const = 0;
    virtual std::string toString() const = 0;
    virtual ExpressionType getType() const = 0;

    virtual int getConstantValue() const;
    virtual std::string getIdentifierName() const;
    virtual std::string getOperator() const;
    virtual Expression* getLhs() const;
    virtual Expression* getRhs() const;
};

class ConstantExp : public Expression {

public:
    ConstantExp(int value);

    int eval(EvaluationContext &context) const override;
    std::string toString() const override;
    ExpressionType getType() const override;
    int getConstantValue() const override;

private:
    int value;
};

class IdentifierExp : public Expression {

public:
    IdentifierExp(std::string name);

    int eval(EvaluationContext &context) const override;
    std::string toString() const override;
    ExpressionType getType() const override;
    std::string getIdentifierName() const override;

private:
    std::string name;
};

class CompoundExp : public Expression {

public:
    CompoundExp(std::string op, Expression* lhs, Expression* rhs);

    ~CompoundExp() override;
    int eval(EvaluationContext &context) const override;
    std::string toString() const override;
    ExpressionType getType() const override;
    std::string getOperator() const override;
    Expression * getLhs() const override;
    Expression * getRhs() const override;

private:
    std::string op;
    Expression* lhs;
    Expression* rhs;
};

class EvaluationContext {

public:
    void setValue(std::string var, int value);
    int getValue(std::string name);
    bool isDefined(std::string var);

private:
    Map<std::string, int> varTable;
};

#endif // EXP_H
