#include <iostream>
#include <string>
#include <sstream>
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

// SudokuGrid Class: Manages the Sudoku grid and game logic
class SudokuGrid {
private:
    int grid[10][10];

public:
    SudokuGrid(int initialGrid[10][10]) {
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
        }
    }

    void placeNumber(int row, int col, int num) {
        grid[row][col] = num;
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
    SudokuGrid sudoku(puzzle);

    cout << "Sudoku Grid before solving:" << endl;
    sudoku.printGrid();

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
            if (r == 'R' && c == 'C' && row >= 0 && row < 10 && col >= 0 && col < 10 && num >= 1 && num <= 10) {
                sudoku.placeNumber(row, col, num);
                cout << "Placed " << num << " at (" << row << ", " << col << ").\n";
                sudoku.printGrid();
                player.incrementMoves();

                if (sudoku.isSolved()) {
                    cout << "Congratulations! You've solved the Sudoku!\n";
                    break;
                }
            } else {
                cout << "Invalid input! Please use 'R <row> C <col> <num>' within range.\n";
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
