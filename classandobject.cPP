#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Base Class representing general game functionality
class Game {
protected:
    int totalMoves; // Track total moves for the game

public:
    Game() : totalMoves(0) {}

    virtual ~Game() {}

    virtual void printGameType() const = 0; // Pure virtual function for polymorphism

    virtual void printGrid() const = 0; // Pure virtual function for displaying the grid

    virtual bool isSolved() const = 0; // Pure virtual function for checking if solved

    virtual void placeNumber(int row, int col, int num) = 0; // Pure virtual function for placing a number
};

// Class representing a Player
class Player {
private:
    string* name;
    Player(const string& playerName) : moves(0) {
        name = new string(playerName);
        totalPlayers++;
    }

    ~Player() {
        delete name;
    }

    string getName() const {
        return *name;
    }

 
    int getMoves() const {
        return moves;
    }
};

int Player::totalMoves = 0;
int Player::totalPlayers = 0;

// Class representing a Sudoku grid
class SudokuGrid : public Game {
protected:
    int** grid;
                grid[i][j] = initialGrid[i][j];
            }
        }
        totalGrids++;
    }

    ~SudokuGrid() {
        for (int i = 0; i < size; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }

                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
}
                if (grid[i][j] == 0) {
                    return false;
                }
            }
        }
        puzzlesSolved++;
        return true;
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
            }

            player.incrementMoves();

    return 0;
}
