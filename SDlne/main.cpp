#include <iostream>
#include <SDL_image.h>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Hello World!";

void logErrorAndExit(const char* msg, const char* error);
SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);
SDL_Renderer* createRenderer(SDL_Window* window);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void drawSomething(SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer);

int main(int argc, char* argv[])
{
    //Khởi tạo môi trường đồ họa
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);
    //Draw something
    SDL_SetRenderDrawColor(renderer, 0, 200, 255, 200);
    SDL_RenderDrawLine(renderer, 0, 0, 400, 300);
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
    //Thoát khỏi SDl
    quitSDL(window, renderer);
    return 0;
}

void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
{
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //full screen
    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
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

SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                     "Loading %s", filename);

	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Load texture %s", IMG_GetError());
      }

	return texture;
}


void drawSomething(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    SDL_SetRenderDrawColor(renderer, 100, 100, 200, 255);   // red
    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
    SDL_Rect filled_rect;
    filled_rect.x = SCREEN_WIDTH - 400;
    filled_rect.y = SCREEN_HEIGHT - 150;
    filled_rect.w = 320;
    filled_rect.h = 100;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // green
    SDL_RenderFillRect(renderer, &filled_rect);
}
