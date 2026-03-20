/*
  FILE: MC14489.h
  AUTHOR: Ignacy110 (github.com/Ignacy110)

	MC14489 Arduino Library
  https://github.com/Ignacy110/MC14489

	Copyright (C) 2026 Ignacy110

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	The Library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
	See the GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with the GNU C Library; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MC14489_H
#define MC14489_H

#include <Arduino.h>

class MC14489 {

private:
  uint8_t _dataPin, _clockPin, _enablePin;
  uint32_t _buffer;

  enum class regBits {
    confRegMSB = 31,
    confRegLSB = 24,
    displayRegMSB = 23,
    displayRegLSB = 0,

    specialDecodeLSB = 25,
    brightnessBit = 23,
    dotPointLSB = 20,

  }

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
};

#endif
