
// temperatureDisplay.ino example
// This example demonstrates how to use the MC14489 library to display temperature values

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
  // temperature value
  float temperature = 23.736;

  // Display format: [X][X].[X][°][C]

  ledDisplay.clear(0); // clear the display
  ledDisplay.set(4,"*C"); // set the string "*C"
  ledDisplay.set(3, (int)(temperature * 10), 1); // set temperature on the display; multiply by 10 to display one decimal place (integer required); right-align for third position
  ledDisplay.setDotPoint(2); // set decimal point after second digit
  ledDisplay.display(); // update the display

  delay(1000);
}