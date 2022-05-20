
class CarClass
{
    public:
        SDL_Texture *carImg;

        SDL_Rect carRect;
        SDL_Rect drawingRect;
        float carLength { 1.8f };
        float drivingSpeed { 250.0f };
        bool drivingFor { false };
        bool drivingRev { false };
        float carXspeed { 0.0f };
        float carYspeed { 0.0f };
        float carRot { 0.0f };
        bool rotLeft { false };
        bool rotRight { false };

        void drive(float deltaTime, float pi)
        {
            if(drivingFor && drivingRev)
            {
                carXspeed = 0;
            } else if(drivingFor)
            {
                carXspeed = drivingSpeed * cos(carRot*pi/180);
                carYspeed = -(drivingSpeed * sin(carRot*pi/180));
            } else if(drivingRev)
            {
                carXspeed = -(drivingSpeed * cos(carRot*pi/180));
                carYspeed = drivingSpeed * sin(carRot*pi/180);
            } else
            {
                carXspeed = 0;
                carYspeed = 0;
            }

            if(rotLeft && rotRight)
            {
                carRot += 0;
            } else if(!drivingFor && !drivingRev)
            {
                carRot += 0;
            } else if(rotLeft && drivingRev)
            {
                carRot += 50 * deltaTime;
            } else if(rotRight && drivingRev)
            {
                carRot -= 50 * deltaTime;
            } else if(rotLeft)
            {
                carRot -= 50 * deltaTime;
            } else if(rotRight)
            {
                carRot += 50 * deltaTime;
            } else
            {
                carRot += 0;
            }

            if(carRot > 360)
            {
                carRot = 0;
            } else if(carRot < 0)
            {
                carRot = 360;
            }
            if(SDL_GetP)

            carRect.y += carYspeed * deltaTime;
            carRect.x -= carXspeed * deltaTime;
        }

        void draw(SDL_Renderer *mainRendere, SDL_Rect cameraRect)
        {
            drawingRect = { carRect.x - cameraRect.x, carRect.y - cameraRect.y, carRect.w, carRect.h };
            SDL_RenderCopyEx(mainRendere, carImg, NULL, &drawingRect, carRot, NULL, SDL_FLIP_NONE);
        }
};

 class SelfDriving
 {
     public:
        SDL_Texture *carImg;

        SDL_Rect carRect;
        SDL_Rect drawingRect;
        ColorRGBA lineColor;
        float carLength { 1.8f };
        float drivingSpeed { 250.0f };
        bool drivingFor { false };
        bool drivingRev { false };
        float carXspeed { 0.0f };
        float carYspeed { 0.0f };
        float carRot { 0.0f };
        bool rotLeft { false };
        bool rotRight { false };

        void selfDrive(CarClass target, float deltaTime,float pi)
        {
            float tempX { static_cast<float>(target.carRect.x - carRect.x) };
            float tempY { static_cast<float>(target.carRect.y - carRect.y) };
            carRot = atan2(tempY, tempX) * (180/pi);
            if(carRot < 0)
            {
                carRot = 360 - (-carRot);
            }
            carRot += 180;

            carXspeed = drivingSpeed * cos(carRot*pi/180);
            carYspeed = -(drivingSpeed * sin(carRot*pi/180));

            carRect.y += carYspeed * deltaTime;
            carRect.x -= carXspeed * deltaTime;
        }

        void draw(SDL_Renderer *mainRendere, SDL_Rect cameraRect, CarClass target)
        {
            drawingRect = { carRect.x - cameraRect.x, carRect.y - cameraRect.y, carRect.w, carRect.h };
            SDL_RenderCopyEx(mainRendere, carImg, NULL, &drawingRect, carRot, NULL, SDL_FLIP_NONE);
            thickLineRGBA(mainRendere, target.drawingRect.x + target.carRect.w / 2, target.drawingRect.y + target.carRect.h / 2, drawingRect.x + carRect.w / 2, drawingRect.y + carRect.h / 2, 5, lineColor.r, lineColor.g, lineColor.b, lineColor.a);
        }
 };
