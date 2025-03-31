#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"
#include "libgame.h"

using namespace std;

int main(int argc, char* argv[])
{
    Snake mySnake;
    mySnake.graphics.init();
    mySnake.loadAllTexture();
    mySnake.mainLoopGame();
    mySnake.destroyAllTexture();
    mySnake.graphics.quit();
}
