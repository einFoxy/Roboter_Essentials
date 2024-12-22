
#ifndef BATTERY_CHECK
#define BATTERY_CHECK

#include <Arduino.h>
#include <FastLED.h>

// Voltages
#define MAX_VOLTAGE 4.1
#define MIN_OPERATING_VOTAGE 3.6
#define MIN_VOLTAGE 3.2

// LEDS
#define NUM_LEDS 4

#define DATA_PIN 23
#define CLOCK_PIN 18


// Pin für ADC der Batter
#define ADC_BATTERY_PIN 39

typedef struct{
// Define the array of leds
CRGB rgbLeds[NUM_LEDS];

bool ledStauts = 0;
short led_light = 0; // welche der LEDS leuchtet
}Led;

typedef struct{
// Battery Messung
const int R1 = 47;                   // k
const int R2 = 100;                  // k
const int resulution_adc = 4096 - 1; // 12bit
const double u_referenz = 3.3;
unsigned long sumAnalogWerte;
char anzAnalogWerte;
double uBattery;
const int analogWerte_abfrage = 5; // ms
unsigned long lastWertAbfrage;
const double analog_convert = u_referenz * (R1 + R2) / (resulution_adc * R2);
bool _shutdown = 0;
}Battery;

//Motor Vars
typedef struct{
  const int motR_vorwaerts = 1;
  const int motR_chanel = 0;
  const int motR_SpeedPin = 2;
  const int motR_DIR_PIN = 15;

  const int motL_vorwaerts = 0;
  const int motL_chanel = 1;
  const int motL_SpeedPin = 32;
  const int motL_DIR_PIN = 33;
}Motor;

typedef struct{
  Led led;
  Battery battery;
  Motor motor;
}RoboterVar;

void quickSetupRoboter(RoboterVar &vars);

void action_minVoltage(RoboterVar &vars);
void action_minOperatingVoltage(RoboterVar &vars);
void action_maxVoltage(RoboterVar &vars);
void display_Voltage(RoboterVar &vars);
void battery_check(RoboterVar &vars);





#endif

