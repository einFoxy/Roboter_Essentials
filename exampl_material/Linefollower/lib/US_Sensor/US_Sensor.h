#include <Arduino.h>

//Ultraschallpin
#define US_SPEED 0.033 // cm pro us
#define US_TRIGER_PIN 25
#define US_ECHO_PIN 26

//Ultraschallsensor vars
volatile unsigned long  t_begin_ultsens;
volatile unsigned long  t_end_ultsens;
float tempdistance;
float us_distance;



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

void setup_ultraschallsensor(){
  attachInterrupt(digitalPinToInterrupt(US_ECHO_PIN), ultrasonic_isr, CHANGE);
  pinMode(US_TRIGER_PIN, OUTPUT);
}

void ultrasonic_trigger(){
  static unsigned long t_trigger = millis();
  
  if(t_trigger < millis()){
  t_trigger += 70;

  digitalWrite(US_TRIGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIGER_PIN, LOW);

  tempdistance =(double) (t_end_ultsens - t_begin_ultsens)*US_SPEED/2.0;
  if(((int) tempdistance) < 1000)
      us_distance = tempdistance;
  }
}