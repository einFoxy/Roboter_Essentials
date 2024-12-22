#include <Arduino.h>
#include "Linefollower_and_Motor.hpp"

//Directions
#define FORWORD 0
#define BACKWORD 1
#define RIGHT 2
#define STRONG_RIGHT 3
#define LEFT 4
#define STRONG_LEFT 5
int direction;

//Linefollower
#define WHITE 0
#define BLACK 1
#define LF_RIGHT_LEFT 12
#define LINEFOLLOWER_PIN 36


//Motor rechts
  int motR_vorwaerts = 1;
  const int motR_chanel = 0;
  const int motR_SpeedPin = 2;
  const int motR_DIR_PIN = 15;
//Motor links
  int motL_vorwaerts = 0;
  const int motL_chanel = 1;
  const int motL_SpeedPin = 32;
  const int motL_DIR_PIN = 33;

//Linefollower OUTPUT
bool LF_R;
bool LF_L;



void setup_Motor(){
    //Motor setup
  pinMode(motR_DIR_PIN, OUTPUT);
  pinMode(motL_DIR_PIN, OUTPUT);

  digitalWrite(motR_DIR_PIN, motR_vorwaerts);
  digitalWrite(motL_DIR_PIN, motL_vorwaerts);

  ledcSetup(motR_chanel, 16000,10);
  ledcSetup(motL_chanel, 16000,10);

  ledcAttachPin(motR_SpeedPin, motR_chanel);
  ledcAttachPin(motL_SpeedPin, motL_chanel);

}

void setup_Linefollower(){
  pinMode(LF_RIGHT_LEFT, OUTPUT);
  pinMode(LINEFOLLOWER_PIN, INPUT);
}

void getLF(){

  //Right
  digitalWrite(LF_RIGHT_LEFT, LOW);
  //Serial.print("RIGHT: ");
  //Serial.print(analogRead(LINEFOLLOWER_PIN));
  if(analogRead(LINEFOLLOWER_PIN) < 500){
      LF_R = WHITE;
  }
  else
      LF_R = BLACK;

  //LEFT
  digitalWrite(LF_RIGHT_LEFT, HIGH); 
  //Serial.print("     LEFT: ");
  //Serial.println(analogRead(LINEFOLLOWER_PIN));
  if(analogRead(LINEFOLLOWER_PIN) < 500){
      LF_L = WHITE;
  }
  else
      LF_L = BLACK;

}

void linefollower(float us_distance){
  if(us_distance < 10){
    digitalWrite(motR_DIR_PIN, !motR_vorwaerts);
    digitalWrite(motL_DIR_PIN, motL_vorwaerts);
    ledcWrite(motR_chanel, 750);
    ledcWrite(motL_chanel, 750);
    return;
  }

  getLF();
  
  if(LF_R && LF_L){
    direction = FORWORD;
    execute_direction();
  }
  else if((LF_R == BLACK) && (LF_L == WHITE)){
      direction = RIGHT;
      execute_direction();
  }
  else if((LF_R == WHITE) && (LF_L == BLACK)){
      direction = LEFT;
      execute_direction();
  }
  else if((direction == RIGHT) || (direction == LEFT)){
    direction++;
    execute_direction();
  }

}

void execute_direction(){
  switch(direction)
{
case FORWORD:
digitalWrite(motR_DIR_PIN, motR_vorwaerts);
digitalWrite(motL_DIR_PIN, motL_vorwaerts);
ledcWrite(motR_chanel, 750);
ledcWrite(motL_chanel, 750);
break;
case BACKWORD: 
digitalWrite(motR_DIR_PIN, !motR_vorwaerts);
digitalWrite(motL_DIR_PIN, !motL_vorwaerts);
ledcWrite(motR_chanel, 750);
ledcWrite(motL_chanel, 750);
break;
case RIGHT:
digitalWrite(motR_DIR_PIN, motR_vorwaerts);
digitalWrite(motL_DIR_PIN, motL_vorwaerts);
ledcWrite(motR_chanel, 400);
ledcWrite(motL_chanel, 750);
break;
case STRONG_RIGHT:
digitalWrite(motR_DIR_PIN, motR_vorwaerts);
digitalWrite(motL_DIR_PIN, motL_vorwaerts);
ledcWrite(motR_chanel, 100);
ledcWrite(motL_chanel, 750);
break;
case LEFT:
digitalWrite(motR_DIR_PIN, motR_vorwaerts);
digitalWrite(motL_DIR_PIN, motL_vorwaerts);
ledcWrite(motR_chanel, 750);
ledcWrite(motL_chanel, 400);
break;
case STRONG_LEFT:
digitalWrite(motR_DIR_PIN, motR_vorwaerts);
digitalWrite(motL_DIR_PIN, motL_vorwaerts);
ledcWrite(motR_chanel, 750);
ledcWrite(motL_chanel, 100);
break;
}

}

