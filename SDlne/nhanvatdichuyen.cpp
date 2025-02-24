#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

void waitUntilKeyPressed();

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    SDL_Texture* imgmap = graphics.loadTexture("greenmap.png");
    graphics.prepareScene(imgmap);
    graphics.presentScene();
    int infor[14][2];
    int row = 0, col = 0;
    for(int i = 0; i < 14; i++)
    {
        if(i >= 5 && i <= 9) row = 168;
        else if(i >= 10) row = 336;
        infor[i][0] = col;
        infor[i][1] = row;
        col += 183;
        if(i == 4 || i == 9) col = 0;
    }

    SDL_Texture* img = graphics.loadTexture("83127-sprite-area-line-animated-bird-film.png");
    int y = 200;
    SDL_Event e;
    bool check = true;
    while(check)
    {
        if(e.type == SDL_QUIT)
        {
            check = false;
        }
        else
        {
            for(int i = 0; i < 14; i++)
            {
                SDL_Rect hcn1 = {infor[i][0], infor[i][1], 183, 168};//in frame nao
                if(e.key.keysym.scancode == SDL_SCANCODE_UP) y -= 50;
                else if(e.key.keysym.scancode == SDL_SCANCODE_DOWN) y += 50;
                SDL_Rect hcn2 = {200, y, 100, 100};//in ra dau tren man hinh
                SDL_RenderCopy(graphics.renderer, img, &hcn1, &hcn2);
                graphics.presentScene();
                SDL_Delay(50);
                SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 255);
                SDL_RenderClear(graphics.renderer);
                //graphics.prepareScene(imgmap);
                //graphics.presentScene();
            }
        }
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

