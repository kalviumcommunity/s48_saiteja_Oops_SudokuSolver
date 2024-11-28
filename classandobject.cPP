#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Base class for validation
class MoveValidator {
public:
    virtual bool validate(int row, int col, int num) const = 0;
    virtual ~MoveValidator() = default;
};

// ClassicSudokuValidator: Implements basic validation rules
class ClassicSudokuValidator : public MoveValidator {
public:
    bool validate(int row, int col, int num) const override {
        return row >= 0 && row < 10 && col >= 0 && col < 10 && num >= 1 && num <= 10;
    }
};

// AdvancedSudokuValidator: Adds extra rules for row uniqueness
class AdvancedSudokuValidator : public MoveValidator {
private:
    const int (*grid)[10];

public:
    AdvancedSudokuValidator(const int g[10][10]) : grid(g) {}

    bool validate(int row, int col, int num) const override {
        if (row < 0 || row >= 10 || col < 0 || col >= 10 || num < 1 || num > 10)
            return false;

        // Check if num is already in the row
        for (int j = 0; j < 10; j++) {
            if (grid[row][j] == num) return false;
        }
        return true;
    }
};

// Base class for printing
class GridPrinter {
public:
    virtual void print(const int grid[10][10]) const = 0;
    virtual ~GridPrinter() = default;
};

// SimpleGridPrinter: Prints grid top to bottom
class SimpleGridPrinter : public GridPrinter {
public:
    void print(const int grid[10][10]) const override {
        for (int i = 9; i >= 0; i--) {
            for (int j = 0; j < 10; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// FancyGridPrinter: Adds row and column headers
class FancyGridPrinter : public GridPrinter {
public:
    void print(const int grid[10][10]) const override {
        cout << "   ";
        for (int j = 0; j < 10; j++) cout << j << " ";
        cout << endl;

        for (int i = 9; i >= 0; i--) {
            cout << i << "  ";
            for (int j = 0; j < 10; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// SudokuGrid: Manages the Sudoku grid
class SudokuGrid {
private:
    int grid[10][10];
    MoveValidator* validator;

public:
    SudokuGrid(int initialGrid[10][10], MoveValidator* mv) : validator(mv) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                grid[i][j] = initialGrid[i][j];
            }
        }
    }

    void placeNumber(int row, int col, int num) {
        if (validator->validate(row, col, num)) {
            grid[row][col] = num;
            cout << "Move accepted!\n";
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }

    void printGrid(const GridPrinter& printer) const {
        printer.print(grid);
    }

    bool isSolved() const {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (grid[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }
};

// Main function
int main() {
    int puzzle[10][10] = {
        {1, 0, 0, 4, 0, 6, 0, 0, 0, 2},
        {0, 3, 0, 0, 0, 0, 5, 0, 0, 0},
        {0, 0, 7, 0, 0, 0, 0, 0, 6, 0},
        {0, 0, 0, 8, 0, 0, 0, 4, 0, 0},
        {9, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {0, 4, 0, 0, 0, 7, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 2, 0, 0, 5, 0, 0, 0, 0},
        {0, 6, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 5}
    };

    // Use AdvancedSudokuValidator and FancyGridPrinter
    AdvancedSudokuValidator validator(puzzle);
    SudokuGrid sudoku(puzzle, &validator);
    FancyGridPrinter printer;

    cout << "Sudoku Grid before solving:" << endl;
    sudoku.printGrid(printer);

    string input;
    while (true) {
        cout << "Enter your move (R <row> C <col> <num>) or type 'exit' to quit: ";
        getline(cin, input);

        if (input == "exit") {
            cout << "Thank you!" << endl;
            break;
        }

        char r, c;
        int row, col, num;
        istringstream iss(input);
        if (iss >> r >> row >> c >> col >> num) {
            if (r == 'R' && c == 'C') {
                sudoku.placeNumber(row, col, num);
                sudoku.printGrid(printer);

                if (sudoku.isSolved()) {
                    cout << "Congratulations! You've solved the Sudoku!\n";
                    break;
                }
            } else {
                cout << "Invalid input! Please use 'R <row> C <col> <num>'.\n";
            }
        } else {
            cout << "Invalid format! Use 'R <row> C <col> <num>'.\n";
        }
    }

    return 0;
}
