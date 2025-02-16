#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

void waitUntilKeyPressed();

void draw(Graphics graphics, int scrolling)
{
    SDL_Texture* img = graphics.loadTexture("123456.png");
    SDL_Rect hcn1 = {0 - scrolling, 0, 800, 600};
    SDL_Rect hcn2 = {800, 0, 800, 600};
    if(hcn1.x > 0)
    {
        hcn2.x = hcn1.x - 800;
    }
    else if(hcn1.x < 0)
    {
        hcn2.x = hcn1.x + 800;
    }
    SDL_RenderCopy(graphics.renderer, img, NULL, &hcn1);
    SDL_RenderCopy(graphics.renderer, img, NULL, &hcn2);
    graphics.presentScene();
}

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    int step = 50;
    int scrolling = 0;
    SDL_Texture* img = graphics.loadTexture("123456.png");
    SDL_Rect hcn1 = {0, 0, 800, 600};
    SDL_Rect hcn2 = {800, 0, 800, 600};
    SDL_RenderCopy(graphics.renderer, img, NULL, &hcn1);
    SDL_RenderCopy(graphics.renderer, img, NULL, &hcn2);
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
                break;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                {
                    //cout << "Down at RIGHT\n";
                    scrolling += step;
                    if(scrolling == 800) scrolling = 0;
                    draw(graphics, scrolling);
                }
                else if(e.key.keysym.scancode == SDL_SCANCODE_LEFT)
                {
                    //cout << "Down at LEFT\n";
                    scrolling -= step;
                    if(scrolling == -800) scrolling = 0;
                    draw(graphics, scrolling);
                }
            }
        }
        SDL_Delay(50);
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


