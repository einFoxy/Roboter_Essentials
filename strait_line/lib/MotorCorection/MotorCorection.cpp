#include "MotorCorection.h"

#define MOTOR_MIN_SPEED 200

#define MAX_SLOW_FACTOR 0.95 //works

//funktion exponential funktion to rais slow factor to max
#define R_MOTOR_MAX_SPEED 977.988 //MAX_SLOW_FACTOR * 1023
#define BASE 1.0003


//#define exponentialFunktion(max, base, exponent) (max*(max/104)*(1- 1/pow(base, exponent))+OFFSET)
#define exponentialFunktion(max, base, exponent) (max*max/285*(1- 1/pow(base, exponent)))

Motor motor;

double pow(double base, int exponent){
    double result = base;
    for (int i = 0; i < exponent; i++)
        result *= base;

    return result;
}

void motorSpeed(const uint8_t chanal, uint32_t duty){

    duty = (duty > 1023)? 1023 : duty;

    if(duty < MOTOR_MIN_SPEED)
        duty = 0;
    else if(chanal == motor.motR_chanel)
        duty *= MAX_SLOW_FACTOR;

    else if(chanal == motor.motL_chanel)
        duty = exponentialFunktion(1023,BASE, duty);
    
    ledcWrite(chanal, duty);

}