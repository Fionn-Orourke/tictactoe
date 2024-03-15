#include <SDL.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>



//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int xbox = 117, xmin = 88;
int ybox = 108, ymin = 109;

int box(int, int);
int i, j, count1, count2;
char prev = 'o';

bool winstat = false;
bool draw = false;
int bot = 2;
int rdisp = 20, gdisp = 20;
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
            SDL_Rect line1 = { (SCREEN_WIDTH / 10) * 3 , (SCREEN_HEIGHT / 6), 4, 300 };
            SDL_Rect line2 = { (SCREEN_WIDTH / 10) * 5, (SCREEN_HEIGHT / 6), 4, 300 };
            SDL_FillRect(screenSurface, &line1, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_FillRect(screenSurface, &line2, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            // Horizontal lines

            SDL_Rect line3 = { SCREEN_WIDTH / 6, (SCREEN_HEIGHT / 10) * 3, 300, 4 };
            SDL_Rect line4 = { SCREEN_WIDTH / 6, (SCREEN_HEIGHT / 10) * 5, 300, 4 };
            SDL_FillRect(screenSurface, &line3, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_FillRect(screenSurface, &line4, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            printf_s("\nenter [1] to play against a bot, enter [2] to play 2 player: ");
            scanf_s("%i", &bot);
            while (true) {
                Uint32 buttons = SDL_GetMouseState(&x, &y);
                //printf_s("%d, %d", x, y);


                            //Update the surface
                SDL_UpdateWindowSurface(window);

                
                SDL_Event e;
                SDL_PollEvent(&e);
                
                //detects when enter key is pressed

                if (e.key.keysym.sym == 13) {
                    //resets the grid
                    if (winstat == true) {
                        for (count1 = 0; count1 <= 2; count1++) {
                            for (count2 = 0; count2 <= 2; count2++) {
                                grid[count1][count2] = '/0';
                                SDL_Rect box1 = { (xmin)+(count1 * xbox)  , (ymin)+(count2 * ybox), 50, 50 };
                                SDL_FillRect(screenSurface, &box1, SDL_MapRGB(screenSurface->format, 0, 0, 0));
                            }

                        }
                        winstat = false;
                        if (draw == true){
                            draw = false;
                        }
                        else
                        {

                            // puts win counter on the screen
                            if (prev == 'x') {
                                SDL_Rect rmark = {rdisp, 20, 3,10  };
                                SDL_FillRect(screenSurface, &rmark, SDL_MapRGB(screenSurface->format, 0xFF, 0, 0));
                                rdisp += 5;
                            }
                            if (prev == 'o') {
                                SDL_Rect rmark = { gdisp, 40, 3,10 };
                                SDL_FillRect(screenSurface, &rmark, SDL_MapRGB(screenSurface->format, 0, 0xFF, 0));
                                gdisp += 5;
                            }
                        }
                    }
                }
                if (winstat == false){
                    int num = 0;
                    //reads when window is clicked
                    if (e.button.state == 1) {
                        Uint32 buttons = SDL_GetMouseState(&x, &y);

                        
                        if (bot == 2 || prev == 'o') {

                            if (box(x, y) == 0)
                                printf_s("incorrect input");
                            else
                            {
                                // turns coordinates into locations on 3 by 3 grid

                                if (box(x, y) <= 3) {
                                    i = 0;
                                    j = box(x, y) - 1;
                                }
                                else if (box(x, y) <= 6) {
                                    i = 1;
                                    j = box(x, y) - 4;
                                }
                                else if (box(x, y) <= 9) {
                                    i = 2;
                                    j = box(x, y) - 7;
                                }
                                else
                                    printf_s("incorrect input");
                            }
                        }
                        else 
                        {
                            int p, b;
                            int n, m;
                            int rowx[3] = { 0 }; 
                            int colx[3] = { 0 };
                            int rowo[3] = { 0 };
                            int colo[3] = { 0 };
                            // tells the bot how many spots on each row is taken up
                            for (n = 0; n < 3; n++) {
                                for (m = 0; m < 3; m++) {
                                    if (grid[n][m] == 'x') {
                                        colx[n] += 1;
                                        rowx[m] += 1;
                                    }
                                    if (grid[n][m] == 'o') {
                                        colo[n] += 1;
                                        rowo[m] += 1;
                                    }
                                }
                            }

                            int choice[3] = { 0 };//[1 = columb. 2 = row]
                            choice[0] = 0;
                            int max = 0;
                            for (int i = 0; i < 3; i++) {
                                if (colo[i] > max){
                                    max = colo[i];
                                    choice[0] = 1;
                                    choice[1] = i;

                                }
                                if (colx[i] > max) {
                                    max = colx[i];
                                    choice[0] = 1;
                                    choice[1] = i;
                                }
                                    
                                if (rowo[i] > max) {
                                    max = rowo[i];
                                    choice[0] = 2;
                                    choice[1] = i;
                                }
                                    
                                if (rowx[i] > max) {
                                    max = rowx[i];
                                    choice[0] = 2;
                                    choice[1] = i;
                                }
                                    
                            }
                            

                            

                            // gives the bot the location of the first empty spot(bug fix)
                            for (count1 = 0; count1 <= 2; count1++) {
                                for (count2 = 0; count2 <= 2; count2++) {
                                    if (grid[count1][count2] != 'x' && grid[count1][count2] != 'o') {
                                        p = count1;
                                        b = count2;
                                        break;
                                    }

                                }
                            }

                            // checks random locations untill one is found
                            for (count1 = 0; count1 <= 2; count1++) {
                                srand(time(NULL));
                                int randp = rand() % 3;
                                for (count2 = 0; count2 <= 2; count2++) {
                                    srand(time(NULL));
                                    int randb = rand() % 3;
                                    if (grid[randp][randb] != 'x' && grid[randp][randb] != 'o') {
                                        p = randp;
                                        b = randb;
                                        break;
                                    }
                                
                                }
                            }
                            
                            //filters to find open spot on row with highest value
                            if (choice[0] == 1) {
                                for (n = 0; n < 3; n++) {
                                    if (grid[choice[1]][n] != 'x' && grid[choice[1]][n] != 'o') {
                                        p = choice[1];
                                        b = n;
                                        printf_s("hhhhh");
                                     
                                    }
                                

                                }
                            
                            }

                            else if (choice[0] == 2) 
                            {
                                for (n = 0; n < 3; n++) {
                                    if (grid[n][choice[1]] != 'x' && grid[n][choice[1]] != 'o') {
                                        b = choice[1];
                                        p = n;
                                        printf_s("hhhhh");
                                     
                                    }
                            
                                
                                }
                            
                        
                            }
                         i= p;
                         j = b;
                        }
                        //places players choice in the array
                        printf_s("[%i][%i]", i, j);
                        if (grid[i][j] == 'x' || grid[i][j] == 'o') {

                            printf_s("This place is already taken");
                        }
                        else {
                            if (prev == 'o') {
                                grid[i][j] = 'x';
                                prev = 'x';
                            }
                            else {
                                grid[i][j] = 'o';
                                prev = 'o';
                            }
                            for (count1 = 0; count1 <= 2; count1++) {
                                for (count2 = 0; count2 <= 2; count2++) {
                                    printf_s("%c", grid[count1][count2]);
                                }
                                printf_s("\n");
                            }


                            // displays players choice
                            SDL_Rect box = { (xmin)+(j * xbox)  , (ymin)+(i * ybox), 50, 50 };
                            if (prev == 'x')
                                SDL_FillRect(screenSurface, &box, SDL_MapRGB(screenSurface->format, 0xFF, 0, 0));
                            else
                                SDL_FillRect(screenSurface, &box, SDL_MapRGB(screenSurface->format, 0, 0xFF, 0));

                            // places w in the row of the winning line
                            char value = prev;
                            for (int p = 0; p < 3; ++p) {
                                if (grid[p][0] == value && grid[p][1] == value && grid[p][2] == value) {
                                    grid[0][p] = 'w';
                                    grid[1][p] = 'w';
                                    grid[2][p] = 'w';
                                    winstat = true;


                                }
                                if (grid[0][p] == value && grid[1][p] == value && grid[2][p] == value) {
                                    grid[p][0] = 'w';
                                    grid[p][1] = 'w';
                                    grid[p][2] = 'w';
                                    winstat = true;


                                }
                            }
                            // checks for winners
                            // Check diagonals
                            if ((grid[0][0] == value && grid[1][1] == value && grid[2][2] == value)) {
                                grid[0][0] = 'w';
                                grid[1][1] = 'w';
                                grid[2][2] = 'w';
                                winstat = true;

                            }

                            if (grid[0][2] == value && grid[1][1] == value && grid[2][0] == value) {
                                grid[0][2] = 'w';
                                grid[1][1] = 'w';
                                grid[2][0] = 'w';
                                winstat = true;



                            }
                            // counts spots taken
                            if (winstat == false) {
                                int cn = 0;
                                for (count1 = 0; count1 <= 2; count1++) {
                                    for (count2 = 0; count2 <= 2; count2++) {
                                        if (grid[count1][count2] == 'x' || grid[count1][count2] == 'o') {
                                            cn += 1;
                                        }
                                    }
                                }// if all spots are taken and there is no winner 
                                if (cn == 9) {
                                    winstat = true;
                                    draw = true;
                                }

                            }
                            // all locations that arent in the winning line are reset
                            if (winstat == true) {
                                for (count1 = 0; count1 <= 2; count1++) {
                                    for (count2 = 0; count2 <= 2; count2++) {
                                        if (grid[count1][count2] != 'w') {
                                            SDL_Rect box1 = { (xmin)+(count1 * xbox)  , (ymin)+(count2 * ybox), 50, 50 };
                                            SDL_FillRect(screenSurface, &box1, SDL_MapRGB(screenSurface->format, 0, 0, 0));

                                        }
                                    }
                                }
                            }
                        }



                    }
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



    //gets the specific ox and returns a value from 1 to  9 each number reffering to a box
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