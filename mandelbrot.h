#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "renderer.h"

class Mandelbrot {
    
public:
    Mandelbrot();
    bool Initialize();
    void RunLoop();
    void ProcessUpdate();
    void Update();
    void GenerateOutput();
    void End();
    
protected:
    bool mRunning;
    int mPrevTime;
    class Renderer* mRenderer;
    
    SDL_Point mWorldSize;
    
    int mMin;
    int mMax;
    
    int mMaxIterations;
    int mDivergence;
    
    float mCamMoveSpeed;
    float mCamZoomSpeed;
};

