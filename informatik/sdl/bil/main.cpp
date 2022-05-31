#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

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

    SDL_Rect cameraRect;
    cameraRect.w = windowW;
    cameraRect.h = windowH;
    cameraRect.x = cameraRect.y = 50;

    SDL_Texture *map;
    map = LoadTexture("track.png", mainRendere);
    SDL_Rect mapRect;
    SDL_QueryTexture(map, NULL, NULL, &mapRect.w, &mapRect.h);
    mapRect.x = mapRect.y = 0;

    CarClass car0;
    car0.carRect.w = 128;
    car0.carRect.h = 77;
    car0.carRect.x = 0; 
    car0.carRect.y = windowH / 2 - car0.carRect.h / 2;
    car0.carImg = LoadTexture("0.png", mainRendere);

    CarClass car1;
    car1.carRect.w = 128;
    car1.carRect.h = 77;
    car1.carRect.x = 0; 
    car1.carRect.y = windowH / 2 - car0.carRect.h / 2;
    car1.carImg = LoadTexture("1.png", mainRendere);

    SelfDriving self0;
    self0.carRect.w = 128;
    self0.carRect.h = 77;
    self0.carRect.x = windowW / 2 - self0.carRect.w / 2; 
    self0.carRect.y = windowH / 2 - self0.carRect.h / 2;
    self0.carImg = LoadTexture("2.png", mainRendere);
    self0.drivingSpeed = 200;
    self0.lineColor = { 255, 0, 0, 255 };

    SelfDriving self1;
    self1.carRect.w = 128;
    self1.carRect.h = 77;
    self1.carRect.x = windowW / 2 - self1.carRect.w / 2; 
    self1.carRect.y = windowH / 2 - self1.carRect.h / 2;
    self1.carImg = LoadTexture("3.png", mainRendere);
    self1.drivingSpeed = 200;
    self1.lineColor = { 0, 0, 255, 255 };

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
        //std::cout << self0.carRot << '\n';

        SDL_RenderClear(mainRendere);

        car0.drive(deltaTime, pi);
        car1.drive(deltaTime, pi);
        self0.selfDrive(car0, deltaTime, pi);
        self1.selfDrive(car1, deltaTime, pi);

        cameraRect.x = car0.carRect.x - windowW / 2;
        cameraRect.y = car0.carRect.y - windowH / 2;

        if(cameraRect.x < 0)
            cameraRect.x = 0;
        if(cameraRect.y < 0)
            cameraRect.y = 0;

        if(cameraRect.x + cameraRect.w >= mapRect.w)
            cameraRect.x = mapRect.w - windowW;
        if(cameraRect.y + cameraRect.h >= mapRect.h)
            cameraRect.y = mapRect.h - windowH;

        SDL_RenderCopy(mainRendere, map, &cameraRect, NULL);
        car0.draw(mainRendere, cameraRect);
        car1.draw(mainRendere, cameraRect);
        self0.draw(mainRendere, cameraRect, car0);
        self1.draw(mainRendere, cameraRect, car1);
        SDL_RenderPresent(mainRendere);
    }

    //cleanup
    SDL_DestroyWindow(mainWindow);
    SDL_DestroyRenderer(mainRendere);
    SDL_DestroyTexture(car0.carImg);
    SDL_DestroyTexture(car1.carImg);
    SDL_DestroyTexture(self0.carImg);
    SDL_DestroyTexture(map);

    mainWindow = nullptr;
    mainRendere = nullptr;
    car0.carImg = nullptr;
    car1.carImg = nullptr;
    self0.carImg = nullptr;
    map = nullptr;

    SDL_Quit();
    IMG_Quit();

    return 0;
}
