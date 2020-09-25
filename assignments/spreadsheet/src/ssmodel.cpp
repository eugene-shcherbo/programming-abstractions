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

Set<std::string> getCellsInRange(range cellRange) {
    return Set<std::string> { "A1", "B1", "C1" };
}

void yieldCellsFromExpression(const Expression* exp, Set<std::string>& cells) {
    if (exp->getType() == IDENTIFIER) {
        cells.add(((const IdentifierExp*)exp)->getIdentifierName());
    } else if (exp->getType() == FUNCTION) {
        auto function = (const FunctionExpression*)exp;
        cells.addAll(getCellsInRange(function->getRange()));
    } else if (exp->getType() == COMPOUND) {
        auto compound = (const CompoundExp*)exp;
        yieldCellsFromExpression(compound->getLHS(), cells);
        yieldCellsFromExpression(compound->getRHS(), cells);
    }
}

bool detectCycle(node* from, const Set<std::string>& toCells) {
    if (from == nullptr) return false;
    else if (toCells.contains(from->name)) return true;

    for (arc* arc : from->outgoing) {
        if (detectCycle(arc->finish, toCells)) return true;
    }

    return false;
}

bool detectCyclicReference(graph* dependencies, const std::string& fromCell, const Set<std::string>& toCells) {
    node* fromNode = dependencies->index[fromCell];
    if (fromNode == nullptr) return toCells.contains(fromCell);
    else return detectCycle(fromNode, toCells);
}

void addNode(graph* dependencies, const string& cellname) {
    node* newNode = new node;
    newNode->name = cellname;
    dependencies->nodes.add(newNode);
    dependencies->index[cellname] = newNode;
}

node* getOrCreateNode(graph* dependencies, const string& cellname) {
    node* node = dependencies->index[cellname];

    if (node == nullptr)
        addNode(dependencies, cellname);

    return node;
}

void addDependency(graph* dependencies, node* impact, node* dependent) {
    arc* dependency = new arc;
    dependency->start = impact;
    dependency->finish = dependent;

    impact->outgoing.add(dependency);
    dependent->incoming.add(dependency);

    dependencies->arcs.add(dependency);
}

SSModel::SSModel(int nRows, int nCols, SSView* view) {
    _numRows = nRows;
    _numCols = nCols;
    _view = view;
    _dependencies = new graph();
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
    Expression* exp = parseExp(scanner, *this);
    Set<std::string> cells;
    yieldCellsFromExpression(exp, cells);

    if (detectCyclicReference(_dependencies, cellname, cells)) {
        error("Cyclic reference");
    }

    node* dependent = getOrCreateNode(_dependencies, cellname);

    for (arc* inc : dependent->incoming) {
        inc->start->outgoing.remove(inc);
        delete inc;
    }

    dependent->incoming.clear();

    for (const std::string& cell : cells) {
        node* impact = getOrCreateNode(_dependencies, cell);
        addDependency(_dependencies, impact, dependent);
    }

    // This is double work, because I already done this with graph of dependencies (the name is also not best)
    if (_cells.containsKey(cellname)) {
        delete _cells[cellname];
    }

    Cell* cell = new Cell(this, exp);
    _cells[cellname] = cell;
    _view->displayCell(cellname, cell->stringValue());
}

void SSModel::printCellInformation(const string& cellname) const {
    if (!_cells.containsKey(cellname)) {
        cout << "The cell is empty." << endl;
    } else {
        cout << "Cell Formula: " << cellname << " = " << _cells[cellname]->stringExpression() << endl;
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

double SSModel::getCellValue(const std::string& cellname) const {
    if (!nameIsValid(cellname)) error("Invalid cell name");
    Cell* cell = _cells[cellname];
    return cell == nullptr ? .0 : cell->getValue();
}

Vector<double> SSModel::getRangeValues(range cellRange) const {
    Vector<double> values;
    return Vector<double>{2, 3, 4};
}

SSModel::Cell::Cell(const SSModel* parent, Expression* exp) {
    _exp = exp;
    _hasValue = false;
    _parent = parent;
}

SSModel::Cell::~Cell() {
    delete _exp;
}

double SSModel::Cell::getValue() {
    EvaluationContext context(_parent);

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
