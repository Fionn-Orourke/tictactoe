#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

int main(int argc, char* args[])
{
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
        window = SDL_CreateWindow("Fionn Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x11, 0x31, 0xa1));

            //Draw two parallel lines in the middle of the window
            SDL_Rect line1 = { SCREEN_WIDTH / 4 - 50, SCREEN_HEIGHT / 2, 100, 2 };
            SDL_Rect line2 = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 10, 2, 100 };
            SDL_FillRect(screenSurface, &line1, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_FillRect(screenSurface, &line2, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            //Update the surface
            SDL_UpdateWindowSurface(window);

            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
        }

    }

    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}

