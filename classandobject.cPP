#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// GameStats Class: Manages global game statistics
@@ -25,51 +26,66 @@ int GameStats::totalMoves = 0;
int GameStats::totalPlayers = 0;
int GameStats::puzzlesSolved = 0;

// Player Class: Manages individual player details
class Player {
private:
    string name;
    int moves;
// Abstract MoveValidator Class: Open for adding new rules
class MoveValidator {
public:
    virtual bool validate(int row, int col, int num) const = 0;
    virtual ~MoveValidator() = default;
};

// ClassicSudokuValidator Class: Implements basic validation rules
class ClassicSudokuValidator : public MoveValidator {
public:
    Player(const string& playerName) : name(playerName), moves(0) {
        GameStats::incrementTotalPlayers();
    bool validate(int row, int col, int num) const override {
        return row >= 0 && row < 10 && col >= 0 && col < 10 && num >= 1 && num <= 10;
    }
};

    void incrementMoves() {
        moves++;
        GameStats::incrementTotalMoves();
    }
// Abstract GridPrinter Class: Open for custom printing logic
class GridPrinter {
public:
    virtual void print(const int grid[10][10]) const = 0;
    virtual ~GridPrinter() = default;
};

    string getName() const { return name; }
    int getMoves() const { return moves; }
// SimpleGridPrinter Class: Basic printing logic
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

// SudokuGrid Class: Manages the Sudoku grid and game logic
class SudokuGrid {
private:
    int grid[10][10];
    MoveValidator* validator;

public:
    SudokuGrid(int initialGrid[10][10]) {
    SudokuGrid(int initialGrid[10][10], MoveValidator* mv) : validator(mv) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                grid[i][j] = initialGrid[i][j];
            }
        }
    }

    void printGrid() const {
        for (int i = 9; i >= 0; i--) {
            for (int j = 0; j < 10; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
    void placeNumber(int row, int col, int num) {
        if (validator->validate(row, col, num)) {
            grid[row][col] = num;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }

    void placeNumber(int row, int col, int num) {
        grid[row][col] = num;
    void printGrid(const GridPrinter& printer) const {
        printer.print(grid);
    }

    bool isSolved() const {
@@ -85,6 +101,26 @@ public:
    }
};

// Player Class: Manages individual player details
class Player {
private:
    string name;
    int moves;

public:
    Player(const string& playerName) : name(playerName), moves(0) {
        GameStats::incrementTotalPlayers();
    }

    void incrementMoves() {
        moves++;
        GameStats::incrementTotalMoves();
    }

    string getName() const { return name; }
    int getMoves() const { return moves; }
};

// Main function
int main() {
    int puzzle[10][10] = {
@@ -105,10 +141,12 @@ int main() {
    getline(cin, playerName);

    Player player(playerName);
    SudokuGrid sudoku(puzzle);
    ClassicSudokuValidator validator;
    SudokuGrid sudoku(puzzle, &validator);
    SimpleGridPrinter printer;

    cout << "Sudoku Grid before solving:" << endl;
    sudoku.printGrid();
    sudoku.printGrid(printer);

    string input;
    while (true) {
@@ -124,18 +162,17 @@ int main() {
        int row, col, num;
        istringstream iss(input);
        if (iss >> r >> row >> c >> col >> num) {
            if (r == 'R' && c == 'C' && row >= 0 && row < 10 && col >= 0 && col < 10 && num >= 1 && num <= 10) {
            if (r == 'R' && c == 'C') {
                sudoku.placeNumber(row, col, num);
                cout << "Placed " << num << " at (" << row << ", " << col << ").\n";
                sudoku.printGrid();
                player.incrementMoves();
                sudoku.printGrid(printer);

                if (sudoku.isSolved()) {
                    cout << "Congratulations! You've solved the Sudoku!\n";
                    break;
                }
            } else {
                cout << "Invalid input! Please use 'R <row> C <col> <num>' within range.\n";
                cout << "Invalid input! Please use 'R <row> C <col> <num>'.\n";
            }
        } else {
            cout << "Invalid format! Use 'R <row> C <col> <num>'.\n";