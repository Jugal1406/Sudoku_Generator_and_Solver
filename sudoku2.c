#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 9 // Size of the grid

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%2d", grid[row][col]);
        }
        printf("\n");
    }
}

// Check if placing num in grid[row][col] is valid
bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

// Solve the Sudoku using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;
    bool emptyCell = false;

    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                emptyCell = true;
                break;
            }
        }
        if (emptyCell) break;
    }

    if (!emptyCell)
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            grid[row][col] = 0; // Backtrack
        }
    }

    return false;
}

// Function to fill the diagonal 3x3 grids
void fillDiagonal(int grid[N][N]) {
    for (int i = 0; i < N; i += 3) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                int num;
                do {
                    num = rand() % 9 + 1;
                } while (!isSafe(grid, i + row, i + col, num));
                grid[i + row][i + col] = num;
            }
        }
    }
}

// Remove k digits to create a puzzle
void removeDigits(int grid[N][N], int k) {
    while (k > 0) {
        int cellId = rand() % (N * N);
        int row = cellId / N;
        int col = cellId % N;

        if (grid[row][col] != 0) {
            grid[row][col] = 0;
            k--;
        }
    }
}

// Generate a full valid Sudoku grid
void generateSudoku(int grid[N][N]) {
    // Initialize empty grid
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = 0;

    // Fill diagonal grids
    fillDiagonal(grid);

    // Solve to fill the rest of the grid
    solveSudoku(grid);
}

// Main function
int main() {
    srand(time(0));

    int grid[N][N];
    char choice;
    while(1){
    printf("\n\nEnter 'g' to generate sudoku puzzle or Enter 'i' to input sudoku puzzle or Enter '0' to exit : ");
    scanf(" %c",&choice);
    if(choice=='0')
    {
        printf("\nExited");
        break;
    }
    switch(choice)
    {
       case 'g': generateSudoku(grid);

    // Print the fully solved Sudoku
   // printf("Generated Full Sudoku:\n");
    //printGrid(grid);

    // Remove digits to create a puzzle
    int k = 40; // Number of cells to remove
    removeDigits(grid, k);

    // Print the puzzle
    printf("\n\nSudoku Puzzle:\n");
    printGrid(grid);
    char solution;
    x:
    printf("\nTO SEE SOLUTION ENTER 's' :");
    scanf(" %c",&solution);
    printf("\n");
    if(solution=='s'){
    if (solveSudoku(grid)) {
        printf("\nSolved Sudoku:\n");
        printGrid(grid);
    } else {
        printf("\nNo solution exists.\n");
    }
    }
    else
    {
        printf("\nInvalid entry...\n");
        goto x;

    }

    break;


    case 'i':
            printf("\nEnter the Sudoku Puzzle(for empty places enter 0):\n");
            for(int i=0;i<N;i++)
             {
                for(int j=0;j<N;j++)
                {
                    scanf("%d",&grid[i][j]);
                }
             }


    // Solve the puzzle
    if (solveSudoku(grid)) {
        printf("\nSolved Sudoku:\n");
        printGrid(grid);
    } else {
        printf("\nNo solution exists.\n");
    }
    break;

    default:printf("\nInvalid Entry...\n");
            break;
    }
    }

    return 0;
}
