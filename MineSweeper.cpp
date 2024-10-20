#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;


const int ROWS = 10;
const int COLS = 10;
const int MINES = 15;


void initializeMinefield(char minefield[ROWS][COLS], bool mines[ROWS][COLS]) {

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            minefield[i][j] = '.';
            mines[i][j] = false;
        }
    }


    srand(time(0));
    for (int i = 0; i < MINES; ) {
        int row = rand() % ROWS;
        int col = rand() % COLS;

        if (!mines[row][col]) {
            mines[row][col] = true;
            ++i;
        }
    }
}

void displayMinefield(char minefield[ROWS][COLS]) {
    cout << "   ";
    for (int j = 0; j < COLS; ++j) {
        cout << j << " ";
    }
    cout << endl;

    for (int i = 0; i < ROWS; ++i) {
        cout << i << "  ";
        for (int j = 0; j < COLS; ++j) {
            cout << minefield[i][j] << " ";
        }
        cout << endl;
    }
}

int countAdjacentMines(int row, int col, bool mines[ROWS][COLS]) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && mines[newRow][newCol]) {
                count++;
            }
        }
    }
    return count;
}


void revealCell(int row, int col, char minefield[ROWS][COLS], bool mines[ROWS][COLS], stack<pair<int, int>>& cellStack) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS || minefield[row][col] != '.') {
        return;
    }

    int adjacentMines = countAdjacentMines(row, col, mines);
    minefield[row][col] = adjacentMines + '0';


    cellStack.push({row, col});

    if (adjacentMines == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i != 0 || j != 0) {
                    revealCell(row + i, col + j, minefield, mines, cellStack);
                }
            }
        }
    }
}

void undoReveal(char minefield[ROWS][COLS], stack<pair<int, int>>& cellStack) {
    if (cellStack.empty()) {
        cout << "No moves to undo!" << endl;
        return;
    }

    pair<int, int> lastCell = cellStack.top();
    cellStack.pop();
    minefield[lastCell.first][lastCell.second] = '.';
    cout << "Undid reveal of cell: (" << lastCell.first << ", " << lastCell.second << ")" << endl;
}

int main() {
    char minefield[ROWS][COLS];
    bool mines[ROWS][COLS];
    initializeMinefield(minefield, mines);

    int revealedCells = 0;
    int totalCells = ROWS * COLS - MINES;
    stack<pair<int, int>> cellStack;

    while (revealedCells < totalCells) {
        displayMinefield(minefield);
        cout << "Enter row (0-" << ROWS - 1 << ") and column (0-" << COLS - 1 << ") to reveal (or '-1 -1' to quit, 'u' to undo): ";

        string input;
        cin >> input;

        if (input == "-1") {
            cout << "Thanks for playing! Exiting the game." << endl;
            break;
        }

        if (input == "u") {
            undoReveal(minefield, cellStack);
            continue;
        }

        int row = stoi(input);
        int col;
        cin >> col;

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            cout << "Invalid input! Please try again." << endl;
            continue;
        }

        if (mines[row][col]) {
            cout << "Boom! You hit a mine!" << endl;
            minefield[row][col] = '*';
            displayMinefield(minefield);
            break;
        } else {
            revealCell(row, col, minefield, mines, cellStack);
            revealedCells++;
        }
    }

    cout << "Game Over!" << endl;
    return 0;
}
