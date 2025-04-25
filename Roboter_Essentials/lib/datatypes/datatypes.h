#pragma once


class Speed{
protected:
    float speed;
    float omega;

public:
    Speed(float liniar, float rotation): speed(liniar), omega(rotation){}

    inline float getLinearSpeed()const {return speed;}
    inline float getOmega()const {return omega;}

};

class PIDController
    {
    public:
        PIDController();
        PIDController(const float Kp, const float Ki, const float Kd); 

        void setParameters(const float Kp, const float Ki, const float Kd);

        void reset();

        float calculate(const float error);

    private:
        float Kp, Ki, Kd;

        double integral;
        double previous_error;
        unsigned long last_time;
    };

    int clampInt(const int value, const int min, const int max);