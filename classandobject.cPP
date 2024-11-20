#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Player {
private:
    string* name;
    int moves;

public:
    // Constructor with dynamic memory allocation for name
    Player(const string& playerName) : moves(0) {
        name = new string(playerName);
    }

    // Destructor to deallocate memory
    ~Player() {
        delete name;
    }

    string getName() const {
        return *name;
    }

    void incrementMoves() {
        moves++;
    }

    int getMoves() const {
        return moves;
    }
};

class SudokuGrid {
private:
    int** grid;
    int size;

public:
    // Constructor to initialize the grid dynamically
    SudokuGrid(int initialGrid[10][10], int size) : size(size) {
        grid = new int*[size];
        for (int i = 0; i < size; i++) {
            grid[i] = new int[size];
            for (int j = 0; j < size; j++) {
                grid[i][j] = initialGrid[i][j];
            }
        }
    }

    // Destructor to free the allocated memory
    ~SudokuGrid() {
        for (int i = 0; i < size; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    // Function to print the grid
    void printGrid() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Function to check if the grid is solved
    bool isSolved() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (grid[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }

    // Function to place a number in the grid
    void placeNumber(int row, int col, int num) {
        if (row >= 0 && row < size && col >= 0 && col < size && num >= 1 && num <= size) {
            grid[row][col] = num;
        } else {
            cout << "Invalid placement.\n";
        }
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

    Player player("John Doe");
    SudokuGrid sudoku(puzzle, 10);

    cout << "Sudoku Grid before solving:" << endl;
    sudoku.printGrid();

    string input;
    while (true) {
        cout << "Enter your move (R <row> C <col> <num>) or type 'exit' to quit: ";
        getline(cin, input);

        if (input == "exit") {
            cout << "Thank you for playing!" << endl;
            break;
        }

        char r, c;
        int row, col, num;
        istringstream iss(input);
        if (iss >> r >> row >> c >> col >> num) {
            sudoku.placeNumber(row - 1, col - 1, num); // Adjust for 0-based indexing
            cout << "Grid after move:" << endl;
            sudoku.printGrid();

            if (sudoku.isSolved()) {
                cout << "Congratulations! You've solved the Sudoku!\n";
                break;
            }

            player.incrementMoves();
        } else {
            cout << "Invalid input format! Please use 'R <row> C <col> <num>'.\n";
        }
    }

    cout << "Player: " << player.getName() << " | Moves: " << player.getMoves() << endl;

    return 0;
}
