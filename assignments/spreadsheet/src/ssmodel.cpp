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

void yieldRefsFromExpression(const Expression* exp, Set<std::string>& refs) {
    if (exp->getType() == IDENTIFIER) {
        refs.add(((const IdentifierExp*)exp)->getIdentifierName());
    } else if (exp->getType() == COMPOUND) {
        auto compound = (const CompoundExp*)exp;
        yieldRefsFromExpression(compound->getLHS(), refs);
        yieldRefsFromExpression(compound->getRHS(), refs);
    }
}

bool SSModel::formsCycle(node* dependent, const Set<std::string>& refs) {
    if (dependent == nullptr) {
        return false;
    } else if (refs.contains(dependent->name)) {
        return true;
    }

    for (arc* dependency : dependent->outgoing) {
        if (formsCycle(dependency->finish, refs)) {
            return true;
        }
    }

    return false;
}

SSModel::SSModel(int nRows, int nCols, SSView* view) {
    _numRows = nRows;
    _numCols = nCols;
    _view = view;
    _spreadsheet = new graph();
    _evalContext = new SpreadsheetEvaluationContext(this);
}

SSModel::~SSModel() {
    delete _spreadsheet;
    delete _evalContext;
}

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
    Expression* exp = parseExp(scanner, *this);
    node* cell = getCell(cellname);
    setCell(cell, exp);
    displayCell(cell);
}

void SSModel::setCell(node* cell, Expression* exp) {
    Set<std::string> refs;
    yieldRefsFromExpression(exp, refs);

    if (formsCycle(cell, refs)) {
        error("Cyclic reference");
    } else {
        cleanCell(cell);
        cell->exp = exp;
        _spreadsheet->nodes.add(cell);
        _spreadsheet->index[cell->name] = cell;
        addDependencies(cell, refs);
    }
}

void SSModel::displayCell(node* cell) {
    if (cell->exp->getType() == TEXTSTRING) {
        auto exp = static_cast<TextStringExp*>(cell->exp);
        _view->displayCell(cell->name, exp->toString());
    } else {
        double expValue = cell->exp->eval(*_evalContext);
        _view->displayCell(cell->name, realToString(expValue));
    }
}

node* SSModel::getCell(const std::string& cellname) {
    node* cell = _spreadsheet->index[cellname];

    if (cell == nullptr) {
        cell = new node();
        cell->name = cellname;
        cell->exp = nullptr;
    }

    return cell;
}

void SSModel::cleanCell(node* cell) {
    if (cell->exp != nullptr)
        delete cell->exp;

    for (arc* ref : cell->incoming) {
        ref->start->outgoing.remove(ref);
        delete ref;
    }

    cell->incoming.clear();
}

void SSModel::addDependencies(node* dependent, const Set<std::string>& refs) {
    for (const std::string& ref : refs) {
        node* refCell = getCell(ref);
        _spreadsheet->nodes.add(refCell);
        _spreadsheet->index[ref] = refCell;
        addDependency(dependent, refCell);
    }
}

void SSModel::addDependency(node* dependent, node* ref) {
    arc* dependency = new arc();
    dependency->start = ref;
    dependency->finish = dependent;
    ref->outgoing.add(dependency);
    dependent->incoming.add(dependency);
    _spreadsheet->arcs.add(dependency);
}

void SSModel::printCellInformation(const string& cellname) const {
    if (!_spreadsheet->index.containsKey(cellname)) {
        cout << "The cell is empty." << endl;
    } else {
        cout << "Cell Formula: " << cellname << " = "
             << _spreadsheet->index[cellname]->exp->toString() << endl;
    }
}

void SSModel::writeToStream(ostream& outfile) const {
    for (node* cell: _spreadsheet->nodes) {
        outfile << cell->name << " = ";

        if (cell->exp->getType() == TEXTSTRING) {
            auto text = static_cast<TextStringExp*>(cell->exp);
            outfile << text->getTextStringValue() << std::endl;
        } else {
            outfile << cell->exp->toString() << std::endl;
        }
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
    for (node* cell : _spreadsheet->nodes) {
        cleanCell(cell);
        delete cell;
    }

    for (arc* dependency : _spreadsheet->arcs)
        delete dependency;

    _spreadsheet->nodes.clear();
    _spreadsheet->arcs.clear();
    _spreadsheet->index.clear();
    _view->displayEmptySpreadsheet();
}


double SSModel::getCellValue(const std::string& cellname) const {
    if (!_spreadsheet->index.containsKey(cellname)) {
        return .0;
    }

    Expression* exp = _spreadsheet->index[cellname]->exp;

    if (exp == nullptr) {
        return .0;
    }

    return exp->eval(*_evalContext);
}

SpreadsheetEvaluationContext::~SpreadsheetEvaluationContext() {
}

double SpreadsheetEvaluationContext::getValue(const std::string& var) const {
    return _spreadsheet->getCellValue(var);
}

bool SpreadsheetEvaluationContext::isDefined(const std::string& var) const {
    return _spreadsheet->nameIsValid(var);
}
