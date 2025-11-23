#include "motor.h"
#include "log.h"

        bool Motor::isSetUp = 0;
        int Motor::speedRight_Pin = 2;
        int Motor::speedLeft_Pin = 32;
        int Motor::directionRight_Pin = 15;
        int Motor::directionLeft_Pin = 33;

Motor::Motor(){
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

        liniar_PID.setParameters(0.1,0,0);
        angular_PID.setParameters(1,0.01,0.01);

        maxLiniarSpeed = calculateMaxVelocity();
        maxOmegaSpeed = calculateMaxOmega();

}


Motor::Motor(int motor_speedRight_Pin, int motor_speedLeft_Pin,
             int motordirectionRight_Pin, int motordirectionLeft_Pin)
{
    if (!isSetUp)
    {
        isSetUp = 1;
        speedRight_Pin = motor_speedRight_Pin;
        speedLeft_Pin = motor_speedLeft_Pin;
        directionRight_Pin = motordirectionRight_Pin;
        directionLeft_Pin = motordirectionLeft_Pin;

        pinMode(directionRight_Pin, OUTPUT);
        pinMode(directionLeft_Pin, OUTPUT);

        // Richtung der Motoren Bestimmen
        digitalWrite(directionRight_Pin, MOTOR_RIGHT_CHANAL);
        digitalWrite(directionLeft_Pin, MOTOR_LEFT_CHANAL);

        // Setup von PWM Chanals
        ledcSetup(MOTOR_RIGHT_CHANAL, 16000, 10);
        ledcSetup(MOTOR_LEFT_CHANAL, 16000, 10);
        ledcAttachPin(speedRight_Pin, MOTOR_RIGHT_CHANAL);
        ledcAttachPin(speedLeft_Pin, MOTOR_LEFT_CHANAL);
        // PWM Chanals == 0
        ledcWrite(MOTOR_RIGHT_CHANAL, 0);
        ledcWrite(MOTOR_LEFT_CHANAL, 0);

        maxLiniarSpeed = calculateMaxVelocity();
        maxOmegaSpeed = calculateMaxOmega();

        liniar_PID.setParameters(1, 0, 0);
        angular_PID.setParameters(5, 0, 0);
    }
}

Motor::Motor(uint32_t frequency, uint8_t resulutionBits)
{
    if (!isSetUp)
    {
        isSetUp = 1;
        pinMode(directionRight_Pin, OUTPUT);
        pinMode(directionLeft_Pin, OUTPUT);

        // Richtung der Motoren Bestimmen
        digitalWrite(directionRight_Pin, MOTOR_RIGHT_CHANAL);
        digitalWrite(directionLeft_Pin, MOTOR_LEFT_CHANAL);

        // Setup von PWM Chanals
        ledcSetup(MOTOR_RIGHT_CHANAL, frequency, resulutionBits);
        ledcSetup(MOTOR_RIGHT_CHANAL, frequency, resulutionBits);
        ledcAttachPin(speedRight_Pin, MOTOR_RIGHT_CHANAL);
        ledcAttachPin(speedLeft_Pin, MOTOR_LEFT_CHANAL);
        // PWM Chanals == 0
        ledcWrite(MOTOR_RIGHT_CHANAL, 0);
        ledcWrite(MOTOR_LEFT_CHANAL, 0);

        maxLiniarSpeed = calculateMaxVelocity();
        maxOmegaSpeed = calculateMaxOmega();

        liniar_PID.setParameters(1, 0, 0);
        angular_PID.setParameters(5, 0, 0);
    }
} 

Motor::Motor(int motor_speedRight_Pin, int motor_speedLeft_Pin,
             int motordirectionRight_Pin, int motordirectionLeft_Pin,
             uint32_t frequency, uint8_t resulutionBits)
{
    if (!isSetUp)
    {
        isSetUp = 1;
        speedRight_Pin = motor_speedRight_Pin;
        speedLeft_Pin = motor_speedLeft_Pin;
        directionRight_Pin = motordirectionRight_Pin;
        directionLeft_Pin = motordirectionLeft_Pin;

        pinMode(directionRight_Pin, OUTPUT);
        pinMode(directionLeft_Pin, OUTPUT);

        // Richtung der Motoren Bestimmen
        digitalWrite(directionRight_Pin, MOTOR_RIGHT_CHANAL);
        digitalWrite(directionLeft_Pin, MOTOR_LEFT_CHANAL);

        // Setup von PWM Chanals
        ledcSetup(MOTOR_RIGHT_CHANAL, frequency, resulutionBits);
        ledcSetup(MOTOR_LEFT_CHANAL, frequency, resulutionBits);
        ledcAttachPin(speedRight_Pin, MOTOR_RIGHT_CHANAL);
        ledcAttachPin(speedLeft_Pin, MOTOR_LEFT_CHANAL);
        // PWM Chanals == 0
        ledcWrite(MOTOR_RIGHT_CHANAL, 0);
        ledcWrite(MOTOR_LEFT_CHANAL, 0);

        maxLiniarSpeed = calculateMaxVelocity();
        maxOmegaSpeed = calculateMaxOmega();

        liniar_PID.setParameters(1, 0, 0);
        angular_PID.setParameters(5, 0, 0);
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
   {
        if(speed > 0) changeDirection(MOTOR_RIGHT_FORWARD, MOTOR_RIGHT);
        else changeDirection(MOTOR_RIGHT_BACKWARDS, MOTOR_RIGHT);
        ledcWrite(MOTOR_RIGHT_CHANAL, speed); 
   }
    else //motor == MOTOR_LEFT
    {
        if(speed > 0) changeDirection(MOTOR_LEFT_FORWARDS, MOTOR_LEFT);
        else changeDirection(MOTOR_LEFT_BACKWARDS, MOTOR_LEFT);
        ledcWrite(MOTOR_LEFT_CHANAL, speed); 
    }
}


void Motor::setLiniarPID(float Kp,float Ki,float Kd){
    liniar_PID.setParameters(Kp,Ki, Kd);
}
void Motor::setAngularPID(float Kp,float Ki,float Kd){
    
    angular_PID.setParameters(Kp,Ki, Kd);
}

void Motor::setSpeed(const Speed& speed){
//meachure time
static unsigned long  tlast = 0;
const auto tnow = millis();

const float dt_seconds = (float)(tnow - tlast)/1000.0f;

//meashure distance / rotation change
const uint32_t newRightTicks = getRightTicks();
const uint32_t newLeftTicks  =  getLeftTicks();
static uint32_t lastRightTicks = 0;
static uint32_t lastLeftTicks  = 0;

const uint32_t deltaRightTicks = newRightTicks - lastRightTicks;
const uint32_t deltaLeftTicks  = newLeftTicks  - lastLeftTicks;

LOG("right ticks: ");
LOG(deltaRightTicks);
LOG("  left ticks: ");
LOG_LN(deltaLeftTicks);
LOG("  dt: ");
LOG_LN(dt_seconds);


const auto v_meashured = calculateVelocity(deltaRightTicks, deltaLeftTicks, dt_seconds);
const auto omega_meashured = calculateAngle(deltaRightTicks, deltaLeftTicks, dt_seconds);
LOG("v_measured: ");
LOG(v_meashured);
LOG("  omega mesured. ");
LOG_LN(omega_meashured);
calculateDistanceDriven(deltaRightTicks, deltaLeftTicks, dt_seconds);
calculateAngleDriven(deltaRightTicks, deltaLeftTicks, dt_seconds);

//calculate error
const float liniar_error  = speed.getLinearSpeed() * maxLiniarSpeed - v_meashured;
const float angulareError = speed.getOmega() * maxOmegaSpeed - omega_meashured;

LOG("maxLiniarSpeed: ");
LOG(maxLiniarSpeed);
LOG("  maxOmegaSpeed: ");
LOG_LN(maxOmegaSpeed);

LOG("liniar error: ");
LOG(liniar_error);
LOG("  angulare error: ");
LOG_LN(angulareError);

const float v_correction = liniar_PID.calculate(liniar_error);
const float omega_correction= angular_PID.calculate(angulareError);

const auto finalVelocityCMD = speed.getLinearSpeed() * maxLiniarSpeed + v_correction;
const auto finalOmegaCMD = speed.getOmega() * maxOmegaSpeed + omega_correction;

LOG("final velocity: ");
LOG(finalVelocityCMD);
LOG("  fianl omega: ");
LOG_LN(finalOmegaCMD);

setMotorSpeeds(finalVelocityCMD, finalOmegaCMD);


lastRightTicks = newRightTicks;
lastLeftTicks  = newLeftTicks;
tlast = tnow;
    

}

void Motor::setMotorSpeeds(const float final_v_cmd, const float final_omega_cmd)
{
    const float leftMotorSpeed_mps = final_v_cmd - final_omega_cmd * wheelBase / 2.0f;
    const float rightMotorSpeed_mps = final_v_cmd + final_omega_cmd * wheelBase / 2.0f;

    LOG("motor commnad (mps): ");
    LOG(leftMotorSpeed_mps);
    LOG("  ");
    LOG_LN(rightMotorSpeed_mps);

    const float leftMotorCmd_ticks = leftMotorSpeed_mps / (2.0f * M_PI * wheelRadius) * ticksPerRevolution;
    const float rightMotorCmd_ticks = rightMotorSpeed_mps / (2.0f * M_PI * wheelRadius) * ticksPerRevolution;

    
    const int leftMotorCmd =  leftMotorCmd_ticks  / maxTicksPerSecond * MAX_SPEED_CMD;
    const int rightMotorCmd = rightMotorCmd_ticks / maxTicksPerSecond * MAX_SPEED_CMD;

    LOG("final motor commnad: ");
    LOG(leftMotorCmd);
    LOG("  ");
    LOG_LN(rightMotorCmd);

    const int leftMotorSpeed = clampInt(leftMotorCmd, -MAX_SPEED_CMD, MAX_SPEED_CMD);
    const int rightMotorSpeed = clampInt(rightMotorCmd, -MAX_SPEED_CMD, MAX_SPEED_CMD);
    LOG("final motor commnad (clamped): ");
    LOG(leftMotorSpeed);
    LOG("  ");
    LOG_LN(rightMotorSpeed);

    changeSpeed(leftMotorSpeed, MOTOR_LEFT);
    changeSpeed(rightMotorSpeed, MOTOR_RIGHT);
}

float Motor::calculateVelocity(const uint32_t rightTicks,const uint32_t leftTicks, const float dt_seconds){
//calculate rotation
const float rightRotations = rightTicks/(float) ticksPerRevolution;
const float leftRotations = leftTicks/(float) ticksPerRevolution;

//calculate distance
const float rightDistance = 2.0f * M_PI * wheelRadius * rightRotations;
const float leftDistance = 2.0f * M_PI * wheelRadius * leftRotations;

//calculate velocity
const float rightVelocity = rightDistance/dt_seconds;
const float leftVelocity  = leftDistance/ dt_seconds;


return (rightVelocity + leftVelocity)/2.0f;
}

float Motor::calculateAngle(const uint32_t rightTicks, const uint32_t leftTicks, const float dt_seconds){
//calculate rotation
const float rightRotations = rightTicks/ticksPerRevolution;
const float leftRotations = leftTicks/ticksPerRevolution;

//calculate distance
const float rightDistance = 2 * M_PI * wheelRadius * rightRotations;
const float leftDistance = 2 * M_PI * wheelRadius * leftRotations;

//calculate velocity
const float rightVelocity = rightDistance/dt_seconds;
const float leftVelocity = leftDistance/dt_seconds;

return (rightVelocity - leftVelocity)/wheelBase;
}


void Motor::calculateAngleDriven(const uint32_t rightTicks,const uint32_t leftTicks, const float dt_seconds)
{
//calculate rotation
const float rightRotations = rightTicks/ticksPerRevolution;
const float leftRotations = leftTicks/ticksPerRevolution;

//calculate distance
const float rightDistance = 2 * M_PI * wheelRadius * rightRotations;
const float leftDistance = 2 * M_PI * wheelRadius * leftRotations;

angularDriven += (rightDistance + leftDistance)/2.0f;

}

void Motor::calculateDistanceDriven(const uint32_t rightTicks,const uint32_t leftTicks, const float dt_seconds)
{
//calculate rotation
const float rightRotations = rightTicks/ticksPerRevolution;
const float leftRotations = leftTicks/ticksPerRevolution;

//calculate distance
const float rightDistance = 2 * M_PI * wheelRadius * rightRotations;
const float leftDistance = 2 * M_PI * wheelRadius * leftRotations;

angularDriven += (rightDistance + leftDistance)/2.0f;

}


void Motor::reset(){
    liniar_PID.reset();
    angular_PID.reset();
    
    distaceDriven = 0;
    angularDriven = 0;
}

float Motor::calculateMaxVelocity()
{
    const auto maxRotations = (float) maxTicksPerSecond/ticksPerRevolution;
    const auto maxVelocity = 2.0f * M_PI * wheelRadius * maxRotations;

    return maxVelocity;
}
float Motor::calculateMaxOmega()
{
    const auto maxRotationsPerSeconds = (float) maxTicksPerSecond/ticksPerRevolution;
    const auto maxVelocityPerWheel = 2.0f * M_PI * wheelRadius * maxRotationsPerSeconds;

    return 2*maxVelocityPerWheel/wheelBase;
}