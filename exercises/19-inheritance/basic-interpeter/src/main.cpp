#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "error.h"
#include "strlib.h"
#include "set.h"
#include "exp.h"
#include "parser.h"
#include "exputil.h"
#include "pqueue.h"
#include "map.h"

using namespace std;

Expression* createFromString(string exp);
void executeProgram(Vector<Line*>& statements, EvaluationContext& context);
void addLine(Vector<Line*>& lines, Line* line, uint linenum);

int main() {
    Vector<Line*> lines;
    TokenScanner scanner;
    Expression* exp;
    EvaluationContext context;

    scanner.ignoreWhitespace();
    scanner.scanNumbers();

    while (true) {
        exp = nullptr;

        try {
            string line;
            getline(cin, line);

            if (line == "quit") break;

            if (line == "RUN") {
                context.setLineNum(0);
                executeProgram(lines, context);
                break;
            } else if (line == "quit") {
                break;
            } else {
                scanner.setInput(line);
                Line* line = readLine(scanner);
                addLine(lines, line, line->getNumber());
            }

        } catch (ErrorException& ex) {
            cerr << "Error: " << ex.getMessage() << endl;
        }

        if (exp != nullptr) delete exp;
    }

    return 0;
}

void addLine(Vector<Line*>& lines, Line* line, uint linenum) {
    uint size = static_cast<uint>(lines.size());

    if (linenum == size) {
        lines.add(line);
    } else if (linenum > size) {
        uint diff = linenum - size;
        while (diff > 0) {
            lines.add(nullptr);
            diff--;
        }
        lines.add(line);
    }
}

void executeProgram(Vector<Line*>& statements, EvaluationContext& context) {
    for (uint i = context.getLineNum(); i < statements.size(); i = context.getLineNum()) {
        context.setLineNum(i + 1);
        if (statements[i] == nullptr) continue;
        statements[i]->execute(context);
    }
}

Expression* createFromString(string exp) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(exp);
    return parseExp(scanner);
}
