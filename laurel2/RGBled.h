// Written by Thomas Quinn tom@orbinnovations.com
// Property of Orb Innovations
// RGBled.h - For control of an RGB LED

#ifndef RGBled_h
#define RGBled_h

#include "Arduino.h"

class RGBled
{
  public:
    RGBled(int red_pin, int green_pin, int blue_pin);
    void off();
    void color(const bool color[]);
    void flash(const bool color[], int onTime, int offTime);
    void red();
    void green();
    void blue();
    void yellow();
    void cyan();
    void magenta();
    void white();
  private:
    int _pins[3];
    int interval  = 0;
    bool ledState = true;
    unsigned long previousMillis  = 0;
};

#endif
