#ifndef _LIBGAME_H
#define _LIBGAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstring>
#include <fstream>
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
    int scores = 0;
    int stepX = 0;
    int stepY = 0;
    Graphics graphics;
    SDL_Texture* imgmap;
    SDL_Texture* imgdau;
    SDL_Texture* imgthan;
    SDL_Texture* imgfood;
    SDL_Texture* menu;
    SDL_Texture* rulegame;
    SDL_Texture* topscore;
    Mix_Chunk* eatsound;
    Mix_Chunk* gameoversound;
    Mix_Chunk* switchsound;
    Mix_Music* nhacnen;

    void loadAllTexture()
    {
        imgmap = graphics.loadTexture("map.png");
        imgdau = graphics.loadTexture("dau.png");
        imgthan = graphics.loadTexture("than.png");
        imgfood = graphics.loadTexture("foodpixel.png");
        menu = graphics.loadTexture("START.png");
        rulegame = graphics.loadTexture("RuleGame.png");
        topscore = graphics.loadTexture("TopScore.png");
        eatsound = graphics.loadSound("applebitesound.mp3");
        gameoversound = graphics.loadSound("gameoversound1.mp3");
        switchsound = graphics.loadSound("soundswitch.wav");
        nhacnen = graphics.loadMusic("backgroundmusic.mp3");
    }
    void initMap()
    {
        graphics.prepareScene(imgmap);
    }
    void initSnake()
    {
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
        graphics.renderTexture(imgfood, food.x, food.y);
    }
    void renderSnake()
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
    void renderRule()
    {
        graphics.prepareScene(rulegame);
        graphics.presentScene();
    }
    void renderTopScore()
    {
        graphics.prepareScene(topscore);
        TTF_Font* font = graphics.loadFont("Purisa-BoldOblique.ttf", 50);
        SDL_Color color = {59, 106, 167, 255};
        fstream myfile;
        myfile.open("data.txt", ios::in);
        int nums[3];
        for(int i = 0; i < 3; i++) myfile >> nums[i];
        myfile.close();
        int d = 0;
        for(int i = 0; i < 3; i++)
        {
            char tmp[] = "0";
            convertIntToChar(tmp, nums[i]);
            SDL_Texture* score = graphics.renderText(tmp, font, color);
            graphics.renderTexture(score, 380, 190 + d);
            d += 73;
        }
        graphics.presentScene();
        TTF_CloseFont(font);
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
    void convertIntToChar(char* tmp, int n)
    {
        if(!n)
        {
            *(tmp) = '0';
            *(tmp + 1) = '\0';
        }
        else
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
    }
    void renderScores()
    {
        char tmp1[] = "0";
        convertIntToChar(tmp1, scores);
        TTF_Font* font = graphics.loadFont("Purisa-BoldOblique.ttf", 30);
        SDL_Color color = {227, 180, 72, 255};
        SDL_Texture* score = graphics.renderText(tmp1, font, color);
        SDL_Texture* SCORES = graphics.renderText("Scores: ", font, color);
        graphics.renderTexture(SCORES, 0, -8);
        graphics.renderTexture(score, 145, -8);
        TTF_CloseFont(font);
        SDL_DestroyTexture(score);
        SDL_DestroyTexture(SCORES);
    }
    void soundWhenEatFood()
    {
        graphics.playChunk(eatsound);
    }
    void soundWhenGameOver()
    {
        graphics.playChunk(gameoversound);
        Mix_VolumeChunk(gameoversound, MIX_MAX_VOLUME / 3);
        SDL_Delay(4000);
    }
    void soundWhenSwitch()
    {
        graphics.playChunk(switchsound);
        Mix_VolumeChunk(switchsound, MIX_MAX_VOLUME / 5);
    }
    void soundWhenNewRecord()
    {
        SDL_Texture* congra = graphics.loadTexture("congratulations.png");
        Mix_Chunk* soundcongra = graphics.loadSound("subway-surfers-new-record.mp3");
        graphics.prepareScene(congra);
        graphics.presentScene();
        graphics.playChunk(soundcongra);
        SDL_Delay(6000);
        SDL_DestroyTexture(congra);
        Mix_FreeChunk(soundcongra);
    }
    void backgroundMusic()
    {
        graphics.playMusic(nhacnen);
        Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
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
    bool changeRecord()
    {
        bool check = false;
        fstream myfile;
        myfile.open("data.txt", ios::in | ios::out);
        int record[3] = {0};
        for(int i = 0; i < 3; i++)
        {
            myfile >> record[i];
        }
        if(scores > record[0])
        {
            record[2] = record[1];
            record[1] = record[0];
            record[0] = scores;
            check = true;
        }
        else if(scores > record[1] && scores != record[0])
        {
            record[2] = record[1];
            record[1] = scores;
            check= true;
        }
        else if(scores > record[2] && scores != record[1])
        {
            record[2] = scores;
            check = true;
        }
        for(int i : record) cout << i << ' ';
        cout << endl;
        myfile.close();
        myfile.open("data.txt", ios::out | ios::trunc);
        char c = ' ';
        for(int i = 0; i < 3; i++)
        {
            myfile << record[i];
            myfile << c;
        }
        myfile.close();
        return check;
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
        graphics.prepareScene(menu);
        graphics.presentScene();
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
        scores = 0;
    }
    void logicOfMove(SDL_Event& e, string& newDirection, bool& ok, bool& check)
    {
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
    }
    void playGame()
    {
        Mix_HaltMusic();
        initMap();
        renderFood();
        renderScores();
        initSnake();
        SDL_Event e;
        bool check = true;
        bool ok = false;
        while(check)
        {
            if(isGameOver())
            {
                soundWhenGameOver();
                if(changeRecord())
                {
                    soundWhenNewRecord();
                }
                reset();
                break;
            }
            string newDirection = direction;
            logicOfMove(e, newDirection, ok, check);
            initMap();
            renderFood();
            renderScores();
            if(ateFood())
            {
                scores++;
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
    void destroyAllTexture()
    {
        Mix_FreeMusic(nhacnen);
        Mix_FreeChunk(eatsound);
        Mix_FreeChunk(gameoversound);
        Mix_FreeChunk(switchsound);
        SDL_DestroyTexture(imgdau);
        SDL_DestroyTexture(imgthan);
        SDL_DestroyTexture(imgfood);
        SDL_DestroyTexture(imgmap);
        SDL_DestroyTexture(menu);
        SDL_DestroyTexture(rulegame);
        SDL_DestroyTexture(topscore);
    }
};


#endif // _LIBGAME_H
