#include <iostream>
using namespace std;

#define N 9   // Size of the Sudoku grid (9x9)

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Check if a number can be placed in a given position
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;

    // Check column
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Solve Sudoku using Backtracking
bool solveSudoku(int grid[N][N], int row, int col) {
    // If reached the end of the grid, Sudoku is solved
    if (row == N - 1 && col == N)
        return true;

    // Move to next row if column is at the end
    if (col == N) {
        row++;
        col = 0;
    }

    // Skip filled cells
    if (grid[row][col] != 0)
        return solveSudoku(grid, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        // Check if placing num is safe
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recurse for next cell
            if (solveSudoku(grid, row, col + 1))
                return true;
        }

        // Undo assignment (Backtrack)
        grid[row][col] = 0;
    }
    return false;
}

int main() {
    // Example Sudoku Puzzle (0 means empty cell)
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Original Sudoku Puzzle:\n";
    printGrid(grid);

    if (solveSudoku(grid, 0, 0)) {
        cout << "\nSolved Sudoku Puzzle:\n";
        printGrid(grid);
    } else {
        cout << "\nNo solution exists!\n";
    }

    return 0;
}
