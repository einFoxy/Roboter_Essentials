
#include "Battery_check.h"
#include <BluetoothSerial.h>
#include "US_Sensor.h"



BluetoothSerial SerialBT;


//Motor rechts
  int motR_vorwaerts = 1;
  const int motR_chanel = 0;
  const int motR_SpeedPin = 2;
  const int motR_DIR_PIN = 15;
//Motor links
  int motL_vorwaerts = 0;
  const int motL_chanel = 1;
  const int motL_SpeedPin = 32;
  const int motL_DIR_PIN = 33;



//void IRAM_ATTR ultrasonic_isr();

//void ultrasonic_trigger();



void setup()
{
  Serial.begin(115200);
  SerialBT.begin("ESP32_GREM");
  
  pinMode(adcBattery_Pin, INPUT);

  FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RBG>(leds, NUM_LEDS); // setup LEDS
//Motor setup
  pinMode(motR_DIR_PIN, OUTPUT);
  pinMode(motL_DIR_PIN, OUTPUT);

  digitalWrite(motR_DIR_PIN, motR_vorwaerts);
  digitalWrite(motL_DIR_PIN, motL_vorwaerts);

  ledcSetup(motR_chanel, 16000,10);
  ledcSetup(motL_chanel, 16000,10);

  ledcAttachPin(motR_SpeedPin, motR_chanel);
  ledcAttachPin(motL_SpeedPin, motL_chanel);


//Ultraschallsensor
  attachInterrupt(digitalPinToInterrupt(US_ECHO_PIN), ultrasonic_isr, CHANGE);
  pinMode(US_TRIGER_PIN, OUTPUT);
}

void loop()
{
  battery_check();
  
  //ultrasonic_trigger;
  ultrasonic_trigger();
  
  
}


