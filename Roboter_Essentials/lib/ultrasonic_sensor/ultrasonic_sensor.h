#include <Arduino.h>

//Ultraschallpin
#define US_SPEED 0.033 // cm pro us
#define US_TRIGER_PIN 25
#define US_ECHO_PIN 26


void IRAM_ATTR ultrasonic_isr();

class  UltrasonicSensor{
private:
    volatile unsigned long  t_begin_ultsens;
    volatile unsigned long  t_end_ultsens;
protected:
    double distans_ultsens;

    friend void IRAM_ATTR ultrasonic_isr();

public:
    UltrasonicSensor();
    
    void ultrasonic_trigger();
};

