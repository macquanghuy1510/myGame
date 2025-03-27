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

bool click()
{
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
                if(x > 450 && x < 635 && y > 300 && y < 385) return true;
            }
        }
        SDL_Delay(100);
    }
    return false;
}

void change(int n, char* tmp)
{
    vector<int> nums;
    while(n)
    {
        nums.push_back(n % 10);
        n /= 10;
    }
    int l = nums.size();
    for(int i = l - 1; i >= 0; i--)
    {
        *(tmp + l - i - 1) = (nums[i] + '0');
    }
    *(tmp + l) = '\0';
}

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    TTF_Font* font = graphics.loadFont("Purisa-BoldOblique.ttf", 30);
    SDL_Color color = {204, 49, 61, 255};
    int n = 1243;
    char tmp[] = "abcdef";
    change(n, tmp);
    SDL_Texture* question = graphics.renderText(tmp, font, color);
    graphics.renderTexture(question, 200, 300);
    graphics.presentScene();
    waitUntilKeyPressed();
    SDL_Event eventchuot;
    int x, y;
    while(true)
    {
        SDL_PollEvent(&eventchuot);
        if(eventchuot.type == SDL_QUIT)
        {
            break;
        }
        else if(eventchuot.type == SDL_MOUSEBUTTONDOWN)
        {
            if(eventchuot.button.button == SDL_BUTTON_LEFT)
            {
                picture(graphics);
                if(click()) draw(graphics);
            }
        }
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

