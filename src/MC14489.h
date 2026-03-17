#ifndef MC14489_H
#define MC14489_H

#include <Arduino.h>

class MC14489 {
public:
  MC14489(uint8_t dataPin, uint8_t clockPin, uint8_t enablePin);

  void begin();
  void display();
  void displaySettings();
  void setDigit(uint8_t position, uint8_t value);
  void setSpecialChar(uint8_t position, bool value);
  void setBrightness(bool brightness);
  void setDotPoint(uint8_t value);
  void setValue(uint8_t position, uint16_t value);
  void setValue(uint8_t position, uint16_t value, uint8_t lenght);
  void setDisplay(uint8_t position1, uint8_t position2, uint8_t position3, uint8_t position4, uint8_t position5, uint8_t dotPoint);

private:
  uint8_t _dataPin, _clockPin, _enablePin;
  uint32_t _buffer;
};

#endif
