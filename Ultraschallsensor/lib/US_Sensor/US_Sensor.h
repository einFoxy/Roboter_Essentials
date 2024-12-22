#include <Arduino.h>

//Ultraschallpin
#define US_SPEED 0.033 // cm pro us
#define US_TRIGER_PIN 25
#define US_ECHO_PIN 26

//Ultraschallsensor
volatile unsigned long  t_begin_ultsens;
volatile unsigned long  t_end_ultsens;
double distans_ultsens;


void IRAM_ATTR ultrasonic_isr(){
    static bool status = 0;

    switch(status){
      case 0: 
        t_begin_ultsens = micros();
        break;
      case 1:
        t_end_ultsens = micros();
      

        break;
    }
    status = !status;
}

void ultrasonic_trigger(){
  static unsigned long t_trigger = micros();
  
  if(t_trigger < micros()){
  digitalWrite(US_TRIGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIGER_PIN, LOW);

  distans_ultsens =(double) (t_end_ultsens - t_begin_ultsens)*US_SPEED/2.0;
  Serial.println(distans_ultsens);
  t_trigger += 100;
  }

}