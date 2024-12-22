
#ifndef BATTERY_CHECK
#define BATTERY_CHECK

#include <FastLED.h>
#include <Arduino.h>


// Avalible funkions:
void setup_BatterCheck_and_LED();
void intitila_BatteryCheck();
void action_minVoltage();
void action_minOperatingVoltage();
void action_maxVoltage();
void display_Voltage();
void battery_check();
void setLeds(uint8_t r, uint8_t g, uint8_t b);


#endif