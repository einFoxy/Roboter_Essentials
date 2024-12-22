#ifndef BATTERY_CHECK
#define BATTERY_CHECK

#include <Arduino.h>
#include "../Motor/motor.h"
#include "../ARGB_LEDs/ARGB_LEDs.h"

// Voltages
#define MAX_VOLTAGE 4.1
#define MIN_OPERATING_VOTAGE 3.3
#define MIN_VOLTAGE 3.0

// Pin für ADC der Batter
#define ADC_BATTERY_PIN 39

//phisical parameters
#define R1 47 //k
#define R2 100 //k
#define resulution_adc  4095 // 12bit - 1
#define U_REFERENC 3.3

//sleeptime for shutdown
#define SLEEP_TIME 4000000 //us


class BatteryManagement:private Motor, private OnBoardLeds
{
private:
    bool isSetUp;
protected:
    static unsigned long sumAnalogWerte;
    static char anzAnalogWerte;
    static double uBattery;
    static  int samplingPeriode; // ms
    static double analog_convert_factor; 

public:
    BatteryManagement(int samplingPeriode = 5);
    void action_minVoltage();
    void action_minOperatingVoltage();
    void action_maxVoltage();
    void display_Voltage();
    void battery_check();
};

#endif
