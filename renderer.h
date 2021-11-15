#pragma once
#include <SDL2/SDL.h>
#include "math.h"

class Renderer {
    
public:
    Renderer();
    bool Create();
    void Destroy();
    void ClearScreen();
    void DrawPoint(int xPos, int yPos, int r, int g, int b);
    SDL_Renderer* GetRenderer() { return mRenderer; }
    SDL_Point GetWindowSize() { return mWindowSize; }
    
    void MoveCam(SDL_Point movement);
    
protected:
    SDL_Point mWindowSize;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    
    SDL_Point mCameraPos;
};
