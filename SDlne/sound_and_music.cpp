#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

void waitUntilKeyPressed();

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    Mix_Chunk* eatsound = graphics.loadSound("applebitesound.mp3");
    Mix_Music* nhacnen = graphics.loadMusic("backgroundmusic.mp3");
    SDL_Event e;
    bool quit = true;
    while(quit)
    {
        if(SDL_PollEvent(&e) == 0) continue;
        if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_SPACE:
                    graphics.playChunk(eatsound);
                    Mix_VolumeChunk(eatsound, MIX_MAX_VOLUME / 2);
                    break;
                case SDLK_m:
                    graphics.playMusic(nhacnen);
                    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
                    break;
                case SDLK_ESCAPE: quit = false; break;
            }
        }
    }
    //waitUntilKeyPressed();
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

