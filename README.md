# MC14489

Arduino library for communicating with the MC14489 Multi-Character LED Display Driver.

The library enables support for 5 LED segments connected to the MC14489 chip.

## Work In Progress

## 1. Installation

<!-- ### Method 1:
In the Arduino IDE:
1. Open *LIBRARY MANAGER*
2. Search phrase `MC14489`
3. Find the ***MC14489** by Ignacy110* library in the list
4. Click *INSTALL*

### Method 2: -->
1. Download the repository as *.zip* file.
2. In the Arduino IDE, select:
*Sketch → Include Library → Add .ZIP Library...*
3. Select the downloaded *.zip* file.

## 2. Connecting the MC14489 chip and pinout

|Symbol| Pin | Description |I/O| How to connect |
| --- | :-: | --- | :-: | --- |
|f|1|f LED segments|output| |
|e|2|e LED segments|output| |
|VDD|3|**5V** (typical value) common positive supply|power| |
|d|4|d LED segments|output||
|c|5|c LED segments|output||
|b|6|b LED segments|output||
|a|7|a LED segments|output||
|Rx|8||||
|BANK 1|9|first LED segment cathode|output||
|<span style="text-decoration: overline;">ENABLE</span>|10||transmission||
|CLOCK|11||transmission||
|DATA IN|12||transmission||
|BANK 2|13|second LED segment cathode|output||
|VSS|14|**GND**|power||
|BANK 3|15|third LED segment cathode|output||
|BANK 4|16|fourth LED segment cathode|output||
|BANK 5|17|fifth LED segment cathode|output||
|DATA OUT|18||transmission||
|h|19|h LED segments|output||
|g|20|g LED segments|output||

## 3. Usage

### 3.1 Basic setup

Include this library `<MC14489.h>`.

Before using the library methods you need to create an instance of the `MC14489` class e.g. `MC14489 ledDisplay(2, 3, 4);` where the parameters denote pins: DATA, CLOCK, <span style="text-decoration: overline;">ENABLE</span>. For readability you can define pins in advance using `#define`.

To operate the display correctly, you must initiate the transmission by calling the `begin()` method.

Example:
```cpp
#include <MC14489.h>
#define ledDataPin 2
#define ledClockPin 3
#define ledEnablePin 4

MC14489 ledDisplay(ledDataPin, ledClockPin, ledEnablePin);

void setup()
{
  ledDisplay.begin();
}
```

### 3.2 Use library methods

<!-- All available methods and their syntax are described in  [paragraph 4](#4-methods). -->

#### Simple example of use:
This program alternately displays the number 12345 and the text HELLO.
```cpp
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
  ledDisplay.set(1,12345);
  ledDisplay.display();
  delay(1000);

  ledDisplay.set(1,"HELLO");
  ledDisplay.display();
  delay(1000);
}
```
> [!TIP]
> More examples are in the *examples* folder.

## 4. Methods

> [!IMPORTANT]
> All methods provided by this library are member functions of the `MC14489` class.  
> Therefore they must be called using the created object, for example `ledDisplay`.

### 4.1 Display refreshing - display information, set settings

The `display()` method is used to refresh information on the display.

After calling this method, you can see all the changes that have been applied to the methods: `set()`, `setDotPoint()`, `setBrightness()`

### 4.2 Setting the number or characters on the display

The `set()` method is used to set numbers and characters on the display. Thanks to the four variants of this method we can send numbers, text and set left or right alignment.

This method takes two or three arguments:

|No.|Argument name|Adopted values| Description |
| :-: | --- | --- | --- |
|1|*position*|`uint8_t` - from 1 to 5|position from which characters or numbers will be written|
|2|*value*|`int` - a number that is in the range of the int type <br>`string` - text (character array)|characters or numbers to be written<br><br>(if a number or text has more characters than can fit on the display, it will be cut off)|
|3*|*direction*|`bool` - 0 or 1|Set text alignment to left (default) or right relative to *position*<br><br>* - you can omit this argument when calling the function - by default *direction = 0*|

Specific prototypes of the set() function and examples of their use in practice (e.g. in the loop() function):

|`set()` method prototypes|Example of use in practice|Example description|
| --- | --- | --- |
|`set(uint8_t position, int value)`|`set(2,123)`|From the second position set the number *123* (left alignment from the second position)|
|`set(uint8_t position, int value, bool direction)`|`set(5,840,1)`|Set the number to *840*, but the last character must be at position five (right alignment from the fifth position)|
|`set(uint8_t position, const char* str)`|`set(3,"OFF")`|From the third position set the text *OFF* (left alignment from the third position)|
|`set(uint8_t position, const char* str, bool direction)`|`set(2,"o7",1)`|Set the text to *o7*, but the last character must be at position two (right alignment from the second position)|
