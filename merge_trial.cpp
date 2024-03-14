#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

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

int box(int col, int row) {
    int result = 0;

    if (col >= 52 && col <= 179)
        result = 1;
    else if (col >= 185 && col <= 298)
        result = 2;
    else if (col >= 304 && col <= 418)
        result = 3;
    else
        result = 0;

    if (result > 0) {
        if (row >= 64 && row <= 178)
            result += 0;
        else if (row >= 182 && row <= 299)
            result += 3;
        else if (row >= 301 && row <= 436)
            result += 6;
    }

    if ((col < 52 || col > 418) || (row < 64 || row > 436)) {
        result = 0;
    }

    return result;
}

int main() {
    char grid[3][3] = { {' ', ' ', ' '},  // Define a 3x3 grid with initial values
                       {' ', ' ', ' '},
                       {' ', ' ', ' '} };

    char value;
    int x, y;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Create window
    SDL_Window* window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    while (true) {
        // Ask the user for the value (X or O)
        printf("Enter a value (X or O): ");
        scanf(" %c", &value);

        // Validate the input value
        if (value != 'X' && value != 'O') {
            printf("Invalid input! Please enter either X or O.\n");
            continue;
        }

        Uint32 buttons;
        SDL_Event e;
        while (true) {
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) {
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                buttons = SDL_GetMouseState(&x, &y);
                printf(" (%d, %d)", x, y);
                int position = box(x, y);
                if (position != 0) {
                    int row = (position - 1) / 3;
                    int col = (position - 1) % 3;
                    if (grid[row][col] == ' ') {
                        grid[row][col] = value;
                        printGrid(grid);
                        if (checkWin(grid, value)) {
                            printf("Player %c wins!\n", value);
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                            return 0;
                        }
                        break;
                    }
                    else {
                        printf("Cell already occupied! Please choose another cell.\n");
                    }
                }
                else {
                    printf("Invalid position! Please click inside one of the boxes.\n");
                }
            }
        }
    }

    return 0;
}