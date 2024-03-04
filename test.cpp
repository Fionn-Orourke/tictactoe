//mini project 1 
// 

#include <stdio.h>
#include <stdbool.h>

// Function to print the 3x3 grid
void printGrid(char grid[3][3]) {
    printf("3x3 Grid:\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

// Function to check if there is a winner
bool checkWin(char grid[3][3], char value) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((grid[i][0] == value && grid[i][1] == value && grid[i][2] == value) ||
            (grid[0][i] == value && grid[1][i] == value && grid[2][i] == value)) {
            return true;
        }
    }
    // Check diagonals
    if ((grid[0][0] == value && grid[1][1] == value && grid[2][2] == value) ||
        (grid[0][2] == value && grid[1][1] == value && grid[2][0] == value)) {
        return true;
    }
    return false;
}

int main() {
    char grid[3][3] = { {' ', ' ', ' '},  // Define a 3x3 grid with initial values
                       {' ', ' ', ' '},
                       {' ', ' ', ' '} };

    char value;
    int row, col;

    while (true) {
        // Ask the user for the value (X or O)
        printf("Enter a value (X or O): ");
        scanf(" %c", &value);

        // Validate the input value
        if (value != 'X' && value != 'O') {
            printf("Invalid input! Please enter either X or O.\n");
            continue;
        }

        // Assume a predetermined location to place the value
        printf("Enter the row and column to place the value \n(0,1,2)\n(0,1,2): \n");
        scanf("%d %d", &row, &col);

        // Validate the input row and column
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            printf("Invalid row or column! Please enter values between 0 and 2.\n");
            continue;
        }

        // Check if the cell is already occupied
        if (grid[row][col] != ' ') {
            printf("Cell already occupied! Please choose another cell.\n");
            continue;
        }

        // Place the value in the grid
        grid[row][col] = value;

        // Print the updated grid
        printGrid(grid);

        // Check if there is a winner
        if (checkWin(grid, value)) {
            printf("Player %c wins!\n", value);
            break;
        }
    }

    return 0;
}
