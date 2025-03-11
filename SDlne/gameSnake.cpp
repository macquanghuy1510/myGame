#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <time.h>
#include <vector>
#include <cmath>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

#define SIZE 30
#define INIT_LEN 3
#define STEP 30
int stepX = 0;
int stepY = 0;
Graphics graphics;

void waitUntilKeyPressed();
void waitUntilKeySpacePressed();

struct Snake
{
    vector<SDL_Rect> node;
    string direction = "right";
    SDL_Rect food = {600, 150, SIZE, SIZE};
    double angle = 0;
    void initMap(SDL_Texture* imgmap)
    {
        graphics.prepareScene(imgmap);
    }
    void initSnake(SDL_Texture* imgdau, SDL_Texture* imgthan)
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
    void makeIndexFood()
    {
        int x, y;
        do
        {
            x = rand() % 28 + 1;
            y = rand() % 18 + 1;
        } while(!checkIndexOfFood(x, y));
        food.x = x * SIZE;
        food.y = y * SIZE;
    }
    void renderFood(SDL_Texture* imgfood)
    {
        graphics.renderTexture(imgfood, food.x, food.y);
    }
    void render(SDL_Texture* imgdau, SDL_Texture* imgthan)
    {
        for(int i = 0; i < node.size(); i++)
        {
            if(i == 0)
            {
                if(direction == "right") angle = 0;
                else if(direction == "down") angle = 90;
                else if(direction == "left") angle = 180;
                else angle = 270;
                graphics.rotateImage(imgdau, node[i].x, node[i].y, angle);
            }
            else graphics.renderTexture(imgthan, node[i].x, node[i].y);
        }
    }
    bool ateFood()
    {
        int a = node[0].x + SIZE / 2;
        int b = node[0].y + SIZE / 2;
        int c = food.x + SIZE / 2;
        int d = food.y + SIZE / 2;
        double khoangcach = sqrt(pow(a - c, 2) + pow(b - d, 2));
        return (khoangcach < SIZE);
    }
    void increaseSizeOfSnake()
    {
        node.resize(node.size() + 1);
    }
    bool isGameOver()
    {
        if(node[0].y < 30 && angle == 270 ||
           node[0].y + 30 > 570 && angle == 90 ||
           node[0].x < 30 && angle == 180 ||
           node[0].x + 30 > 870 && angle == 0)
            return true;
        int a = node[0].x + SIZE / 2;
        int b = node[0].y + SIZE / 2;
        for(int i = 1; i < node.size(); i++)
        {
            int c = node[i].x + SIZE / 2;
            int d = node[i].y + SIZE / 2;
            if(sqrt(pow(a - c, 2) + pow(b - d, 2)) < SIZE)
                    return true;
        }
        return false;
    }
    void move()
    {
        for(int i = node.size() - 1; i >= 1; i--)
        {
            node[i].x = node[i - 1].x;
            node[i].y = node[i - 1].y;
        }
        SDL_Delay(50);
        node[0].x += stepX;
        node[0].y += stepY;
    }
    void turnleft()
    {
        stepX = -STEP;
        stepY = 0;
        if(node[0].y != node[1].y) direction = "left";
    }
    void turnright()
    {
        stepX = STEP;
        stepY = 0;
        if(node[0].y != node[1].y) direction = "right";
    }
    void turnup()
    {
        stepX = 0;
        stepY = -STEP;
        if(node[0].x != node[1].x) direction = "up";
    }
    void turndown()
    {
        stepX = 0;
        stepY = STEP;
        if(node[0].x != node[1].x) direction = "down";
    }
    void menuGame()
    {
        SDL_Rect hcn1 = {390, 160, 120, 80};
        SDL_Rect hcn2 = {280, 300, 350, 80};
        SDL_SetRenderDrawColor(graphics.renderer, 2, 119, 189, 255);
        SDL_RenderFillRect(graphics.renderer, &hcn1);
        SDL_RenderFillRect(graphics.renderer, &hcn2);
        TTF_Font* font = graphics.loadFont("Purisa-BoldOblique.ttf", 50);
        SDL_Color color = {244, 255, 129, 255};
        SDL_Texture* play = graphics.renderText("Play", font, color);
        SDL_Texture* howtoplay = graphics.renderText("How to play", font, color);
        graphics.renderTexture(play, 390, 160);
        graphics.renderTexture(howtoplay, 280, 300);
        graphics.presentScene();
    }
    bool clickToStart()
    {
        SDL_Event e;
        bool check = false;
        bool quit = true;
        int x, y;
        while(quit)
        {
            if(SDL_PollEvent(&e))
            {
                SDL_GetMouseState(&x, &y);
                switch(e.type)
                {
                    case SDL_MOUSEBUTTONDOWN:
                        if(e.button.button == SDL_BUTTON_LEFT && x > 390 && x < 510 && y > 160 && y < 240)
                        {
                            check = true;
                            quit = false;
                            break;
                        }
                }
            }
        }
        return check;
    }
    bool askToPlayAgain()
    {
        SDL_Rect hcn1 = {380, 250, 100, 50};
        SDL_Rect hcn2 = {380, 350, 100, 50};
        SDL_SetRenderDrawColor(graphics.renderer, 2, 119, 189, 255);
        SDL_RenderFillRect(graphics.renderer, &hcn1);
        SDL_RenderFillRect(graphics.renderer, &hcn2);
        TTF_Font* font = graphics.loadFont("Purisa-BoldOblique.ttf", 30);
        SDL_Color color = {244, 255, 129, 255};
        SDL_Texture* question = graphics.renderText("Do you want to play again?", font, color);
        SDL_Texture* ansY = graphics.renderText("YES", font, color);
        SDL_Texture* ansN = graphics.renderText("NO", font, color);
        graphics.renderTexture(question, 200, 150);
        graphics.renderTexture(ansY, 395, 250);
        graphics.renderTexture(ansN, 400, 350);
        graphics.presentScene();
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
                    if(x > 380 && x < 480 && y > 250 && y < 300) return true;
                    if(x > 380 && x < 480 && y > 350 && y < 400) return false;
                }
            }
            SDL_Delay(100);
        }
    }
    void playAGame()
    {
        menuGame();
        if(clickToStart())
        {
            SDL_Texture* imgdau = graphics.loadTexture("dau.png");
            SDL_Texture* imgthan = graphics.loadTexture("than.png");
            SDL_Texture* imgmap = graphics.loadTexture("map.png");
            SDL_Texture* imgfood = graphics.loadTexture("foodpixel.png");
            Mix_Chunk* eatsound = graphics.loadSound("applebitesound.mp3");
            Mix_Music* nhacnen = graphics.loadMusic("backgroundmusic.mp3");
            Mix_Chunk* gameoversound = graphics.loadSound("gameoversound1.mp3");
            graphics.playMusic(nhacnen);
            Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
            initMap(imgmap);
            renderFood(imgfood);
            initSnake(imgdau, imgthan);
            SDL_Event e;
            bool check = true;
            bool ok = false;
            int cnt = 0;
            while(check)
            {
                if(isGameOver())
                {
                    angle = 0;
                    graphics.playChunk(gameoversound);
                    Mix_VolumeChunk(gameoversound, MIX_MAX_VOLUME / 3);
                    SDL_Delay(4000);
                    break;
                }
                string newDirection = direction;
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT) break;
                    if(e.type == SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_LEFT:
                                if(direction != "right")
                                {
                                    newDirection = "left";
                                    ok = true;
                                }
                                break;
                            case SDLK_RIGHT:
                                if(direction != "left")
                                {
                                    newDirection = "right";
                                    ok = true;
                                }
                                break;
                            case SDLK_UP:
                                if(direction != "down")
                                {
                                    newDirection = "up";
                                    ok = true;
                                }
                                break;
                            case SDLK_DOWN:
                                if(direction != "up")
                                {
                                    newDirection = "down";
                                    ok = true;
                                }
                                break;
                            case SDLK_ESCAPE: check = false; break;
                            case SDLK_SPACE: waitUntilKeySpacePressed(); break;
                        }
                    }
                }
                direction = newDirection;
                if(direction == "left") turnleft();
                else if(direction == "right") turnright();
                else if(direction == "up") turnup();
                else turndown();
                initMap(imgmap);
                renderFood(imgfood);
                if(ateFood())
                {
                    graphics.playChunk(eatsound);
                    increaseSizeOfSnake();
                    makeIndexFood();
                    renderFood(imgfood);
                }
                if(ok) move();
                SDL_Delay(60);
                render(imgdau, imgthan);
                graphics.presentScene();
            }
        }
        graphics.quit();
    }
    /*void playMoreAGame()
    {

        bool playAgain = false;
        do
        {
            playAGame(graphics);
            playAgain = askToPlayAgain(graphics);
        } while(playAgain);
    }*/
};

int main(int argc, char* argv[])
{
    graphics.init();
    Snake mySnake;
    mySnake.playAGame();
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

void waitUntilKeySpacePressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 )
        {
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_SPACE) return;
            }
        }
        SDL_Delay(100);
    }
}
