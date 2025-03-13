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
    mySnake.menuGame();
    do
    {
        if(mySnake.clickToKnowRule())
        {
            mySnake.renderRuleOfGame();
            mySnake.waitUntilKeySpacePressed();
            mySnake.menuGame();
        }
    } while(!mySnake.clickToStart());
    bool ok = false;
    bool start = false;
    if(mySnake.clickToStart()) start = true;
    do
    {
        if(start) mySnake.playAGame();
        ok = mySnake.askToPlayAgain();
    } while(ok);
}
