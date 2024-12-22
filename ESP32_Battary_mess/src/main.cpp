
#include "RoboterBasics.h"
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

RoboterVar varibals;


void setup()
{

  
  quickSetupRoboter(varibals);
 
  
}

void loop()
{
  battery_check(varibals);
  //SerialBT.println(uBattery);
  
}
