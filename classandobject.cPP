#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Base Class representing general game functionality
class Game {
protected:
    int totalMoves;

public:
    Game() : totalMoves(0) {}

    virtual ~Game() {}

    virtual void printGameType() const = 0; // Pure virtual function for polymorphism

    virtual void printGrid() const = 0; // Pure virtual function for displaying the grid

    virtual bool isSolved() const = 0; // Pure virtual function for checking if solved

    virtual void placeNumber(int row, int col, int num) = 0; // Pure virtual for placing a number
};

// Derived Class representing a specific Player
class Player {
private:
    string* name;
    int moves;
    static int totalMoves;
    static int totalPlayers;

public:
    // Constructor 1: Parameterized constructor
    Player(const string& playerName) : moves(0) {
        name = new string(playerName);
        totalPlayers++;
    }

    // Destructor
    ~Player() {
        delete name;
    }

    string getName() const {
        return *name;
    }

    void setName(const string& playerName) {
        *name = playerName;
    }

    int getMoves() const {
        return moves;
    }

    void incrementMoves() {
        moves++;
        totalMoves++;
    }

    static int getTotalMoves() {
        return totalMoves;
    }

    static int getTotalPlayers() {
        return totalPlayers;
    }

    void clearName() {
        delete name;
        name = nullptr;
    }
};

int Player::totalMoves = 0;
int Player::totalPlayers = 0;

// Derived Class from Game for the specific Sudoku game
class SudokuGrid : public Game {
protected:
    int** grid;
    static int puzzlesSolved;
    static int totalGrids;

public:
    // Constructor 2: Parameterized constructor
    SudokuGrid(int initialGrid[10][10]) {
        grid = new int*[10];
        for (int i = 0; i < 10; i++) {
            grid[i] = new int[10];
            for (int j = 0; j < 10; j++) {
                grid[i][j] = initialGrid[i][j];
            }
        }
        totalGrids++;
    }

    // Destructor
    ~SudokuGrid() {
        for (int i = 0; i < 10; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    void printGrid() const override {
        for (int i = 10 - 1; i >= 0; i--) {
            for (int j = 0; j < 10; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isSolved() const override {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (grid[i][j] == 0) {
                    return false;
                }
            }
        }
        puzzlesSolved++;
        return true;
    }

    static int getPuzzlesSolved() {
        return puzzlesSolved;
    }

    static int getTotalGrids() {
        return totalGrids;
    }

    void placeNumber(int row, int col, int num) override {
        grid[row][col] = num;
    }

    void printGameType() const override {
        cout << "Sudoku Game" << endl;
    }
};

int SudokuGrid::puzzlesSolved = 0;
int SudokuGrid::totalGrids = 0;

// Another Derived Class that extends SudokuGrid
class AdvancedSudokuGrid : public SudokuGrid {
public:
    AdvancedSudokuGrid(int initialGrid[10][10]) : SudokuGrid(initialGrid) {}

    void provideHint() const {
        cout << "Hint: Try focusing on filling rows with fewer empty cells!" << endl;
    }

    void printGameType() const override {
        cout << "Advanced Sudoku Game" << endl;
    }
};

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

    Player* player = new Player(playerName);

    // Using AdvancedSudokuGrid instead of regular SudokuGrid
    AdvancedSudokuGrid* sudoku = new AdvancedSudokuGrid(puzzle);

    cout << "Sudoku Grid before solving:" << endl;
    sudoku->printGrid();

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
                sudoku->placeNumber(row, col, num);
                cout << "Placed " << num << " at (" << row << ", " << col << ").\n";
                sudoku->printGrid();
                player->incrementMoves();

                if (sudoku->isSolved()) {
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

    cout << "\nPlayer: " << player->getName() << " | Moves: " << player->getMoves() << endl;
    cout << "Total Moves by All Players: " << Player::getTotalMoves() << endl;
    cout << "Total Players: " << Player::getTotalPlayers() << endl;
    cout << "Total Puzzles Solved: " << SudokuGrid::getPuzzlesSolved() << endl;
    cout << "Total Sudoku Grids Created: " << SudokuGrid::getTotalGrids() << endl;

    // Downcasting to access AdvancedSudokuGrid methods
    auto* advancedSudoku = dynamic_cast<AdvancedSudokuGrid*>(sudoku);
    if (advancedSudoku) {
        advancedSudoku->provideHint();
    }

    player->clearName();
    delete sudoku;
    delete player;

    return 0;
}
