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
    /*SDL_Rect hcn = {300, 250, 200, 100};
    SDL_SetRenderDrawColor(graphics.renderer, 0, 180, 255, 200);
    SDL_RenderDrawRect(graphics.renderer, &hcn);
    graphics.presentScene();*/
    int x, y;
    SDL_Event eventchuot;
    while(true)
    {
        SDL_PollEvent(&eventchuot);
        SDL_GetMouseState(&x, &y);
        if(eventchuot.type == SDL_QUIT)
        {
            break;
        }
        else if(eventchuot.type == SDL_MOUSEBUTTONDOWN)
        {
            if(eventchuot.button.button == SDL_BUTTON_LEFT)
            {
                cout << "Button left at: " << x << ' ' << y << endl;
            }
            else if(eventchuot.button.button == SDL_BUTTON_RIGHT)
            {
                cout << "Button right at: " << x << ' ' << y << endl;
            }
        }
        SDL_Delay(100);
    }

    graphics.quit();
    return 0;
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

