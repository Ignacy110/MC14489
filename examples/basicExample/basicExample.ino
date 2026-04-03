// basicExample.ino example
// This example demonstrates basic usage of the MC14489 library

#include <MC14489.h> // include the library

#define ledDataPin 2 // define the Arduino pin number
#define ledClockPin 3 // define the Arduino pin number
#define ledEnablePin 4 // define the Arduino pin number

MC14489 ledDisplay(ledDataPin, ledClockPin, ledEnablePin); // create an ledDisplay object using Arduino pins for communication with the MC14489

void setup()
{
  ledDisplay.begin(); // initialize communication
}

void loop()
{
  ledDisplay.clear(0); // clear the display
  ledDisplay.set(1,12345); // set the number 12345 starting from position 1
  ledDisplay.display(); // update the display
  delay(1000); // 1 second delay

  ledDisplay.clear(0); // clear the display
  ledDisplay.set(1,"HELLO"); // set the text "HELLO" starting from position 1
  ledDisplay.display(); // update the display
  delay(1000); // 1 second delay
}