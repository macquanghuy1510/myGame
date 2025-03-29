#include <iostream>
#include <vector>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

void waitUntilKeyPressed();

void picture(Graphics graphics)
{
    SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
    SDL_RenderClear(graphics.renderer);
    SDL_Texture* img = graphics.loadTexture("map.png");
    graphics.prepareScene(img);
    SDL_Texture* button = graphics.loadTexture("buttonstartgame (1)thugon.PNG");
    graphics.renderTexture(button, 450, 300);
    graphics.presentScene();
    SDL_DestroyTexture(img);
    SDL_DestroyTexture(button);
}

void draw(Graphics graphics)
{
    SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
    SDL_RenderClear(graphics.renderer);
    SDL_Texture* img = graphics.loadTexture("bikiniBottom.jpg");
    graphics.renderTexture(img, 300, 300);
    graphics.presentScene();
    SDL_DestroyTexture(img);
}

int clickMouseEvent(int x, int y)
{
    if(x > 325 && x < 579 && y > 66 && y < 166) return 0;
    if(x > 220 && x < 695 && y > 238 && y < 338) return 1;
    if(x > 180 && x < 730 && y > 411 && y < 511) return 2;
}
bool clickOnBack1()
{
    int x, y;
    SDL_Event eventchuot;
    while(true)
    {
        SDL_PollEvent(&eventchuot);
        SDL_GetMouseState(&x, &y);
        //cout << x << ' ' << y << endl;
        if(eventchuot.type == SDL_MOUSEBUTTONDOWN)
        {
            if(eventchuot.button.button == SDL_BUTTON_LEFT)
            {
                if(x > 180 && x < 420 && y > 473 && y < 573) return true;
            }
        }
        SDL_Delay(100);
    }
    return false;
}
bool clickOnBack2()
{
    int x, y;
    SDL_Event eventchuot;
    while(true)
    {
        SDL_PollEvent(&eventchuot);
        SDL_GetMouseState(&x, &y);
        //cout << x << ' ' << y << endl;
        if(eventchuot.type == SDL_MOUSEBUTTONDOWN)
        {
            if(eventchuot.button.button == SDL_BUTTON_LEFT)
            {
                if(x > 469 && x < 709 && y > 465 && y < 565) return true;
            }
        }
        SDL_Delay(100);
    }
    return false;
}

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    SDL_Texture* menu = graphics.loadTexture("START.png");
    SDL_Texture* rulegame = graphics.loadTexture("RuleGame.png");
    SDL_Texture* topscore = graphics.loadTexture("TopScore.png");
    graphics.prepareScene(menu);
    graphics.presentScene();
    SDL_Event eventchuot;
    int x, y;
    bool quit = true;
    while(quit)
    {
        SDL_PollEvent(&eventchuot);
        SDL_GetMouseState(&x, &y);
        cout << x << ' ' << y << endl;
        if(eventchuot.type == SDL_QUIT)
        {
            quit = false;
            break;
        }
        else if(eventchuot.type == SDL_MOUSEBUTTONDOWN)
        {
            if(eventchuot.button.button == SDL_BUTTON_LEFT)
            {
                switch(clickMouseEvent(x, y))
                {
                    case 0:
                        break;
                    case 2:
                        graphics.prepareScene(rulegame);
                        graphics.presentScene();
                        while(true)
                        {
                            if(clickOnBack1())
                            {
                                break;
                            }
                        }
                        graphics.prepareScene(menu);
                        graphics.presentScene();
                        break;
                    case 1:
                        graphics.prepareScene(topscore);
                        graphics.presentScene();
                        while(true)
                        {
                            if(clickOnBack2())
                            {
                                break;
                            }
                        }
                        graphics.prepareScene(menu);
                        graphics.presentScene();
                        break;
                }
            }
        }
        SDL_Delay(100);
    }
    SDL_DestroyTexture(menu);
    SDL_DestroyTexture(rulegame);
    SDL_DestroyTexture(topscore);
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

