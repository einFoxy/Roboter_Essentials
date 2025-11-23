#include "impulsgeber.h"
#include <Arduino.h>
#include <log.h>

Impulsgeber impulsgeber;
volatile uint32_t Impulsgeber::ticksRight = 0;
volatile uint32_t Impulsgeber::ticksLeft = 0;

void Impulsgeber::begin(){

    pinMode(impulsgeber_pin::right, INPUT);
    pinMode(impulsgeber_pin::left, INPUT);

    attachInterrupt(digitalPinToInterrupt(27),isrRightWheel, RISING);
    attachInterrupt(digitalPinToInterrupt(14),isrLeftWheel, RISING);

}

void Impulsgeber::printStatus(){
    LOG("Right Impulsgeber: ");
    LOG(digitalRead(impulsgeber_pin::right));
    LOG(" - Left Impulsgeber: ");
    LOG(digitalRead(impulsgeber_pin::left));

    LOG("     Right Ticks: ");
    LOG(ticksRight);
    LOG(" - LeftTicks: ");
    LOG_LN(ticksLeft);

    

}

uint32_t Impulsgeber::getRightTicks(){
    return ticksRight;
}
uint32_t Impulsgeber::getLeftTicks(){
    return ticksLeft;
}

void IRAM_ATTR isrRightWheel(){
    Impulsgeber::ticksRight++;
}

void IRAM_ATTR isrLeftWheel(){
    Impulsgeber::ticksLeft++;
}
