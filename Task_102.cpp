#include<stdio.h>

#include<SDL2/SDL.h>

#include<math.h>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 640;
int radius = 20;
int CENTERX = SCREEN_WIDTH / 2;
int CENTERY = SCREEN_HEIGHT / 2;
SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;
bool game_running = false;

bool activate_window()
{
    if (SDL_Init(SDL_INIT_VIDEO) != NULL)
    {
        printf("ERROR INITIALIZING SDL!");
        return false;
    }

    Window = SDL_CreateWindow("CREATED BY TASNOVA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (!Window)
    {
        return false;
    }

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

    if (!Renderer)
    {
        return false;
    }

    return true;
}



void MakeCircle(SDL_Renderer* Renderer, int cx, int cy, int radius)
{
    for (int x = -radius; x <= radius; x++)
    {
        for (int y = -radius; y <= radius; y++)
        {
            if (x * x + y * y <= radius * radius)
            {
                SDL_RenderDrawPoint(Renderer, cx + x, cy + y);
            }
        }
    }
}
void startup()
{
    SDL_SetRenderDrawColor(Renderer, 50, 50, 70, 200);

    SDL_RenderClear(Renderer);

    SDL_Color color = { 200,100,100,200 };

    SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);

}
void update()
{
    radius += 5;

    if (radius >= 320)
    {
        radius = 20;
    }

    SDL_RenderClear(Renderer);

    SDL_SetRenderDrawColor(Renderer, 100, 110, 120, 130);

    SDL_RenderClear(Renderer);

    SDL_SetRenderDrawColor(Renderer, 200,100,100, 200);
}

void render()
{
    MakeCircle(Renderer, CENTERX, CENTERY, radius);

    SDL_RenderPresent(Renderer);
}

void destroyWindow()
{
    SDL_DestroyRenderer(Renderer);

    SDL_DestroyWindow(Window);

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