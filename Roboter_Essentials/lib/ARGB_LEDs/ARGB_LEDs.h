#ifndef ON_BOARD_LEDS
#define ON_BOARD_LEDS

#include <Arduino.h>
#include <FastLED.h>
#include "../Battery_Management/Battery_Management.h"

#define NUMBER_OF_LEDS 4

#define DATA_PIN 23
#define CLOCK_PIN 18

class OnBoardLeds{
protected:
    static CRGB leds[NUMBER_OF_LEDS];

private:
    static bool isSetUp;
    static bool ledsInUse;
    friend class BatteryManagement;

public:
    OnBoardLeds();
    void setLed(int pos, uint8_t r, uint8_t g, uint8_t b); //sets the RGB value of one LED
    void setLeds(uint8_t r, uint8_t g, uint8_t b);          //sets the RGB value of every LED
};

#endif ON_BOARD_LEDS
