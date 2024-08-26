#include <iostream>
using namespace std;

class Player {
private:
    string name;
    int moves;

public:
    Player(string playerName) : name(playerName), moves(0) {}

    string getName() const {
        return this->name;
    }

    void incrementMoves() {
        this->moves++;
    }

    int getMoves() const {
        return this->moves;
    }
};

class SudokuGrid {
private:
    int grid[4][4]; 

public:
    SudokuGrid(int initialGrid[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                this->grid[i][j] = initialGrid[i][j];
            }
        }
    }

    void printGrid() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << this->grid[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isSolved() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (this->grid[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
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
