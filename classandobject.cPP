#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// GameStats Class: Manages global game statistics
class GameStats {
private:
    static int totalMoves;
    static int totalPlayers;
    static int puzzlesSolved;

public:
    static void incrementTotalMoves() { totalMoves++; }
    static void incrementTotalPlayers() { totalPlayers++; }
    static void incrementPuzzlesSolved() { puzzlesSolved++; }

    static int getTotalMoves() { return totalMoves; }
    static int getTotalPlayers() { return totalPlayers; }
    static int getPuzzlesSolved() { return puzzlesSolved; }
};

// Initialize static variables
int GameStats::totalMoves = 0;
int GameStats::totalPlayers = 0;
int GameStats::puzzlesSolved = 0;

// Abstract MoveValidator Class: Open for adding new rules
class MoveValidator {
public:
    virtual bool validate(int row, int col, int num) const = 0;
    virtual ~MoveValidator() = default;
};

// ClassicSudokuValidator Class: Implements basic validation rules
class ClassicSudokuValidator : public MoveValidator {
public:
    bool validate(int row, int col, int num) const override {
        return row >= 0 && row < 10 && col >= 0 && col < 10 && num >= 1 && num <= 10;
    }
};

// Abstract GridPrinter Class: Open for custom printing logic
class GridPrinter {
public:
    virtual void print(const int grid[10][10]) const = 0;
    virtual ~GridPrinter() = default;
};

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
        GameStats::incrementPuzzlesSolved();
        return true;
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

    string playerName;
    cout << "Enter your name: ";
    getline(cin, playerName);

    Player player(playerName);
    ClassicSudokuValidator validator;
    SudokuGrid sudoku(puzzle, &validator);
    SimpleGridPrinter printer;

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
                player.incrementMoves();
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

    cout << "\nPlayer: " << player.getName() << " | Moves: " << player.getMoves() << endl;
    cout << "Total Moves by All Players: " << GameStats::getTotalMoves() << endl;
    cout << "Total Players: " << GameStats::getTotalPlayers() << endl;
    cout << "Total Puzzles Solved: " << GameStats::getPuzzlesSolved() << endl;

    return 0;
}
