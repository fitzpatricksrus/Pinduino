#include "Logging.h"
#include "Arduino.h"


// default loglevel if nothing is set from user
#define LOGLEVEL LOG_LEVEL_DEBUG


#define CR "\r\n"
#define LOGGING_VERSION 1


void Logging::init(LogLevel level, long baud){
    _level = level;
    Serial.begin(baud);
}

void Logging::error(const char* msg, ...){
    if (LOG_LEVEL_ERROR <= _level) {
		print ("ERROR: ",0);
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}


void Logging::warning(const char* msg, ...){
    if (LOG_LEVEL_WARNING <= _level) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

void Logging::info(const char* msg, ...){
    if (LOG_LEVEL_INFO <= _level) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}


void Logging::verbose(const char* msg, ...){
    if (Logging::LOG_LEVEL_MEGAVERBOSE <= _level) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}



 void Logging::print(const char *format, va_list args) {
 }
 
 Logging Logging::DEFAULT_LOG;

 
 
  




