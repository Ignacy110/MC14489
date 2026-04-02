
// allMethods.ino example
// This example demonstrates all available methods of the MC14489 library

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
  // set() methods - sets data on the display :

  ledDisplay.clear(0);
  ledDisplay.set(2,123); //  set number 123 from the second position
  ledDisplay.display(); // update the display
  delay(1000); // wait 1 second

  ledDisplay.clear(0);
  ledDisplay.set(5,840,1); // set number 840 and right align to the fifth position
  ledDisplay.display();
  delay(1000);

  ledDisplay.clear(0);
  ledDisplay.set(3,"OFF"); // set text "OFF" the from third position
  ledDisplay.display();
  delay(1000);

  ledDisplay.clear(0);
  ledDisplay.set(2,"o7",1); // set text "o7" and right align to the second position
  ledDisplay.display();
  delay(1000);

  // clear() methods:

  ledDisplay.clear(0); // clear the display - blank display
  ledDisplay.display();
  delay(1000);

  ledDisplay.clear(1); // clear the display - fill with zeros
  ledDisplay.display();
  delay(1000);

  // setDotPoint() methods - decimal point settings:

  ledDisplay.setDotPoint(1); // set the dot after the first digit
  ledDisplay.display();
  delay(1000);

  ledDisplay.setDotPoint(2); // set the dot after the second digit
  ledDisplay.display();
  delay(1000);

  ledDisplay.setDotPoint(3); // set the dot after the third digit
  ledDisplay.display();
  delay(1000);

  ledDisplay.setDotPoint(4); // set the dot after the fourth digit
  ledDisplay.display();
  delay(1000);

  ledDisplay.setDotPoint(5); // set the dot after the fifth digit
  ledDisplay.display();
  delay(1000);

  ledDisplay.setDotPoint(6); // set the dot after first and second digit
  ledDisplay.display();
  delay(1000);

  ledDisplay.setDotPoint(7); // set the dot after all digits
  ledDisplay.display();
  delay(1000);

  ledDisplay.setDotPoint(0); // no dots
  ledDisplay.display();
  delay(1000);

  // setBrightness() method - brightness settings:

  ledDisplay.setBrightness(1); // set brightness - bright
  ledDisplay.display();
  delay(1000);

  ledDisplay.setBrightness(0); // set brightness - dim
  ledDisplay.display();
  delay(1000);
  
}