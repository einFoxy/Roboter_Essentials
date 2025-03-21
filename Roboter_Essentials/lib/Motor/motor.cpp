#include "motor.h"

        bool Motor::isSetUp = 0;
        int Motor::speedRight_Pin = 2;
        int Motor::speedLeft_Pin = 32;
        int Motor::directionRight_Pin = 15;
        int Motor::directionLeft_Pin = 33;

Motor::Motor():v_max(std::pow(2,10)){
    if(!isSetUp){
    isSetUp = 1;
     pinMode(directionRight_Pin, OUTPUT);
     pinMode(directionLeft_Pin, OUTPUT);

     //Richtung der Motoren Bestimmen
     digitalWrite(directionRight_Pin, MOTOR_RIGHT_CHANAL);
     digitalWrite(directionLeft_Pin, MOTOR_LEFT_CHANAL);

    //Setup von PWM Chanals 
     ledcSetup(MOTOR_RIGHT_CHANAL, 16000,10);
     ledcSetup(MOTOR_LEFT_CHANAL, 16000,10);
     ledcAttachPin(speedRight_Pin, MOTOR_RIGHT_CHANAL);
     ledcAttachPin(speedLeft_Pin,MOTOR_LEFT_CHANAL);
        //PWM Chanals == 0
     ledcWrite(MOTOR_RIGHT_CHANAL, 0);
     ledcWrite(MOTOR_LEFT_CHANAL, 0);
    }
}


Motor::Motor(int motor_speedRight_Pin, int motor_speedLeft_Pin,
             int motordirectionRight_Pin, int motordirectionLeft_Pin):v_max(std::pow(2,10))
{
    if(!isSetUp){
    isSetUp = 1;
    speedRight_Pin = motor_speedRight_Pin;
    speedLeft_Pin = motor_speedLeft_Pin;
    directionRight_Pin = motordirectionRight_Pin;
    directionLeft_Pin = motordirectionLeft_Pin;

     pinMode(directionRight_Pin, OUTPUT);
     pinMode(directionLeft_Pin, OUTPUT);

     //Richtung der Motoren Bestimmen
     digitalWrite(directionRight_Pin, MOTOR_RIGHT_CHANAL);
     digitalWrite(directionLeft_Pin, MOTOR_LEFT_CHANAL);

    //Setup von PWM Chanals 
     ledcSetup(MOTOR_RIGHT_CHANAL, 16000,10);
     ledcSetup(MOTOR_LEFT_CHANAL, 16000,10);
     ledcAttachPin(speedRight_Pin, MOTOR_RIGHT_CHANAL);
     ledcAttachPin(speedLeft_Pin,MOTOR_LEFT_CHANAL);
        //PWM Chanals == 0
     ledcWrite(MOTOR_RIGHT_CHANAL, 0);
     ledcWrite(MOTOR_LEFT_CHANAL, 0);
    }
}

Motor::Motor(uint32_t frequency, uint8_t resulutionBits):v_max(std::pow(2,resulutionBits)){
    if(!isSetUp){
    isSetUp = 1;
     pinMode(directionRight_Pin, OUTPUT);
     pinMode(directionLeft_Pin, OUTPUT);

     //Richtung der Motoren Bestimmen
     digitalWrite(directionRight_Pin, MOTOR_RIGHT_CHANAL);
     digitalWrite(directionLeft_Pin, MOTOR_LEFT_CHANAL);

    //Setup von PWM Chanals 
     ledcSetup(MOTOR_RIGHT_CHANAL, frequency, resulutionBits);
     ledcSetup(MOTOR_RIGHT_CHANAL, frequency, resulutionBits);
     ledcAttachPin(speedRight_Pin, MOTOR_RIGHT_CHANAL);
     ledcAttachPin(speedLeft_Pin,MOTOR_LEFT_CHANAL);
        //PWM Chanals == 0
     ledcWrite(MOTOR_RIGHT_CHANAL, 0);
     ledcWrite(MOTOR_LEFT_CHANAL, 0);
    }
} 

Motor::Motor(int motor_speedRight_Pin, int motor_speedLeft_Pin,
             int motordirectionRight_Pin, int motordirectionLeft_Pin,
             uint32_t frequency, uint8_t resulutionBits):v_max(std::pow(2,resulutionBits))
{
    if(!isSetUp){
    isSetUp = 1;
    speedRight_Pin = motor_speedRight_Pin;
    speedLeft_Pin = motor_speedLeft_Pin;
    directionRight_Pin = motordirectionRight_Pin;
    directionLeft_Pin = motordirectionLeft_Pin;

     pinMode(directionRight_Pin, OUTPUT);
     pinMode(directionLeft_Pin, OUTPUT);

     //Richtung der Motoren Bestimmen
     digitalWrite(directionRight_Pin, MOTOR_RIGHT_CHANAL);
     digitalWrite(directionLeft_Pin, MOTOR_LEFT_CHANAL);

    //Setup von PWM Chanals 
     ledcSetup(MOTOR_RIGHT_CHANAL, frequency, resulutionBits);
     ledcSetup(MOTOR_LEFT_CHANAL,  frequency, resulutionBits);
     ledcAttachPin(speedRight_Pin, MOTOR_RIGHT_CHANAL);
     ledcAttachPin(speedLeft_Pin,MOTOR_LEFT_CHANAL);
        //PWM Chanals == 0
     ledcWrite(MOTOR_RIGHT_CHANAL, 0);
     ledcWrite(MOTOR_LEFT_CHANAL, 0);
    }
}


void Motor::changeDirection(int direction, int motor)
{
   if(motor == MOTOR_RIGHT)
        digitalWrite(directionRight_Pin, direction);
    else //motor == MOTOR_LEFT
        digitalWrite(directionLeft_Pin, direction);

}

void Motor::changeSpeed(int speed, int motor){
   if(motor == MOTOR_RIGHT)
        ledcWrite(MOTOR_RIGHT_CHANAL, speed); 
    else //motor == MOTOR_LEFT
        ledcWrite(MOTOR_LEFT_CHANAL, speed); 
}