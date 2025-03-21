#include "ColorSensor.h"


volatile int colorsensorReady = 0;

void setupColorSensor(ColorSensor colorsensor){

  pinMode(COLORSENSOR_INTERRUPT_PIN, INPUT_PULLUP); // TCS interrupt output is Active-LOW and Open-Drain
  attachInterrupt(digitalPinToInterrupt(COLORSENSOR_INTERRUPT_PIN), isr_colorSensor, FALLING);
  pinMode(COLORSENSOR_LED, OUTPUT);
  digitalWrite(COLORSENSOR_LED, HIGH);
  // Set persistence filter to generate an interrupt for every RGB Cycle, regardless of the integration limits
  tcs.begin();
  tcs.write8(TCS34725_PERS, TCS34725_PERS_NONE);
  tcs.setInterrupt(true);
}


void debubValues(ColorSensor colorsensor){

    Serial.print("R: ");
    Serial.print(colorsensor.red, DEC);
    Serial.print(" ");
    Serial.print("G: ");
    Serial.print(colorsensor.green, DEC);
    Serial.print(" ");
    Serial.print("B: ");
    Serial.print(colorsensor.blue, DEC);
    Serial.print(" ");
    Serial.print("W: ");
    Serial.print(colorsensor.white, DEC);
    Serial.print(" ");
    Serial.print("Lux: ");
    Serial.print(colorsensor.lux, DEC);
    Serial.println(" ");

}

void isr_colorSensor()
{
  colorsensorReady = true;
}