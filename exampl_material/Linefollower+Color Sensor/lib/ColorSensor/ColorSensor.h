#ifndef COLOR_SENSOR
#define COLOR_SENSOR

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <SPI.h>

#define COLORSENSOR_LED 13
#define COLORSENSOR_INTERRUPT_PIN 4


typedef struct {
    uint16_t red, green, blue, white, lux; //lux = helligkeit
    Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X);
}ColorSensor;

void setupColorSensor(ColorSensor colorsensor);

void debubValues(ColorSensor colorSensor);


void isr_colorSensor();


#endif