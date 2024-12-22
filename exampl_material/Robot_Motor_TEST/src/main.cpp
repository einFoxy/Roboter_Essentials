#include <Arduino.h>
#include "Battery_check.h"


  int motR_vorwaerts = 1;
  const int motR_chanel = 0;
  const int motR_SpeedPin = 2;
  const int motR_DIR_PIN = 15;


  


  int motL_vorwaerts = 0;
  const int motL_chanel = 1;
  const int motL_SpeedPin = 32;
  const int motL_DIR_PIN = 33;
  
#

void setup()
{
  Serial.begin(115200);
  // SerialBT.begin("ESP32_GREM");
  pinMode(adcBattery_Pin, INPUT);

  FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RBG>(leds, NUM_LEDS); // setup LEDS

  pinMode(motR_DIR_PIN, OUTPUT);
  pinMode(motL_DIR_PIN, OUTPUT);

  digitalWrite(motR_DIR_PIN, motR_vorwaerts);
  digitalWrite(motL_DIR_PIN, motL_vorwaerts);

  ledcSetup(motR_chanel, 16000,10);
  ledcSetup(motL_chanel, 16000,10);

  ledcAttachPin(motR_SpeedPin, motR_chanel);
  ledcAttachPin(motL_SpeedPin, motL_chanel);
  
  
  ledcWrite(motR_chanel, 512);
  ledcWrite(motL_chanel, 512);
}

void loop()
{
  battery_check();
  
  static int i = 0;

  for (; i < 1024; i++)
  {
    ledcWrite(motR_chanel, i);
    ledcWrite(motL_chanel, i);
    delay(10);
  }
  delay(100);

    for (; i >= 0; i--)
  {
    ledcWrite(motR_chanel, i);
    ledcWrite(motL_chanel, i);
    delay(10);
  }
  delay(100);
  

}


