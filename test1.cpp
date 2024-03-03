#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int box(int , int );
int i, j, count1, count2;




void drawX(SDL_Renderer* renderer, int x, int y, int size) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw the first diagonal line (from top-left to bottom-right)
    SDL_RenderDrawLine(renderer, x - size, y - size, x + size, y + size);

    // Draw the second diagonal line (from top-right to bottom-left)
    SDL_RenderDrawLine(renderer, x + size, y - size, x - size, y + size);
}



int main(int argc, char* args[])
{
    char grid[3][3] = { {' ', ' ', ' '},  // Define a 3x3 grid with initial values
                       {' ', ' ', ' '},
                       {' ', ' ', ' '} };
    Uint32 buttons;
    int x, y, clickPos;
    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            //Fill the surface colour
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));


            // Vertical lines
            SDL_Rect line1 = { (SCREEN_WIDTH / 10)*3 , (SCREEN_HEIGHT / 6), 4, 300};
            SDL_Rect line2 = { (SCREEN_WIDTH / 10)*5, (SCREEN_HEIGHT / 6), 4, 300};
            SDL_FillRect(screenSurface, &line1, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_FillRect(screenSurface, &line2, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            // Horizontal lines
            
            SDL_Rect line3 = { SCREEN_WIDTH / 6, (SCREEN_HEIGHT / 10) * 3, 300, 4 };
            SDL_Rect line4 = { SCREEN_WIDTH / 6, (SCREEN_HEIGHT / 10) * 5, 300, 4 };
            SDL_FillRect(screenSurface, &line3, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_FillRect(screenSurface, &line4, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            //SDL_Renderer *renderer = SDL_CreateRenderer(window, SCREEN_WIDTH, SCREEN_HEIGHT);
            //SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255);
            //SDL_RenderDrawLine( renderer, 8, 7, 6, 255);
            //SDL_RenderPresent(renderer);

            while (true) {
                Uint32 buttons = SDL_GetMouseState(&x, &y);
                //printf_s("%d, %d", x, y);


                            //Update the surface
                SDL_UpdateWindowSurface(window);

                            //get window to stay up
                SDL_Event e;
                SDL_PollEvent(&e);
                int num = 0;
                if (e.button.state == 1){
                    Uint32 buttons = SDL_GetMouseState(&x, &y);
                    
                    //printf_s("%i", box(x, y));
                    if (box(x, y) <= 3) {
                        i = 0;
                        j = box(x, y) - 1;
                    }
                    else if (box(x, y) <= 6) {
                        i = 1;
                        j = box(x, y)-4;
                    }
                    else if (box(x, y) <= 9) {
                        i = 2;
                        j = box(x, y) -7;
                    }
                    else
                        printf_s("incorrect input");
                    
                    printf_s("[%i][%i]", x, y);
                    grid[i][j] = 'x';
                    int xbox = 117, xmin = 88;
                    int ybox = 108, ymin = 109;
                    SDL_Rect box = { (xmin)+(j*xbox)  , (ymin) + (i * ybox), 50, 50};
                    SDL_FillRect(screenSurface, &box, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
                    
                    }


                
            }
            SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }

            
        }

    }

    SDL_DestroyWindow(window);

    //Quit SDL window
    SDL_Quit();

    return 0;
}




int box(int col, int row) {
    int result = 0;
    //gets the row and assings 1,2 or 3 for the row
    if (col >= 52 && col <= 179)
        result = 1;
    else if (col >= 185 && col <= 298)
        result = 2;
    else if (col >= 304 && col <= 418)
        result = 3;
    else
        result = 0;
    


    //gets the specific ox and returns a value from 1 to each number reffering to a box
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
