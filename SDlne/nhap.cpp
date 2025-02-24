#include <iostream>
#include <SDL_image.h>
#include <time.h>
#include <vector>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

#define SIZE 30
#define INIT_LEN 20

int stepX = 0;
int stepY = 0;

void waitUntilKeyPressed();

struct Snake
{
    vector<SDL_Rect> node;
    string direction = "right";

    void initMap(Graphics graphics, SDL_Texture* imgmap)
    {
        graphics.prepareScene(imgmap);
    }
    void initSnake(Graphics graphics, SDL_Texture* imgdau, SDL_Texture* imgthan)
    {
        node.resize(INIT_LEN);
        node[0] = {180, 150, SIZE, SIZE};
        for(int i = 1; i < INIT_LEN; i++)
        {
            node[i] = {node[i - 1].x - SIZE, 150, SIZE, SIZE};
        }
        for(int i = 0; i < INIT_LEN; i++)
        {
            if(i == 0) graphics.renderTexture(imgdau, node[i].x, node[i].y);
            else graphics.renderTexture(imgthan, node[i].x, node[i].y);
        }
        graphics.presentScene();
    }
    bool checkIndexOfFood(int x, int y)
    {
        for(int i = 0; i < node.size(); i++)
        {
            if(x * SIZE == node[i].x && y * SIZE == node[i].y)
                return false;
        }
        return true;
    }
    void makeFood(Graphics graphics)
    {
        int x, y;
        do
        {
            x = rand() % 28 + 1;
            y = rand() % 18 + 1;
        } while(!checkIndexOfFood(x, y));

        SDL_Rect food = {x * SIZE, y * SIZE, SIZE, SIZE};
        SDL_SetRenderDrawColor(graphics.renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(graphics.renderer, &food);
        graphics.presentScene();
    }
    void render(Graphics graphics, SDL_Texture* imgdau, SDL_Texture* imgthan)
    {
        for(int i = 0; i < node.size(); i++)
        {
            if(i == 0)
            {
                double angle;
                if(direction == "right") angle = 0;
                else if(direction == "down") angle = 90;
                else if(direction == "left") angle = 180;
                else angle = 270;
                graphics.rotateImage(imgdau, node[i].x, node[i].y, angle);
            }
            else graphics.renderTexture(imgthan, node[i].x, node[i].y);
        }
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
        direction = "left";
    }
    void turnright()
    {
        stepX = SIZE;
        stepY = 0;
        direction = "right";
    }
    void turnup()
    {
        stepX = 0;
        stepY = -SIZE;
        direction = "up";
    }
    void turndown()
    {
        stepX = 0;
        stepY = SIZE;
        direction = "down";
    }
};

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    SDL_Texture* imgdau = graphics.loadTexture("dau.png");
    SDL_Texture* imgthan = graphics.loadTexture("than.png");
    SDL_Texture* imgmap = graphics.loadTexture("map.png");
    Snake mySnake;
    mySnake.initMap(graphics, imgmap);
    mySnake.initSnake(graphics, imgdau, imgthan);
    SDL_Event e;
    bool check = true;
    bool ok = false;
    while(check)
    {
        if(SDL_PollEvent(&e) != 0)
            if(e.type == SDL_QUIT) break;
            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        if(mySnake.direction != "right")
                            mySnake.turnleft(); break;
                    case SDLK_RIGHT:
                        ok = true;
                        if(mySnake.direction != "left")
                            mySnake.turnright(); break;
                    case SDLK_UP:
                        ok = true;
                        if(mySnake.direction != "down")
                            mySnake.turnup(); break;
                    case SDLK_DOWN:
                        ok = true;
                        if(mySnake.direction != "up")
                            mySnake.turndown(); break;
                    case SDLK_ESCAPE: check = false; break;
                }
            }
        mySnake.initMap(graphics, imgmap);
        if(ok) mySnake.move();
        SDL_Delay(200);
        mySnake.render(graphics, imgdau, imgthan);
        //mySnake.makeFood(graphics);
        graphics.presentScene();

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
