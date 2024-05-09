#include<stdio.h>

#include<SDL2/SDL.h>

#include<math.h>

int SCREEN_WIDTH = 640;

int SCREEN_HEIGHT = 640;

SDL_Window* Window=NULL;

SDL_Renderer* Renderer=NULL;

bool game_running=false;

int radius_1 = 80;

int CENTER_x1 = -radius_1;

int CENTER_y1 = SCREEN_HEIGHT/2;

int radius_2 = 20;

int CENTER_x2 = SCREEN_WIDTH/2;

int CENTER_y2 = radius_2;

bool activatewindow()
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        printf("ERROR INITIALIZING SDL!");
        return false;
    }

    Window=SDL_CreateWindow("CREATED BY TASNOVA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH , SCREEN_HEIGHT, 0);
    
    if(!Window) 
    {
         return false;
    }
    Renderer=SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if(!Renderer)
    {
        return false;
    }

    return true;
}

void startup()
{
    SDL_SetRenderDrawColor(Renderer, 70, 80, 90, 255);
    SDL_RenderClear(Renderer);
    SDL_Color color = {0,0,0,0};
    SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);

}
void processinginput()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if(event.type == SDL_KEYDOWN)//to move circle pressing keys
        {
            if(SDLK_RIGHT==event.key.keysym.sym)
            {
                if(CENTER_x2 <= 615)
                {
                    CENTER_x2 += 5;
                }
            }

            else if(SDLK_LEFT==event.key.keysym.sym)
            {
                if(CENTER_x2 >= 25)
                {
                    CENTER_x2 -= 5;
                }
            }

            else if(SDLK_UP==event.key.keysym.sym)
            {
                if(CENTER_y2 >= 25)
                {
                    CENTER_y2 -= 5;
                }
            }

            else if(SDLK_DOWN==event.key.keysym.sym)
            {
                if(CENTER_y2 <= 615)
                {
                    CENTER_y2 += 5;
                }
            }
        }

        else if (event.type == SDL_QUIT)
        {
            game_running = false;
        }
    }
}
void MakeCircle(SDL_Renderer* renderer, int cenx1, int ceny1, int rad1)
{
    for (int x = -rad1; x <= rad1; x++)
    {
        for (int y = -rad1; y <= rad1; y++) 
        {
            if (x * x + y * y <= rad1 * rad1) 
            {
                SDL_RenderDrawPoint(renderer, cenx1 + x, ceny1 + y);
            }
        }
    }
}

void update()
{
    CENTER_x1 +=2;

    if(CENTER_x1 - radius_1 >= SCREEN_WIDTH)

    CENTER_x1 = -radius_1;

    SDL_RenderClear(Renderer);

    SDL_SetRenderDrawColor(Renderer, 255, 200, 150, 255);

    SDL_RenderClear(Renderer);
    
    SDL_SetRenderDrawColor(Renderer,10,10,10,10);
}
void render()
{
    MakeCircle(Renderer, CENTER_x1, CENTER_y1, radius_1);

    SDL_RenderPresent(Renderer);

    MakeCircle(Renderer, CENTER_x2, CENTER_y2, radius_2);

    SDL_RenderPresent(Renderer);
}
void collision()
{
    
    int displacement = sqrt((CENTER_x1-CENTER_x2) * (CENTER_x1 - CENTER_x2) + (CENTER_y1-CENTER_y2) * (CENTER_y1-CENTER_y2));
    if(displacement <= radius_1 + radius_2)
    {
    SDL_Rect r;
    r.x = 0;

    r.y = 0;

    r.w = SCREEN_WIDTH;

    r.h = SCREEN_HEIGHT;

    SDL_RenderClear(Renderer);

    SDL_SetRenderDrawColor(Renderer, 50,100, 150, 200);

    SDL_RenderClear(Renderer);

    SDL_SetRenderDrawColor(Renderer, 300, 150, 75, 35);

    SDL_RenderDrawRect(Renderer,&r);

    SDL_RenderPresent(Renderer);
    }
}

void destroy_Window()
{
    SDL_DestroyRenderer(Renderer);

    SDL_DestroyWindow(Window);

    SDL_Quit();
}

int main(int argc, char *argv[])
{
    game_running=activatewindow();

    while(game_running!=false)
    { 
        processinginput();
        
update();
        render();
        
        collision();
    } 

   destroy_Window();   

  return 0;
}