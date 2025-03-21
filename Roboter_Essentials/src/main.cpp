#include <Arduino.h>

#include "Battery_Management.h"
#include "impulsgeber.h"


void setup() {
Serial.begin(115200);
Serial.println("start");
impulsgeber.begin();
}

void loop() {

impulsgeber.printStatus();
batterymanager.battery_check();
}


