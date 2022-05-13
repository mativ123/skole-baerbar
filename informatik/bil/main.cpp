#include <iostream>
#include <string>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture *LoadTexture(std::string filePath, SDL_Renderer *renderTarget)
{
    SDL_Texture *texture { nullptr };
    SDL_Surface *surface { IMG_Load(filePath.c_str()) };
    if(surface == NULL)
    {
        std::cout << "ERROR: " << SDL_GetError() << '\n';
    } else
    {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
    }

    SDL_FreeSurface(surface);

    return texture;
}

int main(int argc, char *argv[])
{
    const float degreesNorm { 0.278 };

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
    carImg = LoadTexture("bil.jpg", mainRendere);

    SDL_Rect carRect;
    carRect.w = carRect.h = 255;
    carRect.x = 0; 
    carRect.y = windowH / 2 - carRect.h / 2;
    float carLength { 1.8f };
    float drivingSpeed { 5.0f };
    bool drivingFor { false };
    bool drivingRev { false };
    float carXspeed { 0.0f };
    float carYspeed { 0.0f };
    float carRot { 0.0f };
    bool rotLeft { false };
    bool rotRight { false };

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
                        drivingFor = true;
                        break;
                    case SDLK_s:
                        drivingRev = true;
                        break;
                    case SDLK_a:
                        rotLeft = true;
                        break;
                    case SDLK_d:
                        rotRight = true;
                        break;
                }
            } else if(ev.type == SDL_KEYUP)
            {
                switch(ev.key.keysym.sym)
                {
                    case SDLK_w:
                        drivingFor = false;
                        break;
                    case SDLK_s:
                        drivingRev = false;
                        break;
                    case SDLK_a:
                        rotLeft = false;
                        break;
                    case SDLK_d:
                        rotRight = false;
                        break;
                }
                carXspeed = 0;
            }
        }

        SDL_RenderClear(mainRendere);

        if(drivingFor && drivingRev)
        {
            carXspeed = 0;
        }else if(drivingFor)
        {
            carXspeed = -drivingSpeed - (drivingSpeed * ((carRot * degreesNorm) / 100));
        } else if(drivingRev)
        {
            carXspeed = drivingSpeed;
        } else
        {
            carXspeed = 0;
        }

        if(rotLeft && rotRight)
        {
            carRot += 0;
        } else if(rotLeft)
        {
            carRot -= 25 * deltaTime;
        } else if(rotRight)
        {
            carRot += 25 * deltaTime;
        } else
        {
            carRot += 0;
        }

        carRect.y += carYspeed * deltaTime;
        carRect.x += carXspeed;

        SDL_RenderCopyEx(mainRendere, carImg, NULL, &carRect, carRot, NULL, SDL_FLIP_NONE);
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
