// Written by Thomas Quinn 04/12/17 tom@orbinnovations.com
// Property of Orb Innovations
// Laurel v2.01.00

// Software Revision Code X.YY.ZZ
// X = Major Hardware Changes (e.g. compnent changes)
// Y = Major Software Changes (e.g. changing color of RGB led/algorithm changes)
// Z = Minor Software Changes (e.g. changing variable names)

// Change Log
// ==========
// v2.00.00: - Hold Button to Start/Stop Recording.
// v2.00.00 - Hold Button to Start/Stop Recording.
// v2.01.00 - Implementing software naming convention.

// Hardware Setup
// Arduino Nano
// Adafruit LSM9DS0
// Adafruit Micro-SD Breakout Board

const int buttonPin = 12;
const int ledPin    = 13;

int  current;             // Current state of the button (LOW is pressed b/c pullup resistors)
long millis_held;         // How long the button was held (milliseconds)
long secs_held;           // How long the button was held (seconds)
long prev_secs_held;      // How long the button was held in the previous check
byte previous = HIGH;
unsigned long firstTime;  // how long since the button was first pressed
bool recording = LOW;

void setup() {
  Serial.begin(9600);             // Use serial for debugging
  pinMode(ledPin, OUTPUT);
  digitalWrite(buttonPin, HIGH);  // Turn on 20k pullup resistors to simplify switch input
}

void loop() {
  current = digitalRead(buttonPin);

  // if the button state changes to pressed, remember the start time
  if (current == LOW && previous == HIGH && (millis() - firstTime) > 200) {
    firstTime = millis();
  }

  millis_held = (millis() - firstTime);
  secs_held = millis_held / 1000;

  // This if statement is a basic debouncing tool, the button must be pushed for at least
  // 100 milliseconds in a row for it to be considered as a push.
  if (millis_held > 50) {

    if (current == LOW && secs_held > prev_secs_held) {
      ledblink(1, 50, ledPin); // Each second the button is held blink the indicator led
    }

    // check if the button was released since we last checked
    if (current == HIGH && previous == LOW) {
      if (secs_held <= 0) {
        Serial.println("Short Press");
        ledblink(1, 750, ledPin);
      }

      // If the button was held for 1-3 seconds blink LED 10 times
      if (secs_held >= 1 && secs_held < 3) {
        Serial.println("Medium Press");
        ledblink(10, 200, ledPin);
      }

      // Button held for 1-3 seconds, print out some info
      if (secs_held >= 3) {
        Serial.print("Long Press. Seconds held: ");
        Serial.print(secs_held);
        Serial.print("   Milliseconds held: ");
        Serial.print(millis_held);

        if (recording == LOW) {
          Serial.println("   Start Recording");
          recording = !recording;
          digitalWrite(ledPin, HIGH);
        }
        else {
          Serial.println("   Stop Recording");
          recording = !recording;
          digitalWrite(ledPin, LOW);
        }
      }
    }
  }

  previous = current;
  prev_secs_held = secs_held;
}

// Just a simple helper function to blink an led in various patterns
void ledblink(int times, int lengthms, int pinnum) {
  for (int x = 0; x < times; x++) {
    digitalWrite(pinnum, HIGH);
    delay (lengthms);
    digitalWrite(pinnum, LOW);
    delay(lengthms);
  }
}
