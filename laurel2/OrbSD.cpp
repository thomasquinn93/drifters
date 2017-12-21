// Written by Thomas Quinn tom@orbinnovations.com
// Property of Orb Innovations
// ORBSD.cpp - For writing to SD card

// // ARDUINO LIBRARIES ----------------------------------------------------------
// #include "Arduino.h"
// #include <SPI.h>
// #include <SD.h>
//
// // CUSTOM LIBRARIES -----------------------------------------------------------
// #include "OrbSD.h"
// #include "OrbRTC.h"
//
// File dataFile;
//
// OrbSD::OrbSD(int pin) {
//   _pin = pin;
// }
//
// bool OrbSD::begin() {
//   if (!SD.begin(_pin)) {
//     return 0;
//   }
//   return 1;
// }
//
// void OrbSD::logData(float accX, float accY, float accZ, float gyroX, float gyroY, float gyroZ) {
// 
// }
//
// // String OrbSD::generateFiles() {
// //   char filename[] = "00000000.csv";
// //   String fileName = String();
// //   String message = String();
// //   unsigned int filenumber = 1;
// //   while (!filenumber == 0) {
// //     filename[0] = (2017 / 10) % 10 + '0';   //To get 3rd digit from year()
// //     filename[1] = 2017 % 10 + '0';          //To get 4th digit from year()
// //     filename[2] = 12 / 10 + '0';         //To get 1st digit from month()
// //     filename[3] = 12 % 10 + '0';         //To get 2nd digit from month()
// //     filename[4] = 21 / 10 + '0';           //To get 1st digit from day()
// //     filename[5] = 21 % 10 + '0';           //To get 2nd digit from day()
// //     filename[6] = (filenumber / 10) % 10 + '0';
// //     filename[7] = filenumber % 10 + '0';
// //     fileName = String(filename);
// //
// //     message = fileName;
// //
// //     char charFileName[fileName.length() + 1];
// //     fileName.toCharArray(charFileName, sizeof(charFileName));
// //
// //     if (SD.exists(charFileName)) {
// //       message += " exists.";
// //       filenumber++;
// //       if (filenumber > 99) {
// //         filenumber = 0;
// //         //Serial.println("Memory Full");
// //       }
// //     }
// //     else {
// //       File dataFile = SD.open(charFileName, FILE_WRITE);
// //       message += " created.";
// //       dataFile.close();
// //       filenumber = 0;
// //     }
// //     //Serial.println(message);
// //   }
// //   return fileName;
// // }
// //
// // void OrbSD::generateFileHeader(String file) {
// //   dataFile = SD.open(file, FILE_WRITE);
// //   dataFile.print(String(clk.now.year()) + "/" + String(clk.now.month()) + "/" + String(clk.now.day()) + " " + String(clk.now.hour()) + ":" + String(clk.now.minute()) + ":" + String(clk.now.second()) + ",");
// //   dataFile.print("T = ");
// //   //dataFile.print(sample);
// //   dataFile.println("us");
// //   dataFile.print("t");
// //   dataFile.print(",");
// //   dataFile.print("Channel 1");
// //   dataFile.print(",");
// //   dataFile.print("Channel 2");
// //   dataFile.print(",");
// //   dataFile.println("Channel 3");
// //   dataFile.close();
// // }
