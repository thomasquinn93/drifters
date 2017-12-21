// Written by Thomas Quinn tom@orbinnovations.com
// Property of Orb Innovations
// Pulse.h - For reading heart rate monitor

#ifndef Pulse_h
#define Pulse_h

#include "Arduino.h"

class Pulse
{
  public:
    Pulse(int pin);
    void setRate();
    int getRate();
  private:
    int _pin;
    int rate;
};

#endif
