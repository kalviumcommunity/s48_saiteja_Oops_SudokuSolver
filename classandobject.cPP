#include <iostream>
#include <sstream>
using namespace std;

// Base Class representing general game functionality
class Game {
protected:
    int totalMoves;  // Track total moves in the game
public:
    Game() : totalMoves(0) {}

    void incrementMoves() {
        totalMoves++;
    }

    int getTotalMoves() const {
        return totalMoves;
    }

    virtual void printGameType() const {
        cout << "General Game" << endl;
    }
};

// Derived Class: Player class remains as is
class Player {
private:
    string* name;
    int moves;
    static int totalMoves; 
    static int totalPlayers; 

public:
    // Constructor 1: Parameterized constructor
    // Initializes 'name' dynamically using the passed playerName and sets moves to 0.
    // Also increments the static variable totalPlayers to track the number of Player objects created.
    Player(const string& playerName) : moves(0) {
        name = new string(playerName);
        totalPlayers++; 
    }

    // Destructor: Cleans up dynamically allocated memory (name)
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
        return this->moves;
    }

    void incrementMoves() {
        this->moves++;
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
private:
    int** grid;    
    static int puzzlesSolved; 
    static int totalGrids;    

public:
    // Constructor 2: Parameterized constructor
    // Takes a 10x10 grid and allocates memory for it dynamically.
    // Copies the values of the passed grid into the dynamically allocated grid.
    // Increments the static variable totalGrids to track the number of grids created.
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

    // Destructor: Deallocates the dynamically allocated memory for the grid
    ~SudokuGrid() {
        for (int i = 0; i < 10; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    void printGrid() const {
        for (int i = 10 - 1; i >= 0; i--) {
            for (int j = 0; j < 10; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isSolved() const {
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

    void placeNumber(int row, int col, int num) {
        grid[row][col] = num; 
    }

    void printGameType() const override {  // Overriding base class function
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
    
    // Demonstrating the use of the parameterized constructor for SudokuGrid
    SudokuGrid* sudoku = new SudokuGrid(puzzle);

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
                cout << "Invalid input! Please ensure you use the correct format: 'R <row> C <col> <num>' and the values are within range.\n";
            }
        } else {
            cout << "Invalid input format! Please enter in the format 'R <row> C <col> <num>'.\n";
        }
    }

    cout << "\nPlayer: " << player->getName() << " | Moves: " << player->getMoves() << endl;
    cout << "Total Moves by All Players: " << Player::getTotalMoves() << endl;
    cout << "Total Players: " << Player::getTotalPlayers() << endl;
    cout << "Total Puzzles Solved: " << SudokuGrid::getPuzzlesSolved() << endl;
    cout << "Total Sudoku Grids Created: " << SudokuGrid::getTotalGrids() << endl;

    // Show inheritance feature from AdvancedSudokuGrid
    sudoku->provideHint();  

    player->clearName(); 
    delete sudoku;  
    delete player; 

    return 0;
}
