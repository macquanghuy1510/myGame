#ifndef _logicGame_
#define _logicGame_

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

struct Snake
{
    vector<SDL_Rect> node;
    string direction = "right";
    SDL_Rect food = {600, 150, SIZE, SIZE};
    double angle = 0;

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
    void renderFood(Graphics graphics, SDL_Texture* imgfood)
    {
        graphics.renderTexture(imgfood, food.x, food.y);
    }
    void render(Graphics graphics, SDL_Texture* imgdau, SDL_Texture* imgthan)
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

#endif // _logicGame_
