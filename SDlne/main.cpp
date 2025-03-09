#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

void waitUntilKeyPressed();

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    //SDL_Rect hcn = {200, 200, 120, 80};
    //SDL_SetRenderDrawColor(graphics.renderer, 0, 200, 255, 255);
    //SDL_RenderFillRect(graphics.renderer, &hcn);
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
                cout << "Button left at: " << x << ' ' << y << endl;
            }
            else if(eventchuot.button.button == SDL_BUTTON_RIGHT)
            {
                cout << "Button right at: " << x << ' ' << y << endl;
            }
        }
        SDL_Delay(100);
    }
    waitUntilKeyPressed();
	SDL_DestroyTexture( question );
    question = NULL;
    TTF_CloseFont( font );
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
