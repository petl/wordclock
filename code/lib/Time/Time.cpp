#include "Time.h"


Time::Time(int8_t hours, int8_t minutes)  {
  this->hours_ = hours;
  this->minutes_ = minutes;
}

void Time::setTime(int8_t hours, int8_t minutes){
    if(hours>23){
        hours = hours - 24;
    } 
    if(minutes>59){
        minutes = minutes - 60;
        hours = hours + 1;
    } 
    this->saved_millis_ = millis();
    this->hours_ = hours;
    this->minutes_ = minutes;
}

int8_t Time::getMinutes(){
    unsigned long delta_millis = millis() - this->saved_millis_;
    int8_t minutes = (this->minutes_ + delta_millis/(1000*60))%60;
    return minutes;
}

int8_t Time::getHours(){
    unsigned long delta_millis = millis() - this->saved_millis_;
    int8_t hours = (this->hours_ + delta_millis/(1000*60*60))%24;
    return hours;
}
