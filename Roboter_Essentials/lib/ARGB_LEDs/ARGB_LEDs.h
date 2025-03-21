#ifndef ON_BOARD_LEDS
#define ON_BOARD_LEDS

#include <Arduino.h>
#include <FastLED.h>

#define NUMBER_OF_LEDS 4

#define DATA_PIN 23
#define CLOCK_PIN 18

class OnBoardLeds{
protected:
    CRGB leds[NUMBER_OF_LEDS];

    bool ledsInUse;

public:
    OnBoardLeds();
    void setLed(int pos, uint8_t r, uint8_t g, uint8_t b); //sets the RGB value of one LED
    void setLeds(uint8_t r, uint8_t g, uint8_t b);          //sets the RGB value of every LED
};

#endif //ON_BOARD_LEDS
