#include <iostream>
using namespace std;

class Player {
private:
    string name;
    int moves;

public:
    Player(string playerName) : name(playerName), moves(0) {}

    string getName() const {
        return name;
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
    int grid[4][4]; // 4x4 Sudoku grid

public:
    SudokuGrid(int initialGrid[4][4]) {
        // Initialize the grid with the given 2D array
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                grid[i][j] = initialGrid[i][j];
            }
        }
    }

    void printGrid() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Function to check if the puzzle is solved
    bool isSolved() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (grid[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    // Example Sudoku puzzle (0 represents empty cells)
    int puzzle[4][4] = {
        {1, 0, 0, 4},
        {0, 0, 3, 0},
        {0, 3, 0, 0},
        {4, 0, 0, 2}
    };

    Player player("John Doe");
    SudokuGrid sudoku(puzzle);
    sudoku.printGrid();
    player.incrementMoves();

    cout << "Player: " << player.getName() << " | Moves: " << player.getMoves() << endl;

    return 0;
}
