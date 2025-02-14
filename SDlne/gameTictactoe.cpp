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

    SDL_Texture* cellempty = graphics.loadTexture("cell_empty.png");
    SDL_Texture* cellx = graphics.loadTexture("cell_x.png");
    SDL_Texture* cello = graphics.loadTexture("cell_o.png");
    int b = 250;
    int n = 5;
    for(int i = 0; i < n; i++)
    {
        int a = 330;
        for(int j = 0; j < n; j++)
        {
            graphics.renderTexture(cellempty, a, b);
            a += 30;
        }
        b += 30;
    }
    graphics.presentScene();
    SDL_Event eventchuot;
    int ok = 1;
    while(true)
    {
        SDL_PollEvent(&eventchuot);
        if(eventchuot.type == SDL_QUIT)
        {
            break;
        }
        else if(eventchuot.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            //cout << x << ' ' << y << endl;
            if(x >= 330 && x < 330 + 30*n && y >= 250 && y < 250 + 30*n)
            {
                //cout << x << ' ' << y << endl;
                int col = (x - 330) / 30;
                int row = (y - 250) / 30;
                //cout << row << ' ' << col << endl;
                x = 330 + 30*col;
                y = 250 + 30*row;
                //cout << x << ' ' << y << endl;
                if(ok)
                {
                    graphics.renderTexture(cellx, x, y);
                    graphics.presentScene();
                    ok = 0;
                }
                else
                {
                    graphics.renderTexture(cello, x, y);
                    graphics.presentScene();
                    ok = 1;
                }
            }
        }
    }
    graphics.presentScene();
    waitUntilKeyPressed();
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
