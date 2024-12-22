#include "Battery_check.hpp"

// Voltages
#define MAX_VOLTAGE 4.1
#define MIN_OPERATING_VOTAGE 3.6
#define MIN_VOLTAGE 3.4

// Pin für ADC der Batter
#define adcBattery_Pin 39

#define analogWerte_abfrage 5 // ms

// LEDS
#define NUM_LEDS 4

#define DATA_PIN 23
#define CLOCK_PIN 18

// Define the array of leds
CRGB leds[NUM_LEDS];

// Batery Messung

const int R1 = 47;                   // k
const int R2 = 100;                  // k
const int resulution_adc = 4096 - 1; // 12bit
const double u_referenz = 3.3;
double uBattery = 0;
const double analog_convert = (u_referenz * (R1 + R2)) / (resulution_adc * R2); //*anzAnalogWerte);
int ledsInUse = 0; 

void setup_BatterCheck_and_LED()
{
  pinMode(adcBattery_Pin, INPUT);
  FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RBG>(leds, NUM_LEDS); // setup LEDS
  // First Battery check to see if Roboter is able to opperate;
  intitila_BatteryCheck();
}

void intitila_BatteryCheck()
{

  unsigned long sumAnalogWerte = 0;
  unsigned long lastWertAbfrage = 0;
  int anzAnalogWerte = 0;

  while (uBattery == 0)
  {

    if (((lastWertAbfrage + analogWerte_abfrage) < millis()))
    {

      // adding Analogvaues
      sumAnalogWerte += analogRead(adcBattery_Pin);
      ++anzAnalogWerte;
      lastWertAbfrage = millis();

      // Mittelwert
      if (anzAnalogWerte > 200)
      {
        uBattery = (double)((sumAnalogWerte * analog_convert) / anzAnalogWerte);
        display_Voltage();
        break;
      }
    }
  }
}

void action_minVoltage()
{

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
  // ledcWrite(motR_chanel, 0);
  // ledcWrite(motL_chanel, 0);

  // initialise Sleep
  esp_sleep_enable_timer_wakeup(4000000);
  esp_deep_sleep_start();
}

void action_minOperatingVoltage()
{
  static bool ledStauts = 0;
  static short led_light = 0; // welche der LEDS leuchtet
  for (int i = 0; i < 4; i++)
  {
    leds[i] = CRGB::Black;
  }

  ledStauts = !ledStauts;
  led_light = (led_light + 1) % 4;

  leds[led_light] = CRGB::Orange;
}

void action_maxVoltage()
{
  for (int i = 0; i < 4; i++)
  {
    leds[i] = CRGB::Green;
  }
}

void display_Voltage()
{
  // Display Battery status with LEDs
  //uBattery = MIN_VOLTAGE; // for testing
  if (uBattery <= MIN_VOLTAGE)
  {
    ledsInUse = 1;
    action_minVoltage();
    FastLED.show();
  }
  else if (uBattery <= MIN_OPERATING_VOTAGE)
  {
    ledsInUse = 1;
    action_minOperatingVoltage();
    FastLED.show();
  }
  else if (uBattery >= MAX_VOLTAGE)
  { 
    ledsInUse = 1;
    action_maxVoltage();
    FastLED.show();
  }
  else
  { // Wenn LEDS nicht nur für Battery benutzt werden dann auskommentieren
    if(ledsInUse){
      for (int i = 0; i < 4; i++)
      {
        leds[i] = CRGB::Black;
      }
      ledsInUse = 0;
      FastLED.show(); 
    }
  }

}

void battery_check()
{
  static unsigned long sumAnalogWerte;
  static unsigned long lastWertAbfrage;
  static int anzAnalogWerte;

  if (((lastWertAbfrage + analogWerte_abfrage) < millis()))
  {

    // adding Analogvaues
    sumAnalogWerte += analogRead(adcBattery_Pin);
    ++anzAnalogWerte;
    lastWertAbfrage = millis();

    // Mittelwert
    if (anzAnalogWerte > 200)
    {
      uBattery = (double)((sumAnalogWerte * analog_convert) / anzAnalogWerte);

      // Serial.println(uBattery);

      sumAnalogWerte = 0;
      anzAnalogWerte = 0;

      //display_Voltage();
    }
  }
}

void setLeds(uint8_t r, uint8_t g, uint8_t b){
  //if(ledsInUse) return;

  for(int i = 0; i < NUM_LEDS; i++)
    leds[i].setRGB(r,g,b);
  FastLED.show();
}