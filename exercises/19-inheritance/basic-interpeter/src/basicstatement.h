#ifndef BASICSTATEMENT_H
#define BASICSTATEMENT_H

#include <iostream>
#include "exp.h"

class Statement {
public:
    virtual ~Statement();
    virtual void execute(EvaluationContext& context) = 0;

    static Statement* print(std::string varName, std::ostream& os);
    static Statement* let(std::string varName, Expression* expr);
    static Statement* ifThen(std::string op, Expression* lhs, Expression* rhs, uint branchNum);
};

class PrintStatement : public Statement {
public:
    ~PrintStatement() override;
    void execute(EvaluationContext& context) override;

private:
    std::ostream& os;
    std::string varName;

    PrintStatement(std::string varName, std::ostream& os);

    friend class Statement;
};

class LetStatement : public Statement {
public:
    ~LetStatement() override;
    void execute(EvaluationContext& context) override;

private:
    Expression* value;
    std::string varName;

    LetStatement(std::string varName, Expression* value);

    friend class Statement;
};

class IfThenStatement : public Statement {

public:
    ~IfThenStatement() override;
    void execute(EvaluationContext& context) override;

private:
    Expression* lhs;
    Expression* rhs;
    std::string op;
    uint branchNum;

    IfThenStatement(std::string op, Expression* lhs, Expression* rhs, uint branchNum);

    friend class Statement;
};

class Line {

public:
    static Line* create(uint number, Statement* stm);

    uint getNumber() const { return number;  }
    void execute(EvaluationContext& context) const { statement->execute(context); }

private:
    uint number;
    Statement* statement;

    Line(uint number, Statement* stm);
};



#endif // BASICSTATEMENT_H
