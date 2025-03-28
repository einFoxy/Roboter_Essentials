#pragma once


class Speed{
protected:
    float v_liniar;
    float v_rotation;

public:
    Speed(): v_liniar(0),v_rotation(0){}
    Speed(float liniar, float rotation): v_liniar(liniar), v_rotation(rotation){}

    inline float getLinearSpeed(){return v_liniar;}
    inline float getRotationalSpeed(){return v_rotation;}

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
