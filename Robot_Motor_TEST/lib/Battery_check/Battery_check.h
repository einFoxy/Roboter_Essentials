#include <Arduino.h>
#include <FastLED.h>

// Voltages
#define MAX_VOLTAGE 4.1
#define MIN_OPERATING_VOTAGE 3.6
#define MIN_VOLTAGE 3.4

// LEDS
#define NUM_LEDS 4

#define DATA_PIN 23
#define CLOCK_PIN 18


// Pin für ADC der Batter
const short adcBattery_Pin = 39;

// Define the array of leds
CRGB leds[NUM_LEDS];

bool ledStauts = 0;
short led_light = 0; // welche der LEDS leuchtet

// Batery Messung

const int R1 = 47;                   // k
const int R2 = 100;                  // k
const int resulution_adc = 4096 - 1; // 12bit
const double u_referenz = 3.3;
unsigned long sumAnalogWerte;
double uBattery;
const int analogWerte_abfrage = 5; // ms
int anzAnalogWerte;
unsigned long lastWertAbfrage;
const double analog_convert = u_referenz * (R1 + R2) / (resulution_adc * R2); //*anzAnalogWerte);
bool shutdown = 0;

void action_minVoltage(){

// Shut Down

        // LEDS -> off
        for (int i = 0; i < NUM_LEDS; i++)
        {
          leds[i] = CRGB::Black;
        }

        
        leds[0] = CRGB::Red;
        FastLED.show();
        delay(100);

        leds[0] = CRGB::Black;
        FastLED.show();

        // Motor -> off

        // initialise Sleep
        shutdown = 1;
        esp_sleep_enable_timer_wakeup(4000000);
        esp_deep_sleep_start();

}

void action_minOperatingVoltage(){
for (int i = 0; i < 4; i++)
        {
          leds[i] = CRGB::Black;
        }

        ledStauts = !ledStauts;
        led_light = (led_light + 1) % 4;

        leds[led_light] = CRGB::Orange;
      }

void action_maxVoltage(){
    for (int i = 0; i < 4; i++)
        {
          leds[i] = CRGB::Green;
        }
}

void display_Voltage(){
          // Display Battery status with LEDs
      //uBattery = MIN_VOLTAGE;
      if (uBattery <= MIN_VOLTAGE)
      {
        action_minVoltage();
      }
      else if (uBattery <= MIN_OPERATING_VOTAGE)
      {
        action_minOperatingVoltage();
      }
      else if (uBattery >= MAX_VOLTAGE)
      {
        action_maxVoltage();
      }

      FastLED.show();
}
      


void battery_check(){
    if (((lastWertAbfrage + analogWerte_abfrage) < millis()) && !shutdown)
  {
    // adding Analogvaues
    sumAnalogWerte += analogRead(adcBattery_Pin);
    ++anzAnalogWerte;
    lastWertAbfrage = millis();

    // Mittelwert
    if (anzAnalogWerte > 200)
    {
      uBattery = (double)((sumAnalogWerte * analog_convert) / anzAnalogWerte);

      Serial.println(uBattery);

      sumAnalogWerte = 0;
      anzAnalogWerte = 0;

      display_Voltage();
    }
  }
}
