#ifndef MOTOR
#define MOTOR

#include <Arduino.h>

#define MOTOR_RIGHT 1
#define MOTOR_LEFT  0

//motor direcitons
#define MOTOR_RIGHT_FORWARD 1
#define MOTOR_RIGHT_BACKWARDS 0
#define MOTOR_LEFT_FORWARDS 0
#define MOTOR_LEFT_BACKWARDS 1

//motor chanals
#define MOTOR_RIGHT_CHANAL 1
#define MOTOR_LEFT_CHANAL 0

class Motor{
protected: //vars
    static int
        speedRight_Pin,
        speedLeft_Pin,

        directionRight_Pin,
        directionLeft_Pin;
private:
    static bool isSetUp;

public:
    Motor(); //defalt setup

    Motor(int speedRight_Pin, int speedLeft_Pin,            // steup with change pins
          int directionRight_Pin, int directionLeft_Pin);

    Motor(uint32_t frequency, uint8_t resulutionBits); //setup with custom motor frequency & resulution

    Motor(int speedRight_Pin, int speedLeft_Pin,           //setup with custom pins, frequency & resulution  
          int direction_Right_Pin, int direction_Left_Pin,
          uint32_t frequency, uint8_t resulutionBits);


    void changeDirection(int direction, int motor);
    void changeSpeed(int speed, int motor);

};


#endif MOTOR