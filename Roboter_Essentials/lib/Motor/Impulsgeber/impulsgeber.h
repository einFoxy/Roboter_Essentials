#pragma once

#include <Arduino.h>

#define TICKS_PER_ROTATION 20

void IRAM_ATTR isrRightWheel();
void IRAM_ATTR isrLeftWheel();

class Impulsgeber{

protected:
    enum impulsgeber_pin: const int{
       left = 14,
       right = 27
    };

    static volatile uint32_t ticksRight;
    static volatile uint32_t ticksLeft;


public:
    void begin(); 
    static void printStatus();

    uint32_t getRightTicks();
    uint32_t getLeftTicks();

protected:
    friend void IRAM_ATTR isrRightWheel();
    friend void IRAM_ATTR isrLeftWheel();

};

extern Impulsgeber impulsgeber;