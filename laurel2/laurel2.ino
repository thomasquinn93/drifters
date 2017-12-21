// Written by Thomas Quinn tom@orbinnovations.com
// Property of Orb Innovations
// Laurel

#define version "2.03.00"

// Software Revision Code X.YY.ZZ
// X = Major Hardware Changes (e.g. compnent changes)
// Y = Major Software Changes (e.g. changing color of RGB led/algorithm changes)
// Z = Minor Software Changes (e.g. changing variable names)

// Change Log
// ==========
// v2.00.00: - Hold Button to Start/Stop Recording.
// v2.00.00 - Hold Button to Start/Stop Recording.
// v2.01.00 - Implementing software naming convention.
// v2.01.01 - Added function prototype to adheard to C++ standards.
// v2.02.00 - Moved to Adafruit Adalogger M0 (ignoring revision code template
//            for simplicity).
// v2.02.01 - Pin I/O Comments update.
// v2.03.00 - Moved Blue LED to pin 11.
//          - Moved from ATOM back to Arduino IDE due to library issue. Arduino
//            IDE is used in "External Editor Mode".
//          - Started spilitting functionality into classes (libraries).
//          - Version writes XYZ Acc & Gyro values to SD card as .csv files.

// TODO
// v2.04.00 - Save raw data not through filters.
//          - Potentially change data types.
//          - Try structs and .bin files.

// Hardware Setup
// Adafruit Feather M0 Basic Proto
// Adafruit Adalogger FeatherWing
// SparkFun IMU Breakout MPU-9250
// Pulsesensor.com Heart Rate Sensor
// SPST Push button
// 10k Resistor

// Pin I/O - Feather
// SDA      - IMU SDA
// SCL      - IMU SCL
// A5       - Pulse Sensor
// Pin 5    - Pull Up Button (10k Resisotr to GND)

// Pin I/O - 9250
// SDA      - Feather SDA
// SCl      - Fether SCL
// FSYNC    - Feather GND
// VDD      - Feather 3.3V
// GND      - Feather GND

// PRE-CODE ===================================================================

// ARDUINO LIBRARIES ----------------------------------------------------------
#include <SPI.h>
#include <SD.h>

// CUSTOM LIBRARIES -----------------------------------------------------------
#include "RGBled.h"
#include "Button.h"
#include "Pulse.h"
//#include "OrbSD.h"
#include "OrbRTC.h"
#include "OrbIMU.h"

RGBled  RGB(6, 9, 11);
Button  button(5);
//OrbSD   card(10);
OrbRTC  clk;
OrbIMU  imu;

// check board type and ammend serial commands for Feather
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

// CONSTANT VARIABLES ---------------------------------------------------------
const bool RED[]     = {1, 0, 0};
const bool GREEN[]   = {0, 1, 0};
const bool BLUE[]    = {0, 0, 1};
const bool YELLOW[]  = {1, 1, 0};
const long printFreq = 40; // in Hz

// VOLATILE VARIABLES ---------------------------------------------------------
int menu = 0;
int submenu = 0;
unsigned long previousMillis = 0;

File dataFile;

const int chipSelect = 10;

const long sample = 2500; // sample time in microseconds (1000000us = 1s)
long previousTime = 0;
String file;
unsigned long currentTime = 0;
bool sdStatus;

}

// MAIN CODE ==================================================================

void setup() {
  RGB.off();

  Serial.begin(9600);
  delay(2000);
  Serial.println(version);

  clk.begin();
  imu.begin();

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  pinMode(A0, INPUT_PULLUP);
}

void loop() {
  int buttonState = button.poll();
  if (buttonState == 1) {
    menu++;
    if (menu > 2) {
      menu = 0;
    }
  } else if (buttonState == 2) {
    submenu++;
    if (submenu > 1) {
      submenu = 0;
    }
  }
  switch (menu) {
    default:
      // idle mode
      idle();
      break;
    case 1:
      // loggging mode
      record();
      break;
    case 2:
      // live mode
      live();
      break;
  }
}

void idle() {
  RGB.flash(GREEN, 50, 1500);
}

void live() {
  RGB.flash(BLUE, 50, 1500);
  unsigned long _currentMillis = millis();
  if (_currentMillis - previousMillis >= (1000/printFreq)) {
    previousMillis = _currentMillis;
    clk.print();
    imu.getAccel();
    imu.getGyro();
    imu.getMag();
    imu.quaternion();
    imu.print();
    Serial.println(millis());
    Serial.println("");
  }
}

void record() {
  RGB.yellow();

  if (submenu == 1) {

    // generate files
    file = generateFiles();
    //Serial.print(file);
    generateFileHeader();

    for (int i = 0; i < 5; i++) {
      RGB.red();
      delay(500);
      RGB.off();
      delay(500);
    }

    RGB.red();
    dataFile = SD.open(file, FILE_WRITE);

    while(1) {
      //Serial.println("Logging");
      logData();


      if (button.poll() == 2){
        submenu = 0;
        dataFile.close();
        for (int i = 0; i < 5; i++) {
          RGB.yellow();
          delay(100);
          RGB.off();
          delay(100);
        }
        Serial.println("Data Saved");
        break;

      }
    }
  }
}

void logData() {
    // record current time
    currentTime = micros();

    // open file on SD card


    // write to SD card once per sameple
    if (currentTime - previousTime >= sample) {
      previousTime = currentTime;

      // write to SD card
      SDwrite();
    }

}

void SDwrite() {
  imu.getAccel();
  imu.getGyro();
  imu.quaternion();
  dataFile.print(micros());
  dataFile.print(",");
  dataFile.print(imu.accX());
  dataFile.print(",");
  dataFile.print(imu.accY());
  dataFile.print(",");
  dataFile.print(imu.accZ());
  dataFile.print(",");
  dataFile.print(imu.gyroX());
  dataFile.print(",");
  dataFile.print(imu.gyroY());
  dataFile.print(",");
  dataFile.print(imu.gyroZ());
  dataFile.print(",");
  dataFile.print(analogRead(A0));
  dataFile.println(",");
}

String generateFiles() {
  char filename[] = "00000000.csv";
  String fileName = String();
  String message = String();
  unsigned int filenumber = 1;
  while (!filenumber == 0) {
    filename[0] = (clk.year() / 10) % 10 + '0';   //To get 3rd digit from year()
    filename[1] = clk.year() % 10 + '0';          //To get 4th digit from year()
    filename[2] = clk.month() / 10 + '0';         //To get 1st digit from month()
    filename[3] = clk.month() % 10 + '0';         //To get 2nd digit from month()
    filename[4] = clk.day() / 10 + '0';           //To get 1st digit from day()
    filename[5] = clk.day() % 10 + '0';           //To get 2nd digit from day()
    filename[6] = (filenumber / 10) % 10 + '0';
    filename[7] = filenumber % 10 + '0';
    fileName = String(filename);

    message = fileName;

    char charFileName[fileName.length() + 1];
    fileName.toCharArray(charFileName, sizeof(charFileName));

    if (SD.exists(charFileName)) {
      message += " exists.";
      filenumber++;
      if (filenumber > 99) {
        filenumber = 0;
        //Serial.println("Memory Full");
      }
    }
    else {
      File dataFile = SD.open(charFileName, FILE_WRITE);
      message += " created.";
      dataFile.close();
      filenumber = 0;
    }
    //Serial.println(message);
  }
  return fileName;
}

void generateFileHeader() {
  dataFile = SD.open(file, FILE_WRITE);
  dataFile.print(String(clk.year()) + "/" + String(clk.month()) + "/" + String(clk.day()) + " " + String(clk.hour()) + ":" + String(clk.minute()) + ":" + String(clk.second()) + ",");
  dataFile.print("T = ");
  dataFile.print(sample);
  dataFile.println("us");
  dataFile.print("t");
  dataFile.print(",");
  dataFile.print("accX");
  dataFile.print(",");
  dataFile.print("accY");
  dataFile.print(",");
  dataFile.print("accZ");
  dataFile.print(",");
  dataFile.print("gyroX");
  dataFile.print(",");
  dataFile.print("gyroY");
  dataFile.print(",");
  dataFile.print("gyroZ");
  dataFile.print(",");
  dataFile.println("pulse");
  dataFile.close();
}
