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

    for (int8_t bit = static_cast<uint8_t>(regBits::displayRegMSB); bit >= static_cast<uint8_t>(regBits::displayRegLSB); bit--)
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

    for (int8_t bit = static_cast<uint8_t>(regBits::confRegMSB); bit >= static_cast<uint8_t>(regBits::confRegLSB); bit--)
    {
        digitalWrite(_dataPin, (_buffer >> bit) & 1);
        digitalWrite(_clockPin, HIGH);
        digitalWrite(_clockPin, LOW);
    }

    digitalWrite(_enablePin, HIGH);
}

void MC14489::set(uint8_t position, int value)
{
    set(position, value, 0);
}

void MC14489::set(uint8_t position, int value, bool direction)
{
    if(value == 0)
        setDigit(position, 0);
    else
    {
        if(value < 0)
        {
            negativeNumber = 1;
            value = abs(value);
        }
        else
        {
            negativeNumber = 0;
        }
        if(direction)
        {
            while(value > 0)
            {
                setDigit(position, value % 10);
                value /= 10;
                position--;
            }
            if (negativeNumber)
                set(position,"-",0);
        }
        else
        {
            valueLength = countDigits(value);
            while(value > 0)
            {
                setDigit(position + (uint8_t)negativeNumber + valueLength - 1, value % 10);
                value /= 10;
                position--;
            }
            if (negativeNumber)
                set(position + (uint8_t)negativeNumber + valueLength - 1,"-",0);
        }
    }
}

void MC14489::set(uint8_t position, const char* str)
{
    set(position, str, 0);
}

void MC14489::set(uint8_t position, const char* str, bool direction)
{
    valueLength = 0;
    while(str[valueLength] != '\0') valueLength++;

    if(direction)
    {
        for(uint8_t i = 0; i < valueLength && position >= 1; i++)
        {
            setDigit(position, str[valueLength-i-1]);
            position--;
        }
    }
    else
    {
        for(uint8_t i = 0; i < valueLength && (position + i) <= 5; i++)
        {
            setDigit(position + i, str[i]);
        }
    }
}

void MC14489::setDigit(uint8_t position, int value)
{
    if (value >= 16) {
        setSpecialChar(position, 1);
        value &= 0x0F;
    } else {
        setSpecialChar(position, 0);
    }

    if(position >= 1 && position <= 5)
    {
        uint8_t shift = 4 * (position-1);

        _buffer &= ~(0xFUL << shift);
        _buffer |= ((uint32_t)(value & 0x0F) << shift);
    }
}

void MC14489::setDigit(uint8_t position, char value)
{
    if(position >= 1 && position <= 5)
    {
        value = encodeChar(value);

        setDigit(position, (int)value);
    }
}

void MC14489::setSpecialChar(uint8_t position, bool value)
{
    if(position >= 1 && position <= 5)
    {
        _buffer &= ~(0b1UL << (position + static_cast<uint8_t>(regBits::specialDecodeLSB) - 1));
        _buffer |= ((uint32_t)(value & 1) << (position + static_cast<uint8_t>(regBits::specialDecodeLSB) - 1));
    }
}

void MC14489::setBrightness(bool value)
{
    _buffer &= ~(0b1UL << (static_cast<uint8_t>(regBits::brightnessBit)));
    _buffer |= ((uint32_t)(value & 1) << static_cast<uint8_t>(regBits::brightnessBit));
}

void MC14489::setDotPoint(uint8_t value)
{
    if(position >= 0 && position <= 7)
    {
        _buffer &= ~(0b111UL << (static_cast<uint8_t>(regBits::dotPointLSB)));
        _buffer |= ((uint32_t)(value & 0b111) << static_cast<uint8_t>(regBits::dotPointLSB));
    }
}

int MC14489:: encodeChar(char c)
{
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
        case 'b': return 11;
        case 'C': return 12;
        case 'd': return 13;
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

        case 'O': return 0;

        case '-': return 29; // dash
        case '=': return 30; // equal
        case '*': return 31; // degree

        default: return 16;  // space (empty)
    }
}

uint8_t MC14489:: countDigits(int value)
{
    if (value == 0) return 1;

    uint8_t count = 0;
    while (value > 0)
    {
        value /= 10;
        count++;
    }
    return count;
}