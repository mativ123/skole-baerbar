#include <iostream>
#include <string>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "include.h"

int main(int argc, char *argv[])
{
    const float degreesNorm { 1.1111 };
    const float pi { 3.14159f };

    int windowW { 960 };
    int windowH { 540 };
    
    int prevTime { 0 };
    int currentTime { 0 };
    float deltaTime { 0.0f };

    SDL_Window *mainWindow { nullptr };
    SDL_Renderer *mainRendere { nullptr };
    SDL_Init(SDL_INIT_VIDEO);
    int imgFlags { IMG_INIT_PNG | IMG_INIT_JPG };
    if(!(IMG_Init(imgFlags) & imgFlags))
        std::cout << "error: " << IMG_GetError() << '\n';

    mainWindow = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowW, windowH, SDL_WINDOW_SHOWN);
    mainRendere = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(mainRendere, 255, 255, 255, 255);

    SDL_Texture *carImg { nullptr };
    carImg = LoadTexture("0.png", mainRendere);

    CarClass car0;
    car0.carRect.w = 128;
    car0.carRect.h = 77;
    car0.carRect.x = 0; 
    car0.carRect.y = windowH / 2 - car0.carRect.h / 2;
    car0.carImg = LoadTexture("0.png", mainRendere);
    car0.carLength = 1.8f;
    car0.drivingSpeed = 250.0f;
    car0.drivingFor = false;
    car0.drivingRev = false;
    car0.carXspeed = 0.0f;
    car0.carYspeed = 0.0f;
    car0.carRot = 0.0f;
    car0.rotLeft = false;
    car0.rotRight = false;

    CarClass car1;
    car1.carRect.w = 128;
    car1.carRect.h = 77;
    car1.carRect.x = 0; 
    car1.carRect.y = windowH / 2 - car0.carRect.h / 2;
    car1.carImg = LoadTexture("1.png", mainRendere);
    car1.carLength = 1.8f;
    car1.drivingSpeed = 250.0f;
    car1.drivingFor = false;
    car1.drivingRev = false;
    car1.carXspeed = 0.0f;
    car1.carYspeed = 0.0f;
    car1.carRot = 0.0f;
    car1.rotLeft = false;

    SDL_Event ev;
    bool isRunning { true };

    while(isRunning)
    {
        prevTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f;

        while(SDL_PollEvent(&ev) != 0)
        {
            if(ev.type == SDL_QUIT)
            {
                isRunning = false;
            } else if(ev.type == SDL_KEYDOWN)
            {
                switch(ev.key.keysym.sym)
                {
                    case SDLK_w:
                        car0.drivingFor = true;
                        break;
                    case SDLK_s:
                        car0.drivingRev = true;
                        break;
                    case SDLK_a:
                        car0.rotLeft = true;
                        break;
                    case SDLK_d:
                        car0.rotRight = true;
                        break;
                    case SDLK_UP:
                        car1.drivingFor = true;
                        break;
                    case SDLK_DOWN:
                        car1.drivingRev = true;
                        break;
                    case SDLK_LEFT:
                        car1.rotLeft = true;
                        break;
                    case SDLK_RIGHT:
                        car1.rotRight = true;
                        break;
                }
            } else if(ev.type == SDL_KEYUP)
            {
                switch(ev.key.keysym.sym)
                {
                    case SDLK_w:
                        car0.drivingFor = false;
                        break;
                    case SDLK_s:
                        car0.drivingRev = false;
                        break;
                    case SDLK_a:
                        car0.rotLeft = false;
                        break;
                    case SDLK_d:
                        car0.rotRight = false;
                        break;
                    case SDLK_UP:
                        car1.drivingFor = false;
                        break;
                    case SDLK_DOWN:
                        car1.drivingRev = false;
                        break;
                    case SDLK_LEFT:
                        car1.rotLeft = false;
                        break;
                    case SDLK_RIGHT:
                        car1.rotRight = false;
                        break;
                }
                car0.carXspeed = 0;
                car1.carXspeed = 0;
            }
        }

        SDL_RenderClear(mainRendere);

        car0.drive(deltaTime, pi);
        car1.drive(deltaTime, pi);

        SDL_RenderCopyEx(mainRendere, car0.carImg, NULL, &car0.carRect, car0.carRot, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(mainRendere, car1.carImg, NULL, &car1.carRect, car1.carRot, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(mainRendere);
    }

    //cleanup
    SDL_DestroyWindow(mainWindow);
    SDL_DestroyRenderer(mainRendere);
    SDL_DestroyTexture(carImg);

    mainWindow = nullptr;
    mainRendere = nullptr;
    carImg = nullptr;

    SDL_Quit();
    IMG_Quit();

    return 0;
}
