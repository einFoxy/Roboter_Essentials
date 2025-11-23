
#include "Battery_Management.h"
#include "Impulsgeber/impulsgeber.h"

#include "motor.h"
#include "log.h"


//BluetoothSerial SerialBT;
Motor motor;

void setup() {
Serial.begin(115200);
Serial.println("start");
//SerialBT.begin("ESP32_GREIL");

impulsgeber.begin();
//motor.changeSpeed(1024, MOTOR_RIGHT);
//motor.changeSpeed(1024, MOTOR_LEFT);
}


void loop() {
static unsigned long tlast = 0;
unsigned long tnow = millis();
float dt_seconds = (tnow - tlast)/1000.0f;

static unsigned long tickslast = 0;
if(tnow > (tlast + 100) ){
    motor.setSpeed(Speed(0.7,0.0));

    //static unsigned int newTicks, lastTicks = 0;
    //newTicks = impulsgeber.getRightTicks();

    //motor.setMotorSpeeds(1,0);
    //LOG("TICKs Right: ");
    //LOG_LN(newTicks - lastTicks);
    //lastTicks = newTicks;

    tlast = tnow;
}
//motor.setMotorSpeeds(1.0,0.0);

/*
//impulsgeber.printStatus();
float v = motor.calculateVelocity(impulsgeber.getRightTicks() - tickslast, impulsgeber.getRightTicks() - tickslast, dt_seconds);
//Serial.println(dt_seconds);
//Serial.println("hello World");
SerialBT.print(motor.getRightTicks() - tickslast);
SerialBT.print("   ");
SerialBT.print(motor.getLeftTicks() - tickslast);
SerialBT.print("   ");
SerialBT.println(v);
*/


//tickslast = impulsgeber.getRightTicks();

//delayMicroseconds(5);
batterymanager.battery_check();
}


