#include <SDL2/SDL.h>
#include <vector>
#include "mandelbrot.h"
#include "renderer.h"

Mandelbrot::Mandelbrot()
    :mRunning(true)
    ,mWorldSize((SDL_Point){1500, 1500})
    ,mMin(-2)
    ,mMax(2)
    ,mMaxIterations(500)
    ,mDivergence(16)
    ,mCamMoveSpeed(10.0f)
    ,mCamZoomSpeed(5.0f)
{
}

bool Mandelbrot::Initialize() {
    // create renderer
    mRenderer = new Renderer();
    if (!mRenderer->Create())
        return false;
    
    // set previous time
    mPrevTime = SDL_GetTicks();
    
    return true;
}

void Mandelbrot::RunLoop() {
    while (mRunning){
        ProcessUpdate();
        Update();
        GenerateOutput();
    }
}

void Mandelbrot::ProcessUpdate() {
    SDL_Point camMove;
    camMove.x = 0;
    camMove.y = 0;
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                mRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        mRunning = false;
                        break;
                    case SDLK_d:
                        camMove.x = mCamMoveSpeed;
                        break;
                    case SDLK_a:
                        camMove.x = -mCamMoveSpeed;
                        break;
                    case SDLK_w:
                        camMove.y = -mCamMoveSpeed;
                        break;
                    case SDLK_s:
                        camMove.y = mCamMoveSpeed;
                        break;
                    case SDLK_z:
                        mWorldSize.x += mCamZoomSpeed;
                        mWorldSize.y += mCamZoomSpeed;
                        break;
                    case SDLK_x:
                        mWorldSize.x -= mCamZoomSpeed;
                        mWorldSize.y -= mCamZoomSpeed;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    mRenderer->MoveCam(camMove);
}

void Mandelbrot::Update() {
    // Setting fps
    while ((int)SDL_GetTicks() < mPrevTime + 16) {}
    int currentTime = SDL_GetTicks();
    float deltaTime = (float)(currentTime - mPrevTime) / 1000;
    mPrevTime = currentTime;
    
    // clear screen
    mRenderer->ClearScreen();
    
    // iterate over every pixel
    for (int i = 0; i < mWorldSize.x; i++) {
        for (int j = 0; j < mWorldSize.y; j++) {
            // map i and j to min/max range so
            float initA = ((float)i / mWorldSize.x) * (mMax - mMin) + mMin;
            float initB = ((float)j / mWorldSize.y) * (mMax - mMin) + mMin;
            
            float a = initA;
            float b = initB;
            
            int n = 0;
            while (n < mMaxIterations) {
                // a^2 - b^2 + 2abi
                float newA = a * a - b * b;
                float newB = 2 * a * b;
                a = newA + initA;
                b = newB + initB;
                
                // (a + bi)^2 + c
                if (a + b> mDivergence)
                    break;
                
                n++;
            }
            
            float brightness = ((float)n / mMaxIterations) * 255.0f;
            if (n == mMaxIterations)
                brightness = 0.0f;
            mRenderer->DrawPoint(i, j, brightness, brightness, brightness);
        }
    }
    
    // render present
    SDL_RenderPresent(mRenderer->GetRenderer());
}

void Mandelbrot::GenerateOutput() {
}

void Mandelbrot::End() {
    mRenderer->Destroy();
}

