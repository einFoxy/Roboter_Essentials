#include <Arduino.h>
#include <BluetoothSerial.h>
#include "Battery_check.hpp"
#include "Linefollower_and_Motor.hpp"
#include "US_Sensor.hpp"


// BluetoothSerial SerialBT;


// Interrupt Service Routine

/* tcs.getRawData() does a delay(Integration_Time) after the sensor readout.
We don't need to wait for the next integration cycle because we receive an interrupt when the integration cycle is complete*/
void getRawData_noDelay(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c) // muss in Colorsensor.h/.cpp coppied werden
{
  *c = tcs.read16(TCS34725_CDATAL);
  *r = tcs.read16(TCS34725_RDATAL);
  *g = tcs.read16(TCS34725_GDATAL);
  *b = tcs.read16(TCS34725_BDATAL);
}

void setup()
{
  Serial.begin(115200);
  pinMode(5, INPUT_PULLUP);

  setup_BatterCheck_and_LED();


  setup_Motor();

  setup_ultraschallsensor();

  setup_Linefollower();

  // Serial.begin(115200);
  // SerialBT.begin("ESP32_GREM");
  // Serial.print("out");
  //while (!digitalRead(5))
    ;
}

void loop()
{
  static uint16_t r, g, b, c, lux;
  static float distance;
  battery_check();

  // distance = ultrasonic_trigger();
  if (colorsensorReady)
  {
    getRawData_noDelay(&r, &g, &b, &c);
    lux = tcs.calculateLux(r,g,b);

    

    if (c <= 300 && lux <= 60)
    {
      
      if (r > g && r > b && lux <= 30)
      {
        setLeds(255, 0, 0);
      }
      else if (g > r && g > b && lux >= 50 && c <= 150 && c >= 100)
      {
        setLeds(0, 255, 0);
      }
      else if (b > r && b > g)
      {
        setLeds(0, 0, 255);
      }
      else
        setLeds(0,0,0);
      tcs.clearInterrupt();
      colorsensorReady = 0;
    }
  }
  linefollower(ultrasonic_trigger());
}
