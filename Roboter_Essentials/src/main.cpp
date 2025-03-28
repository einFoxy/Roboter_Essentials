#include <Arduino.h>
#include "BluetoothSerial.h"

#include "Battery_Management.h"
#include "Impulsgeber/impulsgeber.h"

#include "motor.h"

BluetoothSerial SerialBT;
Motor motor;

void setup() {
Serial.begin(115200);
Serial.println("start");
SerialBT.begin("ESP32_GREIL");
impulsgeber.begin();

motor.changeSpeed(1024, MOTOR_RIGHT);
motor.changeSpeed(1024, MOTOR_LEFT);
}

void loop() {
static unsigned long tlast = 0;
auto tnow = micros();
auto dt_seconds = tnow - tlast;
//impulsgeber.printStatus();
float v = motor.calculateVelocity(impulsgeber.getRightTicks(), impulsgeber.getLeftTicks(), dt_seconds);

Serial.println(dt_seconds);
SerialBT.println(v);


batterymanager.battery_check();
tlast = tnow;
delayMicroseconds(5);
}


