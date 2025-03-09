#include <iostream>
#include <SDL_image.h>
#include <time.h>
#include <vector>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"
#include "logicGame.h"

using namespace std;

#define SIZE 30
#define INIT_LEN 20

int stepX = 0;
int stepY = 0;

void waitUntilKeyPressed();

struct Snake
{
    vector<SDL_Rect> node;
    void initsnake(Graphics graphics)
    {
        node.resize(INIT_LEN);
        node[0] = {180, 150, SIZE, SIZE};
        for(int i = 1; i < INIT_LEN; i++)
        {
            node[i] = {node[i - 1].x - SIZE, 150, SIZE, SIZE};
        }
        for(int i = 0; i < INIT_LEN; i++)
        {
            SDL_SetRenderDrawColor(graphics.renderer, 250, 0, 0, 255);
            SDL_RenderDrawRect(graphics.renderer, &node[i]);
        }
        graphics.presentScene();
    }
    void render(Graphics graphics)
    {
        SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
        SDL_RenderClear(graphics.renderer);
        for(int i = 0; i < node.size(); i++)
        {
            SDL_SetRenderDrawColor(graphics.renderer, 250, 0, 0, 255);
            SDL_RenderDrawRect(graphics.renderer, &node[i]);
        }
        graphics.presentScene();
    }
    void move()
    {
        for(int i = node.size() - 1; i >= 1; i--)
        {
            node[i].x = node[i - 1].x;
            node[i].y = node[i - 1].y;
        }
        node[0].x += stepX;
        node[0].y += stepY;
    }
    void turnleft()
    {
        stepX = -SIZE;
        stepY = 0;
    }
    void turnright()
    {
        stepX = SIZE;
        stepY = 0;
    }
    void turnup()
    {
        stepX = 0;
        stepY = -SIZE;
    }
    void turndown()
    {
        stepX = 0;
        stepY = SIZE;
    }
};

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    Snake mySnake;
    mySnake.initsnake(graphics);
    SDL_Event e;
    while(true)
    {
        mySnake.render(graphics);
        SDL_Delay(50);
        mySnake.move();
        if(SDL_PollEvent(&e) == 0) continue;
        if(e.type == SDL_QUIT) break;
        if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_LEFT: mySnake.turnleft(); break;
                case SDLK_RIGHT: mySnake.turnright(); break;
                case SDLK_UP: mySnake.turnup(); break;
                case SDLK_DOWN: mySnake.turndown(); break;
            }
        }
    }
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
