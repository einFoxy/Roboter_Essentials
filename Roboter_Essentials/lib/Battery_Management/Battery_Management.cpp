#include "Battery_Management.h"


    unsigned long BatteryManagement::sumAnalogWerte = 0;
    char BatteryManagement::anzAnalogWerte = 0;
    double BatteryManagement::uBattery = 0;


BatteryManagement::BatteryManagement(int sampling_Periode):Motor(),OnBoardLeds(){
    samplingPeriode = sampling_Periode;
    pinMode(ADC_BATTERY_PIN, INPUT);

    analog_convert_factor = U_REFERENC * (R1 + R2) / (resulution_adc * R2); 
}

void BatteryManagement::action_minVoltage(){

// Shut Down

        // Motor -> off
        Motor::changeSpeed(0, MOTOR_RIGHT);
        Motor::changeSpeed(0,MOTOR_LEFT);

        // LEDS -> off
        OnBoardLeds::setLed(0,255,0,0); 
        delay(100);
        OnBoardLeds::setLed(0,0,0,0);


        // initialise Sleep
        esp_sleep_enable_timer_wakeup(SLEEP_TIME);
        esp_deep_sleep_start();

}

void BatteryManagement::action_minOperatingVoltage(){
static int posIlluminated = 0;

        OnBoardLeds::setLed(posIlluminated, 0,0,0);
        posIlluminated = (posIlluminated + 1) % 4;

        OnBoardLeds::setLed(posIlluminated, 255,255,0);

}

void BatteryManagement::action_maxVoltage(){

    OnBoardLeds::setLeds(0,255,0);

}

void BatteryManagement::display_Voltage()
{
  // Display Battery status with LEDs
  //uBattery = MIN_VOLTAGE; // for testing
  if (uBattery <= MIN_VOLTAGE)
  {
    OnBoardLeds::ledsInUse = 1;
    action_minVoltage();
  }
  else if (uBattery <= MIN_OPERATING_VOTAGE)
  {
    OnBoardLeds::ledsInUse = 1;
    action_minOperatingVoltage();
  }
  else if (uBattery >= MAX_VOLTAGE)
  { 
    OnBoardLeds::ledsInUse = 1;
    action_maxVoltage();
  }
  else
  { // Wenn LEDS nicht nur für Battery benutzt werden dann auskommentieren
    if(OnBoardLeds::ledsInUse){
        OnBoardLeds::setLeds(0,0,0);

        OnBoardLeds::ledsInUse = 0;
    }
  }

}

      


void BatteryManagement::battery_check(){
    static unsigned long lastWerteAbrageTime = 0;
    unsigned long currentTime = millis();
    if (((lastWerteAbrageTime + samplingPeriode) < currentTime))
  {
    // adding Analogvaues
    sumAnalogWerte += analogRead(ADC_BATTERY_PIN);
    ++anzAnalogWerte;
    lastWerteAbrageTime = currentTime;

    // Mittelwert
    if (anzAnalogWerte > 200)
    {
      uBattery = (double)((sumAnalogWerte * analog_convert_factor) / anzAnalogWerte);

      //Serial.println(uBattery);
    

      sumAnalogWerte = 0;
      anzAnalogWerte = 0;

      display_Voltage();
    }
  }
}

