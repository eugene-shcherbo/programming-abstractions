#ifndef _vector_h_
#define _vector_h_

#include <string>
#include "error.h"

namespace collections {

    template <typename ValueType>
    class Grid {

    public:
        Grid();
        Grid(int rows, int cols);
        Grid(int rows, int cols, const ValueType& val);
        Grid(const Grid& other);
        ~Grid();

        const ValueType& get(int row, int col) const;
        void set(int row, int col, const ValueType& val);
        int height() const;
        int width() const;
        bool inBounds(int row, int col) const;
        bool isEmpty() const;
        void resize(int rows, int cols);
        int size() const;

        Grid& operator= (const Grid& other);

    private:
        Vector<Vector<ValueType>>* elements_;
        int rows_;
        int cols_;

        void deepCopy(const Grid& other);
    };

    template <typename ValueType>
    std::ostream& operator<<(std::ostream& os, const Grid<ValueType>& grid) {
        return os << toString(grid);
    }

    template <typename ValueType>
    Grid<ValueType>::Grid() {
        rows_ = 0;
        cols_ = 0;
        elements_ = new Vector<Vector<ValueType>>(rows_);
    }

    template <typename ValueType>
    Grid<ValueType>::Grid(int rows, int cols) : Grid(rows, cols, ValueType()) {
    }

    template <typename ValueType>
    Grid<ValueType>::Grid(int rows, int cols, const ValueType& val) {
        rows_ = rows;
        cols_ = cols;
        elements_ = new Vector<Vector<ValueType>>(rows, Vector<ValueType>(cols, val));
    }


    template <typename ValueType>
    Grid<ValueType>::Grid(const Grid& other) {
        deepCopy(other);
    }

    template <typename ValueType>
    Grid<ValueType>::~Grid() {
        delete elements_;
    }

    template <typename ValueType>
    const ValueType& Grid<ValueType>::get(int row, int col) const {
        if (!inBounds(row, col)) {
            error("");
        }
        return (*elements_)[row][col];
    }

    template <typename ValueType>
    void Grid<ValueType>::set(int row, int col, const ValueType& val) {
        if (!inBounds(row, col)) {
            error("");
        }
        (*elements_)[row][col] = val;
    }

    template <typename ValueType>
    bool Grid<ValueType>::inBounds(int row, int col) const {
        return row >= 0 && row < rows_ && col >= 0 && col < cols_;
    }

    template <typename ValueType>
    int Grid<ValueType>::height() const {
        return rows_;
    }

    template <typename ValueType>
    int Grid<ValueType>::width() const {
        return cols_;
    }

    template <typename ValueType>
    bool Grid<ValueType>::isEmpty() const {
        return rows_ == 0;
    }

    template <typename ValueType>
    void Grid<ValueType>::resize(int rows, int cols) {
        delete elements_;
        rows_ = rows;
        cols_ = cols;
        elements_ = new Vector<Vector<ValueType>>(rows, Vector<ValueType>(cols));
    }

    template <typename ValueType>
    int Grid<ValueType>::size() const {
        return rows_ * cols_;
    }

    template <typename ValueType>
    std::string toString(const Grid<ValueType>& grid) {
        std::string res = "{";

        for (int r = 0; r < grid.height(); r++) {
            res += "{";
            for (int c = 0; c < grid.width(); c++) {
                res += genericValueToString(grid.get(r, c));
                if (c < grid.width() - 1) {
                    res += ",";
                }
            }
            res += "}";
            if (r < grid.height() - 1) {
                res += ",\n";
            }
        }

        res += "}";

        return res;
    }

    template <typename ValueType>
    Grid<ValueType>& Grid<ValueType>::operator= (const Grid& other) {
        if (this != &other) {
            delete elements_;
            deepCopy(other);
        }
        return *this;
    }

    template <typename ValueType>
    void Grid<ValueType>::deepCopy(const Grid& other) {
        rows_ = other.rows_;
        cols_ = other.cols_;
        elements_ = new Vector<Vector<ValueType>>(rows_, Vector<ValueType>(cols_));
        for (int r = 0; r < rows_; r++) {
            for (int c = 0; c < cols_; c++) {
                set(r, c, other.get(r, c));
            }
        }
    }

}

#endif
