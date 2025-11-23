#include <Arduino.h>
#define DEBUG

#ifndef LOG_H
#define LOG_H

#ifdef DEBUG

#define LOG(msg)\
Serial.print(msg)

#define LOG_LN(msg)\
Serial.println(msg)

#else // do nothing 

#define LOG(msg) 
#define LOG_LN(msg)

#endif //DEBUG



#endif //LOG_H