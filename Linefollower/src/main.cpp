#include <BluetoothSerial.h>
#include "Battery_check.hpp"
#include "Linefollower_and_Motor.hpp"
#include "US_Sensor.hpp"



//BluetoothSerial SerialBT;



void setup()
{
  Serial.begin(115200);
  setup_BatterCheck_and_LED();
  
  setup_Motor();

  setup_ultraschallsensor();

  setup_Linefollower();

  //Serial.begin(115200);
  //SerialBT.begin("ESP32_GREM");
  //Serial.print("out");
  
}

void loop()
{
  
  battery_check();
  static float distance;
  distance = ultrasonic_trigger();
  
  linefollower(distance);

}


