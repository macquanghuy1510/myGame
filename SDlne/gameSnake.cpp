#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <time.h>
#include <vector>
#include <cmath>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

void waitUntilKeySpacePressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 )
        {
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_SPACE) return;
            }
        }
        SDL_Delay(100);
    }
}

void drawRec(Graphics graphics, int x, int y, int w, int h)
{
    SDL_Rect rec = {x, y, w, h};
    SDL_SetRenderDrawColor(graphics.renderer, 2, 100, 255, 255);
    SDL_RenderDrawRect(graphics.renderer, &rec);
    graphics.presentScene();
}

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    drawRec(graphics, 300, 300, 200, 100);
    waitUntilKeySpacePressed();

    graphics.quit();
}
