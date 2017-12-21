// Written by Thomas Quinn tom@orbinnovations.com
// Property of Orb Innovations
// OrbRTC.h - For reading RTC date and time

#ifndef OrbRTC_h
#define OrbRTC_h

#include "Arduino.h"

class OrbRTC
{
  public:
    void begin();
    void print();
    int year();
    int month();
    int day();
    int hour();
    int minute();
    int second();

  private:
    char daysOfTheWeek[7][12] = {"Sunday", "Monday","Tuesday", "Wednesday",
      "Thursday", "Friday", "Saturday"};
};

#endif
