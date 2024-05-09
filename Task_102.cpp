#include<stdio.h>

#include<SDL2/SDL.h>

#include<math.h>

int SCREEN_WIDTH = 640;

int SCREEN_HEIGHT = 640;

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

bool game_running = false;

int radius = 20;

int CENTERX = SCREEN_WIDTH / 2;

int CENTERY = SCREEN_HEIGHT / 2;

bool activate_window()
{
    if (SDL_Init(SDL_INIT_VIDEO) != NULL)
    {
        printf("ERROR INITIALIZING SDL!");
        return false;
    }

    window = SDL_CreateWindow("MADE BY TASNOVA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (!window)
    {
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        return false;
    }

    return true;
}

void startup()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 70, 200);

    SDL_RenderClear(renderer);

    SDL_Color color = { 200,0,0,200 };

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

}

void MakeCircle(SDL_Renderer* renderer, int cx, int cy, int radius)
{
    for (int x = -radius; x <= radius; x++)
    {
        for (int y = -radius; y <= radius; y++)
        {
            if (x * x + y * y <= radius * radius)
            {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

void update()
{
    radius += 5;

    if (radius >= 320)
    {
        radius = 20;
    }

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 100, 110, 0, 255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 100, 0, 0, 200);
}

void render()
{
    MakeCircle(renderer, CENTERX, CENTERY, radius);

    SDL_RenderPresent(renderer);
}

void destroyWindow()
{
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();
}

int main(int argc, char* argv[])
{
    game_running = activate_window();
  SDL_Event windowevent;
    while (game_running != false)
    {
        update();

        render();
         if(SDL_PollEvent(&windowevent))
        {
            if(SDL_QUIT==windowevent.type)
                break;
        }
    }



    return 0;
}