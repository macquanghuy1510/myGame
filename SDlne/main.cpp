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
    SDL_Texture* background = graphics.loadTexture("bikiniBottom.jpg");
    graphics.prepareScene(background);
    graphics.presentScene();
    waitUntilKeyPressed();
    SDL_Texture* img = graphics.loadTexture("Spongebob.png");
    graphics.renderTexture(img, 400, 300);
    graphics.presentScene();
    waitUntilKeyPressed();

    SDL_DestroyTexture(background);
    background = NULL;
    SDL_DestroyTexture(img);
    img = NULL;
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
