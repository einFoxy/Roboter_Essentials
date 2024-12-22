#include "MotorCorection.h"
#include <BluetoothSerial.h>

#define ROTATION_TIME 72//*10ms


//BluetoothSerial btSerial;
RoboterVar roboter;

// Motor R fährt bei PWM von 190
// Motor L fährt bei PWM von 200


void setup()
{
  //btSerial.begin("ESP32_GREIL");
  //Serial.begin(115200);
  quickSetupRoboter(roboter);

  pinMode(5, INPUT_PULLUP);
}

void loop()
{
  battery_check(roboter);
  if(!digitalRead(5)) return;

  static unsigned char tnow = 0, tnext = 0;
  static unsigned int i = 0;
  static bool state = 0;

  tnow = millis();
    if (((unsigned char)(tnow - tnext) >= 10))
    {
      tnext = tnow;

      if(state == 0){
        i += 3;
        motorSpeed(roboter.motor.motR_chanel,i);
        motorSpeed(roboter.motor.motL_chanel,i);

        if(i >= 1023){
          i = 0;
          state = 1;
          digitalWrite(roboter.motor.motR_DIR_PIN, !roboter.motor.motR_vorwaerts);
          digitalWrite(roboter.motor.motL_DIR_PIN, roboter.motor.motL_vorwaerts);
          motorSpeed(roboter.motor.motR_chanel, 512);
          motorSpeed(roboter.motor.motL_chanel, 512);
        }
      }

      else{
        i++;
        if(i == ROTATION_TIME){
          i = 0;
          state = 0;
          motorSpeed(roboter.motor.motR_chanel, 0);
          motorSpeed(roboter.motor.motL_chanel, 0);
          digitalWrite(roboter.motor.motR_DIR_PIN, roboter.motor.motR_vorwaerts);
          digitalWrite(roboter.motor.motL_DIR_PIN, roboter.motor.motL_vorwaerts);
          
        }
      } 
    
    
    }
}
/*
  if(btSerial.available() && state == 0)
  {

    char c = btSerial.read();
    btSerial.flush();
    if(c == '+')
      {
      grenze += 1;
      
      btSerial.println(grenze);
    }
    else if(c == '-'){
      grenze -= 1;
      
      btSerial.println(grenze);
    }
    else if (c =='a')
     { state =1;
     digitalWrite(roboter.motor.motR_DIR_PIN, !roboter.motor.motR_vorwaerts);
     digitalWrite(roboter.motor.motL_DIR_PIN, roboter.motor.motL_vorwaerts);
     motorSpeed(roboter.motor.motR_chanel, 512);
     motorSpeed(roboter.motor.motL_chanel, 512);
     
        }
    
    
  }
*/
    

      /*
      if(state)
        i -= 5;
      else
        i += 5;
      
      Serial.println(i);

      motorSpeed(roboter.motor.motL_chanel, i);
      motorSpeed(roboter.motor.motR_chanel, i);

      if(i >= 1100 || i == 0)
        state = !state;*/
   

  /*
  static int i = 0;

  if(btSerial.available())
  {
    char c = btSerial.read();
    if(c == '+')
      i +=10;
    else if(c == '-')
      i-= 10;
    else if(c == 'o')
      i = 0;
     else if(c == 'p')
      i += 1;
    else if(c == 'm')
      i -= 1;
    else if(c = 'f')
     i = 1023;
    btSerial.readString();
    btSerial.println(i);

    motorSpeed(roboter.motor.motL_chanel, i);
    motorSpeed(roboter.motor.motR_chanel, i);
    if(i >= 1024)
      i = 0;

  }
  */

  

      