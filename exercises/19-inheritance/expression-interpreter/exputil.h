#ifndef EXPUTIL_H
#define EXPUTIL_H

#include <string>
#include "set.h"
#include "exp.h"

void yieldVariables(Expression* exp, Set<std::string>& variables);

Expression* changeVariable(Expression* exp, std::string oldName, std::string newName);

bool expMatch(Expression* exp1, Expression* exp2);

Expression* foldConstants(const Expression* exp);

std::string unparse(const Expression* expr, int precedence = 0);

Expression* differentiate(Expression* exp, std::string varName);

#endif // EXPUTIL_H
