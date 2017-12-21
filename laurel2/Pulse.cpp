// Written by Thomas Quinn tom@orbinnovations.com
// Property of Orb Innovations
// Pulse.cpp - For reading heart rate monitor

// ARDUINO LIBRARIES ----------------------------------------------------------
#include "Arduino.h"

// CUSTOM LIBRARIES -----------------------------------------------------------
#include "Pulse.h"

Pulse::Pulse(int pin) {
  pinMode(pin, INPUT_PULLUP);
  _pin = pin;
}

void Pulse::setRate() {
  rate = analogRead(_pin);
}

int Pulse::getRate() {
  return rate;
}
