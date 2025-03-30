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
    SDL_Event eventchuot;
    int x, y;
    bool quit = true;
    while(quit)
    {
        SDL_PollEvent(&eventchuot);
        SDL_GetMouseState(&x, &y);
        //cout << x << ' ' << y << endl;
        mySnake.menuGame();
        if(eventchuot.type == SDL_QUIT)
        {
            quit = false;
            break;
        }
        else if(eventchuot.type == SDL_MOUSEBUTTONDOWN)
        {
            if(eventchuot.button.button == SDL_BUTTON_LEFT)
            {
                switch(mySnake.clickMouseEvent(x, y))
                {
                    case 0:
                        mySnake.playGame();
                        break;
                    case 2:
                        mySnake.renderRule();
                        while(true)
                        {
                            if(mySnake.clickOnBack1())
                            {
                                break;
                            }
                        }
                        break;
                    case 1:
                        mySnake.renderTopScore();
                        while(true)
                        {
                            if(mySnake.clickOnBack2())
                            {
                                break;
                            }
                        }
                        break;
                }
            }
        }
        SDL_Delay(100);
    }
    mySnake.destroyAllTexture();
    mySnake.graphics.quit();
}
