#include "ultrasonic_sensor.h"

UltrasonicSensor::UltrasonicSensor(){
  attachInterrupt(digitalPinToInterrupt(US_ECHO_PIN), ultrasonic_isr, CHANGE);
  pinMode(US_TRIGER_PIN, OUTPUT);
}
void UltrasonicSensor::ultrasonic_trigger(){
  static unsigned long t_trigger = micros();
    
  if(t_trigger < micros()){
  digitalWrite(US_TRIGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIGER_PIN, LOW);

  distans_ultsens =(double) ((unsigned long) (t_end_ultsens - t_begin_ultsens))*US_SPEED/2.0;
  //Serial.println(distans_ultsens);
  t_trigger += 100;
  }
}


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


void test(){
    i++;
}