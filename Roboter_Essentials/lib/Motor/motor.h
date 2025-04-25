#ifndef MOTOR
#define MOTOR

#include <Arduino.h>
#include "Impulsgeber/impulsgeber.h"
#include "datatypes.h"

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

#define PWM_BIT_RESULTUION 10
#define MAX_SPEED_CMD 1024



class Motor: public Impulsgeber{
public:
    float wheelBase = 0.156; //m - distance between the wheels 
    float wheelRadius = 0.0325; //m

    float ticksPerRevolution = 20;
    unsigned long maxTicksPerRevolution = 7;
    float maxLiniarSpeed;
    float maxOmegaSpeed;


protected: //vars
    static int
        speedRight_Pin,
        speedLeft_Pin,

        directionRight_Pin,
        directionLeft_Pin;



    PIDController liniar_PID;
    PIDController angular_PID;
    //PIDController heading_PID;


    float distaceDriven = 0;
    float angularDriven = 0;

    
        
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

    float calculateVelocity(const unsigned long rightTicks, const unsigned long leftTicks, const float dt_seconds);
    float calculateAngle(const unsigned long rightTicks, const unsigned long leftTicks, const float dt_seconds);
    void calculateDistanceDriven(const unsigned long rightTicks, const unsigned long leftTicks, const float dt_seconds);
    void calculateAngleDriven(const unsigned long rightTicks, const unsigned long leftTicks, const float dt_seconds);

    float calculateMaxVelocity();
    float calculateMaxOmega();

    inline float getDistance(){return distaceDriven;}
    inline float getAngle(){return angularDriven;}

    void setLiniarPID(float Kp,float Ki,float Kd);
    void setAngularPID(float Kp,float Ki,float Kd);
    //void headingPID(float Kp,float Ki,float Kd);

    void changeDirection(int direction, int motor);
    void changeSpeed(int speed, int motor);

    void setSpeed(const Speed& speed);
    void setMotorSpeeds(const float final_v_cmd, const float final_omega_cmd);

    void reset();


};



#endif