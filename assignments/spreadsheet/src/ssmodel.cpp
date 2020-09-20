/**
 * File: ssmodel.cpp
 * ------------------
 * This file will contain the implementation of the SSModel class (once you
 * have finished it!
 */
 
#include "ssmodel.h"
#include "exp.h"
#include "parser.h"
#include "ssutil.h"
using namespace std;

int colNum(char letter) {
    return (letter - 'A') + 1;
}

SSModel::SSModel(int nRows, int nCols, SSView* view) {
    _numRows = nRows;
    _numCols = nCols;
    _view = view;
}

SSModel::~SSModel() {}

bool SSModel::nameIsValid(const string& cellname) const {
    location loc;

    if (!stringToLocation(cellname, loc)) {
        return false;
    }

    int col = colNum(loc.col);
    int row = loc.row;

    return col >= 1 && col <= _numCols && row >= 1 && row <= _numRows;
}

void SSModel::setCellFromScanner(const string& cellname, TokenScanner& scanner) {
    Expression* exp = parseExp(scanner);

    if (_cells.containsKey(cellname)) {
        delete _cells[cellname];
    }

    Cell* cell = new Cell(exp);
    _cells[cellname] = cell;
    _view->displayCell(cellname, cell->stringValue());
}

void SSModel::printCellInformation(const string& cellname) const {
    if (_cells.containsKey(cellname)) {
        cout << "The cell is empty." << endl;
    }
}

void SSModel::writeToStream(ostream& outfile) const {
    for (std::string cellname: _cells) {
        Cell* cell = _cells[cellname];
        outfile << cellname << " = " << cell->stringExpression() << endl;
    }
}

void SSModel::readFromStream(istream& infile) {
    clear();

    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.scanStrings();

    string line;
    while (getline(infile, line)) {
        scanner.setInput(line);
        std::string cellname = scanner.nextToken();
        if (!nameIsValid(cellname))
            error("Invalid cell name " + cellname);
        if (scanner.nextToken() != "=")
            error("= expected.");
        setCellFromScanner(cellname, scanner);
    }
}

void SSModel::clear() {
    for (std::string cellname: _cells) {
        delete _cells[cellname];
    }
    _cells.clear();
    _view->displayEmptySpreadsheet();
}

SSModel::Cell::Cell(Expression* exp) {
    _exp = exp;
    _hasValue = false;
}

SSModel::Cell::~Cell() {
    delete _exp;
}

double SSModel::Cell::getValue() {
    EvaluationContext context;

    if (_hasValue) {
        return _value;
    } else {
        double res =  _exp->eval(context);
        _hasValue = true;
        _value = res;
        return res;
    }
}

std::string SSModel::Cell::stringValue() {
    if (_exp->getType() == TEXTSTRING) {
        return _exp->toString();
    } else {
        return realToString(getValue());
    }
}

std::string SSModel::Cell::stringExpression() {
    if (_exp->getType() == TEXTSTRING) {
        return static_cast<TextStringExp*>(_exp)->getTextStringValue();
    } else {
        return _exp->toString();
    }
}
