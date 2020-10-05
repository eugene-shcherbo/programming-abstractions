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
#include "queue.h"
using namespace std;

void topologicalSort(const node* graph, Vector<node*>& vertexes);

void SSModel::yieldRefsFromExpression(const Expression* exp, Set<std::string>& refs) {
    if (exp->getType() == IDENTIFIER) {
        refs.add(((const IdentifierExp*)exp)->getIdentifierName());
    } else if (exp->getType() == FUNCTION) {
        auto func = (const FunctionExpression*)exp;
        func->getRange().yieldAllValues(refs);
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
    _spreadsheet = new Graph();
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

    int col = loc.col - 'A' + 1;
    int row = loc.row;

    return col >= 1 && col <= _numCols && row >= 1 && row <= _numRows;
}

void SSModel::setCellFromScanner(const string& cellname, TokenScanner& scanner) {
    Expression* exp = parseExp(scanner, *this);
    node* cell = getCell(cellname);
    setCell(cell, exp);
    displayCell(cell);
    updateDependencies(cell);
}

void SSModel::setCell(node* cell, Expression* exp) {
    Set<std::string> refs;
    yieldRefsFromExpression(exp, refs);

    if (formsCycle(cell, refs)) {
        error("Cell formula would introduce a cycle.");
    } else {
        _spreadsheet->cleanNode(cell);
        cell->exp = exp;
        _spreadsheet->addNode(cell);
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

void SSModel::updateDependencies(node* cell) {
    Vector<node*> dependencies;
    topologicalSort(cell, dependencies);

    for (node* vertex : dependencies) {
        displayCell(vertex);
    }
}

node* SSModel::getCell(const std::string& cellname) {
    node* cell = _spreadsheet->getNode(cellname);

    if (cell == nullptr) {
        cell = new node();
        cell->name = cellname;
        cell->exp = nullptr;
    }

    return cell;
}

void SSModel::addDependencies(node* dependent, const Set<std::string>& refs) {
    for (const std::string& ref : refs) {
        node* refCell = getCell(ref);
        _spreadsheet->addNode(refCell);
        _spreadsheet->addArc(refCell, dependent);
    }
}

void SSModel::printCellInformation(const string& cellname) const {
    if (isCellEmpty(cellname)) {
        cout << "The cell is empty." << endl;
    } else {
        cout << "Cell Formula: " << cellname << " = "
             << _spreadsheet->getNode(cellname)->exp->toString() << endl;
    }
}

void SSModel::writeToStream(ostream& outfile) const {
    for (const node* cell: _spreadsheet->getNodes()) {
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
    _spreadsheet->clear();
    _view->displayEmptySpreadsheet();
}

double SSModel::getCellValue(const std::string& cellname) const {
    if (isCellEmpty(cellname)) return .0;
    Expression* exp = _spreadsheet->getNode(cellname)->exp;
    return exp->eval(*_evalContext);
}

bool SSModel::isCellEmpty(const std::string& cellname) const {
    return !_spreadsheet->hasNode(cellname)
           || _spreadsheet->getNode(cellname)->exp == nullptr;
}

void SSModel::getCellValues(const Set<std::string>& cellnames, Vector<double>& values) const {
    for (const string& cellname : cellnames) {
        values.add(getCellValue(cellname));
    }
}

SpreadsheetEvaluationContext::~SpreadsheetEvaluationContext() {
}

double SpreadsheetEvaluationContext::getValue(const std::string& var) const {
    return _spreadsheet->getCellValue(var);
}


void SpreadsheetEvaluationContext::getValues(const Set<std::string>& variables, Vector<double>& values) const {
    _spreadsheet->getCellValues(variables, values);
}

bool SpreadsheetEvaluationContext::isDefined(const std::string& var) const {
    return _spreadsheet->nameIsValid(var);
}

void topologicalSortVisit(node* cell, Stack<node*>& sorted, Set<node*>& visited) {
    if (visited.contains(cell)) return;

    for (const arc* arc : cell->outgoing) {
        topologicalSortVisit(arc->finish, sorted, visited);
    }

    visited.add(cell);
    sorted.push(cell);
}

void topologicalSort(const node* cell, Vector<node*>& vertexes) {
    Stack<node*> sorted;
    Set<node*> visited;

    for (const arc* arc : cell->outgoing) {
        if (visited.contains(arc->finish)) continue;
        topologicalSortVisit(arc->finish, sorted, visited);
    }

    while (!sorted.isEmpty()) {
        vertexes.add(sorted.pop());
    }
}
