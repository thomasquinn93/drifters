// Written by Thomas Quinn tom@orbinnovations.com
// Property of Orb Innovations
// RGBled.cpp - For control af an RGB LED

// ARDUINO LIBRARIES ----------------------------------------------------------
#include "Arduino.h"

// CUSTOM LIBRARIES -----------------------------------------------------------
#include "RGBled.h"

#define ACTIVE LOW // common annode = LOW, common cathode = HIGH

RGBled::RGBled(int red_pin, int green_pin, int blue_pin) {
  pinMode(red_pin, OUTPUT);
  _pins[0] = red_pin;
  pinMode(green_pin, OUTPUT);
  _pins[1] = green_pin;
  pinMode(blue_pin, OUTPUT);
  _pins[2] = blue_pin;
}

void RGBled::off() {
  for(int i = 0; i < 3; i++) {
    digitalWrite(_pins[i], !ACTIVE);
  }
}

void RGBled::color(const bool color[]) {
  digitalWrite(_pins[0], !ACTIVE ^ color[0]);
  digitalWrite(_pins[1], !ACTIVE ^ color[1]);
  digitalWrite(_pins[2], !ACTIVE ^ color[2]);
}

void RGBled::flash(const bool value[], int onTime, int offTime) {
  if (ledState) {
    color(value);
  } else {
    off();
  }

  unsigned long currentMillis = millis();

  if ((unsigned long)(currentMillis - previousMillis) >= interval) {

    if (ledState) {

      interval = offTime;
    } else {

      interval = onTime;
    }
    ledState = !ledState;
    previousMillis = currentMillis;
  }
}

void RGBled::red() {
  digitalWrite(_pins[0],  ACTIVE);
  digitalWrite(_pins[1], !ACTIVE);
  digitalWrite(_pins[2], !ACTIVE);
}

void RGBled::green() {
  digitalWrite(_pins[0], !ACTIVE);
  digitalWrite(_pins[1],  ACTIVE);
  digitalWrite(_pins[2], !ACTIVE);
}

void RGBled::blue() {
  digitalWrite(_pins[0], !ACTIVE);
  digitalWrite(_pins[1], !ACTIVE);
  digitalWrite(_pins[2],  ACTIVE);
}

void RGBled::yellow() {
  digitalWrite(_pins[0],  ACTIVE);
  digitalWrite(_pins[1],  ACTIVE);
  digitalWrite(_pins[2], !ACTIVE);
}

void RGBled::cyan() {
  digitalWrite(_pins[0], !ACTIVE);
  digitalWrite(_pins[1],  ACTIVE);
  digitalWrite(_pins[2],  ACTIVE);
}

void RGBled::magenta() {
  digitalWrite(_pins[0],  ACTIVE);
  digitalWrite(_pins[1], !ACTIVE);
  digitalWrite(_pins[2],  ACTIVE);
}

void RGBled::white() {
  digitalWrite(_pins[0],  ACTIVE);
  digitalWrite(_pins[1],  ACTIVE);
  digitalWrite(_pins[2],  ACTIVE);
}
