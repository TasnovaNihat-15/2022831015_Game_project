#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

int CENTERX = SCREEN_WIDTH / 2;
int CENTERY = SCREEN_WIDTH / 2;
int radius = 120;


bool activateSDL(SDL_Window** window, SDL_Renderer** Renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != NULL)
    {
        printf("ERROR INITIALIZING SDL!");

        return false;
    }

    *window = SDL_CreateWindow("CREATED BY TASNOVA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (*window == NULL)
    {
        printf("ERROR INITIALIZING SDL!");

        return false;
    }

    *Renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (*Renderer == 0)
    {
        printf("ERROR INITIALIZING RENDERER!");

        return false;
    }

    return true;
}
void MakeCircle(SDL_Renderer* Renderer, int centerX, int centerY, int rad)
{
    for (int x = -rad; x <= rad; x++)
    {
        for (int y = -rad; y <= rad; y++)
        {
            if (x * x + y * y <= rad * rad)
            {
                SDL_RenderDrawPoint(Renderer, centerX + x, centerY + y);
            }
        }
    }
}
int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!activateSDL(&window, &renderer))
    {
        return 1;
    }

    SDL_Event event;

    bool running = true;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 150, 200, 255, 100);
        SDL_RenderClear(renderer);


        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 100);
        MakeCircle(renderer, CENTERX, CENTERY, radius);

        SDL_RenderPresent(renderer);
    }

    return 0;
}