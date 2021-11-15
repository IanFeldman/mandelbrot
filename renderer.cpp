#include "renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "math.h"

Renderer::Renderer()
    :mWindowSize((SDL_Point){0, 0})
    ,mCameraPos((SDL_Point){0, 0})
{
}

bool Renderer::Create() {
    // init video
    int initialized = SDL_Init(SDL_INIT_VIDEO);
    if (initialized != 0) {
        return false;
    }
    // create window
    mWindow = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowSize.x, mWindowSize.y, SDL_WINDOW_FULLSCREEN_DESKTOP); // set fullscreen
    if (mWindow == NULL) {
        return false;
    }
    // get resolution of fullscreen window
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    mWindowSize.x = DM.w;
    mWindowSize.y = DM.h;
    
    // create renderer
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == NULL) {
        return false;
    }
    
    return true;
}

void Renderer::Destroy() {
    //Destroy window
    SDL_DestroyWindow(mWindow);
    //Quit SDL subsystems
    SDL_Quit();
}

void Renderer::ClearScreen() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);
}

void Renderer::DrawPoint(int xPos, int yPos, int r, int g, int b) {
    SDL_SetRenderDrawColor(mRenderer, r, g, b, 255);
    SDL_RenderDrawPoint(mRenderer, xPos - mCameraPos.x, yPos - mCameraPos.y);
}

void Renderer::MoveCam(SDL_Point movement) {
    mCameraPos.x += movement.x;
    mCameraPos.y += movement.y;
}
