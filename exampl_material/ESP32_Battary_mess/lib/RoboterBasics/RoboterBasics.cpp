#include "RoboterBasics.h"




void quickSetupRoboter(RoboterVar &vars){
    pinMode(ADC_BATTERY_PIN, INPUT);

     //LED
     FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RBG>(vars.led.rgbLeds, NUM_LEDS); // setup LEDS

     //Motor
     pinMode(vars.motor.motR_DIR_PIN, OUTPUT);
     pinMode(vars.motor.motL_DIR_PIN, OUTPUT);

     //Richtung der Motoren Bestimmen
    digitalWrite(vars.motor.motR_DIR_PIN, vars.motor.motR_vorwaerts);
     digitalWrite(vars.motor.motL_DIR_PIN, vars.motor.motL_vorwaerts);
    //Setup von PWM Chanals 
     ledcSetup(vars.motor.motR_chanel, 16000,10);
     ledcSetup(vars.motor.motL_chanel, 16000,10);

     ledcAttachPin(vars.motor.motR_SpeedPin, vars.motor.motR_chanel);
     ledcAttachPin(vars.motor.motL_SpeedPin, vars.motor.motL_chanel);
}

void action_minVoltage(RoboterVar &vars){

// Shut Down

        // LEDS -> off
        for (int i = 0; i < NUM_LEDS; i++)
        {
          vars.led.rgbLeds[i] = CRGB::Black;
        }

        
        vars.led.rgbLeds[0] = CRGB::Red;
        FastLED.show();
        delay(100);

        vars.led.rgbLeds[0] = CRGB::Black;
        FastLED.show();

        // Motor -> off
        //ledcWrite(motR_chanel, 0);
        //ledcWrite(motL_chanel, 0);

        // initialise Sleep
        vars.battery._shutdown = 1;
        esp_sleep_enable_timer_wakeup(5000000);
        esp_deep_sleep_start();

}

void action_minOperatingVoltage(RoboterVar &vars){
for (int i = 0; i < 4; i++)
        {
          vars.led.rgbLeds[i] = CRGB::Black;
        }

        vars.led.ledStauts = !vars.led.ledStauts;
        vars.led.led_light = (vars.led.led_light + 1) % 4;

        vars.led.rgbLeds[vars.led.led_light] = CRGB::Orange;
      }

void action_maxVoltage(RoboterVar &vars){
    for (int i = 0; i < 4; i++)
        {
          vars.led.rgbLeds[i] = CRGB::Green;
        }
}

void display_Voltage(RoboterVar &vars){
          // Display Battery status with LEDs
      //uBattery = MIN_OPERATING_VOTAGE;
      if (vars.battery.uBattery <= MIN_VOLTAGE)
      {
        action_minVoltage(vars);
      }
      else if (vars.battery.uBattery <= MIN_OPERATING_VOTAGE)
      {
        action_minOperatingVoltage(vars);
      }
      else if (vars.battery.uBattery >= MAX_VOLTAGE)
      {
        action_maxVoltage(vars);
      }

      FastLED.show();
}
      


void battery_check(RoboterVar &vars){
    if (((vars.battery.lastWertAbfrage + vars.battery.analogWerte_abfrage) < millis()) && !vars.battery._shutdown)
  {
    // adding Analogvaues
    vars.battery.sumAnalogWerte += analogRead(ADC_BATTERY_PIN);
    ++vars.battery.anzAnalogWerte;
    vars.battery.lastWertAbfrage = millis();

    // Mittelwert
    if (vars.battery.anzAnalogWerte > 200)
    {
      vars.battery.uBattery = (double)((vars.battery.sumAnalogWerte * vars.battery.analog_convert) / vars.battery.anzAnalogWerte);

      //Serial.println(uBattery);
    

      vars.battery.sumAnalogWerte = 0;
      vars.battery.anzAnalogWerte = 0;

      display_Voltage(vars);
    }
  }
}

