class CarClass
{
    public:
        SDL_Texture *carImg;

        SDL_Rect carRect;
        float carLength;
        float drivingSpeed;
        bool drivingFor;
        bool drivingRev;
        float carXspeed;
        float carYspeed;
        float carRot;
        bool rotLeft;
        bool rotRight;

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

            carRect.y += carYspeed * deltaTime;
            carRect.x -= carXspeed * deltaTime;
        }
};

 class SelfDriving
 {
     public:
         SDL_Texture *carImg;

         SDL_Rect carRect;
         float carLength;
         float drivingSpeed;
         bool drivingFor;
         bool drivingRev;
         float carXspeed;
         float carYspeed;
         float carRot;
         bool rotLeft;
         bool rotRight;

         void selfDrive(CarClass target,float deltaTime,float pi)
         {
            float tempX { static_cast<float>(target.carRect.x - carRect.y) };
            float tempY { static_cast<float>(target.carRect.y - carRect.y) };
            carRot = atan2(tempY, tempX) * (180/pi);
            carRot += 180;

            carXspeed = drivingSpeed * cos(carRot*pi/180);
            carYspeed = -(drivingSpeed * sin(carRot*pi/180));

            carRect.y += carYspeed * deltaTime;
            carRect.x -= carXspeed * deltaTime;
         }
 };
