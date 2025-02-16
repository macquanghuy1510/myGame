#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

void waitUntilKeyPressed();

void draw(Graphics graphics, int x, int y)
{
    SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
    SDL_RenderClear(graphics.renderer);
    SDL_SetRenderDrawColor(graphics.renderer, 0, 200, 250, 250);
    SDL_Rect hcn = {x, y, 50, 50};
    SDL_RenderDrawRect(graphics.renderer, &hcn);
    graphics.presentScene();
}
int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    int x = 400, y = 300;
    int step = 60;
    SDL_Rect hcn = {x, y, 50, 50};
    SDL_SetRenderDrawColor(graphics.renderer, 0, 200, 250, 250);
    SDL_RenderDrawRect(graphics.renderer, &hcn);
    graphics.presentScene();
    SDL_Event e;
    bool check = true;
    while(check)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                check = false;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.scancode == SDL_SCANCODE_A)
                {
                    x -= step;
                    draw(graphics, x, y);
                }
                else if(e.key.keysym.scancode == SDL_SCANCODE_D)
                {
                    x += step;
                    draw(graphics, x, y);
                }
                else if(e.key.keysym.scancode == SDL_SCANCODE_S)
                {
                    y += step;
                    draw(graphics, x, y);
                }
                else if(e.key.keysym.scancode == SDL_SCANCODE_W)
                {
                    y -= step;
                    draw(graphics, x, y);
                }
            }
        }
        SDL_Delay(5);
    }
    graphics.quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

