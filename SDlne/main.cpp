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
    mySnake.menuGame();
    bool ok = false;
    bool check = false;
    if(mySnake.clickToStart()) check = true;
    do
    {
        if(check) mySnake.playAGame();
        ok = mySnake.askToPlayAgain();
    } while(ok);

    mySnake.destroyAllTexture();
    mySnake.graphics.quit();
}
