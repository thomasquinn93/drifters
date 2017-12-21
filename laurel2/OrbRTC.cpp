// Written by Thomas Quinn tom@orbinnovations.com
// Property of Orb Innovations
// OrbRTC.cpp - For reading RTC date and time

// ARDUINO LIBRARIES ----------------------------------------------------------
#include "Arduino.h"
#include <Wire.h>
#include "RTClib.h"

// CUSTOM LIBRARIES -----------------------------------------------------------
#include "OrbRTC.h"

RTC_PCF8523 rtc;

void OrbRTC::begin() {
  rtc.begin();
}

void OrbRTC::print() {
  DateTime now = rtc.now();

  Serial.print("Date: ");
  Serial.print(now.year(), DEC);
  Serial.print("/");
  Serial.print(now.month(), DEC);
  Serial.print("/");
  Serial.println(now.day(), DEC);

  Serial.print("Time:  ");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.println();
}

int OrbRTC::year() {
  DateTime now = rtc.now();
  return now.year();
}

int OrbRTC::month() {
  DateTime now = rtc.now();
  return now.month();
}

int OrbRTC::day() {
  DateTime now = rtc.now();
  return now.day();
}

int OrbRTC::hour() {
  DateTime now = rtc.now();
  return now.hour();
}

int OrbRTC::minute() {
  DateTime now = rtc.now();
  return now.minute();
}

int OrbRTC::second() {
  DateTime now = rtc.now();
  return now.second();
}
