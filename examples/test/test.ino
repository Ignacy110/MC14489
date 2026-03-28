
#include <MC14489.h>
#define ledDataPin 2
#define ledClockPin 3
#define ledEnablePin 4
MC14489 ledDisplay(ledDataPin, ledClockPin, ledEnablePin);

void setup()
{
  ledDisplay.begin();
}

void loop()
{
  ledDisplay.set(2,-167,0);
  //ledDisplay.setDisplay(16,0,22,16,16,0);
  ledDisplay.display();

  delay(1000);
}