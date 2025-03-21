#include "impulsgeber.h"
#include <Arduino.h>

Impulsgeber impulsgeber;
volatile int Impulsgeber::ticksRight = 0;
volatile int Impulsgeber::ticksLeft = 0;

void Impulsgeber::begin(){

    pinMode(impulsgeber_pin::right, INPUT);
    pinMode(impulsgeber_pin::left, INPUT);

    attachInterrupt(digitalPinToInterrupt(27),isrRightWheel, RISING);
    attachInterrupt(digitalPinToInterrupt(14),isrLeftWheel, RISING);

}

void Impulsgeber::printStatus(){
    Serial.print("Right Impulsgeber: ");
    Serial.print(digitalRead(impulsgeber_pin::right));
    Serial.print(" - Left Impulsgeber: ");
    Serial.print(digitalRead(impulsgeber_pin::left));

    Serial.print("     Right Ticks: ");
    Serial.print(ticksRight);
    Serial.print(" - LeftTicks: ");
    Serial.println(ticksLeft);

    

}

int Impulsgeber::getRightTicks(){
    return ticksRight;
}
int Impulsgeber::getLeftTicks(){
    return ticksLeft;
}

void IRAM_ATTR isrRightWheel(){
    Impulsgeber::ticksRight++;
}

void IRAM_ATTR isrLeftWheel(){
    Impulsgeber::ticksLeft++;
}
