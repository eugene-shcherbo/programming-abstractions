/**
 * File: ssmodel.h
 * ---------------
 * This file defines the interface for SSModel class used in the
 * Stanford 1-2-3 spreadsheet program.
 */
#pragma once
#include <fstream>
#include <string>
#include "tokenscanner.h"
#include "ssview.h"
#include "graphtypes.h"

/**
 * This is a "forward reference" which informs the compiler there is a
 * class named Expression that we'll eventually get around to seeing the
 * full class interface for, but for now, we just need to know such a class
 * exists.
 */


class SpreadsheetEvaluationContext;
class Expression;
struct range;

/**
 * Class: SSModel
 * --------------
 * This is the starting interface for the spreadsheet data model class.  The 
 * public member functions listed here are used by other parts of the given code 
 * (i.e. controller/view) and thus need to be retained as is and implemented correctly. 
 * However the rest of the class (both public & private) is yours to design.
 */

class SSModel {
public:
		
/**
 * Constructor: SSModel
 * Usage: SSModel model(10, 20, vp);
 * --------------------------------
 * The constructor initializes a new empty data model of the given size 
 * which is to be displayed using the given SSView object. Whenever data 
 * in the model changes, this view is notified to re-display the
 * affected cells.
 */
    
    SSModel(int numRows, int numCols, SSView *ssview);

/**
 * Destructor: ~SSModel
 * Usage: delete mp;
 * -----------------
 * The destructor deallocates any storage for this model.
 */
    
	~SSModel();
		
/**
 * Member function: nameIsValid
 * Usage: if (model.nameIsValid(name))...
 * ------------------------------------------
 * This member function returns true if name is a valid string
 * name of a cell in this model, false otherwise. The string
 * must be in the proper format (column letter followed by row number)
 * and refer to a cell location within bounds for this model.
 */
    bool nameIsValid(const std::string& name) const;
	 
 /**
  * Member function: setCellFromScanner
  * Usage: model.setCellFromScanner("A1", scanner);
  * -----------------------------------------------
  * This member function reads an expression from the scanner and
  * stores it as the the contents for the named cell.  If there is
  * any problem with setting the cell's value (the expression is
  * malformed, contains a circular reference, etc.) error is called
  * and the cell's contents are unchanged.  If the contents were
  * successfully updated, the new cell is displayed in the view
  * and its dependent cells are updated as well.
  */
	
    void setCellFromScanner(const std::string& cellname, TokenScanner& scanner);

/**
 * Member function: printCellInformation
 * Usage: model.printCellInformation("A1");
 * ----------------------------------------
 * This member function prints the cell information for the named
 * cell to cout.  Cell information includes its current contents
 * and dependencies (and other information you choose to include).
 */
    
    void printCellInformation(const std::string& cellname) const;

/**
 * Member functions: writeToStream, readFromStream
 * Usage: model.writeToStream(outfile);
 *        model.readFromStream(infile);
 * --------------------------------
 * These member functions read/write model contents
 * to/from a stream.  The stream is assumed to be valid and open.
 * The file format consists of cell values, one per line, like this:
 *
 *      A1 = 3
 *      A2 = 4 * (A1 + 8)
 *      A3 = "a string"
 *
 * error is called if there is any trouble reading/writing
 * the file.
 */

    void writeToStream(std::ostream &outfile) const;
    void readFromStream(std::istream &infile);

/**
 * Member function: clear
 * Usage: model.clear();
 * --------------------------------
 * This member function empties all the cells of the spreadsheet.
 */

    void clear();

    /**
     * Member function: getCellValue
     * Usage: double value = model.getCellValue(cellname);
     * ---------------------------------------------------
     * This member function returns a value which occupy
     * the named cell. If the cell is a textstrign constant or empty,
     * the function returns 0.0.
     */

    double getCellValue(const std::string& cellname) const;

    void getCellValues(const Set<std::string>& cellnames, Vector<double>& values) const;

    /**
     * Member function: getRangeValues
     * Usage: Vector<double> values = model.getRangeValues(range);
     * ---------------------------------------------------
     * This member function returns a vector with values of each cell
     * in the range.
     */

    Vector<double> getRangeValues(range cellRange) const;

private:

    int _numRows;
    int _numCols;
    SSView* _view;
    Graph* _spreadsheet;
    SpreadsheetEvaluationContext* _evalContext;
    Map<std::string, double> _cache;

    node* getCell(const std::string& cellName) const;
    void setCell(node* cell, Expression* exp);
    void displayCell(node* cell) const;
    bool formsCycle(node* dependent, const Set<std::string>& refs);
    void addDependencies(node* dependent, const Set<std::string>& refs);
    bool isCellEmpty(const std::string& cellname) const;
    void yieldRefsFromExpression(const Expression* exp, Set<std::string>& refs);
    void updateDependencies(node* cell);
    void setCellValue(node* cell, double value);
};


class SpreadsheetEvaluationContext : public EvaluationContext {

public:
    SpreadsheetEvaluationContext(const SSModel* spreadSheetModel) {
        _spreadsheet = spreadSheetModel;
    }

    ~SpreadsheetEvaluationContext() override;
    double getValue(const std::string &var) const override;
    void getValues(const Set<std::string>& variables, Vector<double>& values) const override;
    bool isDefined(const std::string &var) const override;

private:
    const SSModel* _spreadsheet;
};
