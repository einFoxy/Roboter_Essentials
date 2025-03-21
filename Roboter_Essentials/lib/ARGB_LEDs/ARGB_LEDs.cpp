#include "ARGB_LEDs.h"

    
OnBoardLeds::OnBoardLeds(){
        FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RBG>(leds, NUMBER_OF_LEDS); // setup LEDS
}


void OnBoardLeds::setLed(int pos, uint8_t r, uint8_t g, uint8_t b){
    if(ledsInUse) return;

    leds[pos].setRGB(r,g,b);
    FastLED.show();
}
void OnBoardLeds::setLeds(uint8_t r, uint8_t g, uint8_t b){
    if(ledsInUse) return;

    for(int i = 0; i < NUMBER_OF_LEDS; i++)
        leds[i].setRGB(r,g,b);
    FastLED.show();
}
