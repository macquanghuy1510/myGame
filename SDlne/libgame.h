#ifndef _LIBGAME_H
#define _LIBGAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstring>
#include <vector>
#include <cmath>
#include "graphics.h"
#include "defs.h"

using namespace std;

struct Snake
{
    vector<SDL_Rect> node;
    string direction = "right";
    SDL_Rect food = {600, 150, SIZE, SIZE};
    double angle = 0;
    int stepX = 0;
    int stepY = 0;
    Graphics graphics;

    Snake()
    {
        graphics.init();
    }
    void initMap()
    {
        SDL_Texture* imgmap = graphics.loadTexture("map.png");
        graphics.prepareScene(imgmap);
        SDL_DestroyTexture(imgmap);
    }
    void initSnake()
    {
        SDL_Texture* imgdau = graphics.loadTexture("dau.png");
        SDL_Texture* imgthan = graphics.loadTexture("than.png");
        node.resize(INIT_LEN);
        node[0] = {180, 150, SIZE, SIZE};
        for(int i = 1; i < INIT_LEN; i++)
        {
            node[i] = {node[i - 1].x - SIZE, 150, SIZE, SIZE};
        }
        for(int i = 0; i < INIT_LEN; i++)
        {
            if(i == 0) graphics.rotateImage(imgdau, node[i].x, node[i].y, angle);
            else graphics.renderTexture(imgthan, node[i].x, node[i].y);
        }
        graphics.presentScene();
        SDL_DestroyTexture(imgdau);
        SDL_DestroyTexture(imgthan);
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
    void renderFood()
    {
        SDL_Texture* imgfood = graphics.loadTexture("foodpixel.png");
        graphics.renderTexture(imgfood, food.x, food.y);
        SDL_DestroyTexture(imgfood);
    }
    void renderSnake()
    {
        SDL_Texture* imgdau = graphics.loadTexture("dau.png");
        SDL_Texture* imgthan = graphics.loadTexture("than.png");
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
        SDL_DestroyTexture(imgdau);
        SDL_DestroyTexture(imgthan);
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
    void soundWhenEatFood()
    {
        Mix_Chunk* eatsound = graphics.loadSound("applebitesound.mp3");
        graphics.playChunk(eatsound);
        //Mix_FreeChunk(eatsound);
    }
    void soundWhenGameOver()
    {
        Mix_Chunk* gameoversound = graphics.loadSound("gameoversound1.mp3");
        graphics.playChunk(gameoversound);
        Mix_VolumeChunk(gameoversound, MIX_MAX_VOLUME / 3);
        Mix_FreeChunk(gameoversound);
    }
    void soundWhenSwitch()
    {
        Mix_Chunk* switchsound = graphics.loadSound("soundswitch.wav");
        graphics.playChunk(switchsound);
        Mix_VolumeChunk(switchsound, MIX_MAX_VOLUME / 3);
        Mix_FreeChunk(switchsound);
    }
    void backgroundMusic()
    {
        Mix_Music* nhacnen = graphics.loadMusic("backgroundmusic.mp3");
        graphics.playMusic(nhacnen);
        Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
        Mix_FreeMusic(nhacnen);
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
    }
    void turnright()
    {
        stepX = STEP;
        stepY = 0;
    }
    void turnup()
    {
        stepX = 0;
        stepY = -STEP;
    }
    void turndown()
    {
        stepX = 0;
        stepY = STEP;
    }
    void menuGame()
    {
        backgroundMusic();
        SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
        SDL_RenderClear(graphics.renderer);
        SDL_Texture* background = graphics.loadTexture("background.jpg");
        SDL_Texture* buttonstart = graphics.loadTexture("buttonstartgamethugon.PNG");
        graphics.prepareScene(background);
        graphics.renderTexture(buttonstart, 265, 200);
        TTF_Font* font = graphics.loadFont("Purisa-BoldOblique.ttf", 70);
        SDL_Color color = {204, 49, 61, 255};
        SDL_Texture* play = graphics.renderText("START", font, color);
        graphics.renderTexture(play, 315, 245);
        graphics.presentScene();
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(buttonstart);
        SDL_DestroyTexture(play);
        TTF_CloseFont(font);
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
                        if(e.button.button == SDL_BUTTON_LEFT && x > 265 && x < 634 && y > 200 && y < 391)
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
        backgroundMusic();
        SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
        SDL_RenderClear(graphics.renderer);
        SDL_Texture* background = graphics.loadTexture("background.jpg");
        graphics.prepareScene(background);
        SDL_Texture* button = graphics.loadTexture("buttonstartgame (1)thugon.PNG");
        graphics.renderTexture(button, 340, 242);
        graphics.renderTexture(button, 340, 382);
        TTF_Font* font = graphics.loadFont("Purisa-BoldOblique.ttf", 40);
        SDL_Color color = {204, 49, 61, 255};
        SDL_Texture* question = graphics.renderText("Do you want to play again?", font, color);
        SDL_Texture* ansY = graphics.renderText("YES", font, color);
        SDL_Texture* ansN = graphics.renderText("NO", font, color);
        graphics.renderTexture(question, 130, 150);
        graphics.renderTexture(ansY, 390, 260);
        graphics.renderTexture(ansN, 400, 400);
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
                    if(x > 340 && x < 525 && y > 242 && y < 327) return true;
                    if(x > 340 && x < 525 && y > 382 && y < 467) return false;
                }
            }
            SDL_Delay(100);
        }
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(button);
        SDL_DestroyTexture(question);
        SDL_DestroyTexture(ansY);
        SDL_DestroyTexture(ansN);
        TTF_CloseFont(font);
    }
    void reset()
    {
        food.x = 600;
        food.y = 150;
        node[0].x = 180;
        node[0].y = 150;
        direction = "right";
    }
    void playAGame()
    {
        Mix_HaltMusic();
        initMap();
        renderFood();
        initSnake();
        SDL_Event e;
        bool check = true;
        bool ok = false;
        while(check)
        {
            if(isGameOver())
            {
                soundWhenGameOver();
                reset();
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
                                soundWhenSwitch();
                                newDirection = "left";
                                ok = true;
                            }
                            break;
                        case SDLK_RIGHT:
                            if(direction != "left")
                            {
                                soundWhenSwitch();
                                newDirection = "right";
                                ok = true;
                            }
                            break;
                        case SDLK_UP:
                            if(direction != "down")
                            {
                                soundWhenSwitch();
                                newDirection = "up";
                                ok = true;
                            }
                            break;
                        case SDLK_DOWN:
                            if(direction != "up")
                            {
                                soundWhenSwitch();
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
            initMap();
            renderFood();
            if(ateFood())
            {
                soundWhenEatFood();
                increaseSizeOfSnake();
                makeIndexFood();
                renderFood();
            }
            if(ok) move();
            SDL_Delay(60);
            renderSnake();
            graphics.presentScene();
        }
    }
};


#endif // _LIBGAME_H
