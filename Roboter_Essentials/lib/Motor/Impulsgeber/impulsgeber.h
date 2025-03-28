#pragma once

#include <Arduino.h>

#define TICKS_PER_ROTATION 20

void IRAM_ATTR isrRightWheel();
void IRAM_ATTR isrLeftWheel();

class Impulsgeber{

protected:
    enum impulsgeber_pin: int{
       left = 14,
       right = 27
    };

    static volatile unsigned long ticksRight;
    static volatile unsigned long ticksLeft;


public:
    void begin(); 
    void printStatus();
    unsigned long getRightTicks();
    unsigned long getLeftTicks();

protected:
    friend void IRAM_ATTR isrRightWheel();
    friend void IRAM_ATTR isrLeftWheel();

};

extern Impulsgeber impulsgeber;