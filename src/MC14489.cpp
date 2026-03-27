/*
	FILE: MC14489.cpp
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
	License along with this library; if not, see <http://www.gnu.org/licenses/>.
*/

#include "MC14489.h"

MC14489::MC14489(uint8_t d, uint8_t c, uint8_t e)
    : _dataPin(d), _clockPin(c), _enablePin(e)
{
}

void MC14489::begin()
{
    pinMode(_dataPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_enablePin, OUTPUT);
    digitalWrite(_dataPin, LOW);
    digitalWrite(_clockPin, LOW);
    digitalWrite(_enablePin, HIGH);

    _buffer = 0b11000001000000000000000000000000UL;

    display();
}

void MC14489::display()
{
    displaySettings();

    digitalWrite(_enablePin, LOW);

    for (int8_t bit = regBits::displayRegMSB; bit >= regBits::displayRegLSB; bit--)
    {
        digitalWrite(_dataPin, (_buffer >> bit) & 1);
        digitalWrite(_clockPin, HIGH);
        digitalWrite(_clockPin, LOW);
    }

    digitalWrite(_enablePin, HIGH);
}

void MC14489::displaySettings()
{
    digitalWrite(_enablePin, LOW);

    for (int8_t bit = regBits::confRegMSB; bit >= regBits::confRegLSB; bit--)
    {
        digitalWrite(_dataPin, (_buffer >> bit) & 1);
        digitalWrite(_clockPin, HIGH);
        digitalWrite(_clockPin, LOW);
    }

    digitalWrite(_enablePin, HIGH);
}

void MC14489::set(uint8_t position, uint8_t value)
{
    uint8_t shift = 4 * (position-1);

    _buffer &= ~(0xFUL << shift);
    _buffer |= ((uint32_t)(value & 0x0F) << shift);
}

void MC14489::set(uint8_t position, char value)
{

}

void MC14489::setDigit(uint8_t position, uint8_t value)
{
    uint8_t shift = 4 * (position-1);

    _buffer &= ~(0xFUL << shift);
    _buffer |= ((uint32_t)(value & 0x0F) << shift);
}

void MC14489::setSpecialChar(uint8_t position, bool value)
{
    _buffer &= ~(0b1UL << (position + regBits::specialDecodeLSB - 1));
    _buffer |= ((uint32_t)(value & 1) << (position + regBits::specialDecodeLSB - 1));
}

void MC14489::setBrightness(bool brightness)
{
    _buffer &= ~(0b1UL << (regBits::brightnessBit));
    _buffer |= ((uint32_t)(brightness & 1) << regBits::brightnessBit);
}

void MC14489::setDotPoint(uint8_t value)
{
    _buffer &= ~(0b111UL << (regBits::dotPointLSB));
    _buffer |= ((uint32_t)(value & 0b111) << regBits::dotPointLSB);
}

void MC14489:: setValue(uint8_t position, uint16_t value)
{
    if(value == 0)
    setDigit(position, 0);
    else
    while(value > 0)
    {
        setDigit(position, value % 10);
        value /= 10;
        position--;
    }
}

void MC14489:: setValue(uint8_t position, uint16_t value, uint8_t lenght)
{
    while(lenght > 0)
    {
        setDigit(position, value % 10);
        value /= 10;
        position--;
        lenght--;
    }
}

void MC14489:: setDisplay(uint8_t position1, uint8_t position2, uint8_t position3, uint8_t position4, uint8_t position5, uint8_t dotPoint)
{
    uint8_t positions[5] = {position1,position2,position3,position4,position5};

    setDotPoint(dotPoint);

    for(int i = 0; i<5; i++)
    {
        setSpecialChar(i+1,positions[i] & 0b10000);
        setDigit(i+1,positions[i] & 0b01111);
    }
}

void MC14489:: uint8_t encodeChar(char c) {
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;

        case 'A': return 10;
        case 'B': return 11;
        case 'C': return 12;
        case 'D': return 13;
        case 'E': return 14;
        case 'F': return 15;

        case 'c': return 17;
        case 'H': return 18;
        case 'h': return 19;
        case 'J': return 20;
        case 'L': return 21;
        case 'n': return 22;
        case 'o': return 23;
        case 'P': return 24;
        case 'r': return 25;
        case 'U': return 26;
        case 'u': return 27;
        case 'y': return 28;

        case '-': return 29; // dash
        case '=': return 30; // equal
        case '*': return 31; // degree

        default: return 16;  // space (empty)
    }
}
