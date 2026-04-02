# MC14489

Arduino library for controlling the MC14489 - a 5-digit LED display driver capable of driving multiple common cathode 7-segment displays using a simple serial interface.

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

|Symbol| Pin | Description |I/O|
| --- | :-: | --- | :-: |
|f|1|f LED segments|output|
|e|2|e LED segments|output|
|VDD|3|Positive supply voltage (**4.5V - 6.0V**)|power|
|d|4|d LED segments|output|
|c|5|c LED segments|output|
|b|6|b LED segments|output|
|a|7|a LED segments|output|
|Rx|8|resistor connected between this pin and VSS<br>(it sets the nominal display value)|analog input|
|BANK 1|9|first LED digit cathode|output|
|<span style="text-decoration: overline;">ENABLE</span>|10|chip enable (active low)|input|
|CLOCK|11|clock signal|input|
|DATA IN|12|serial data input|input|
|BANK 2|13|second LED digit cathode|output|
|VSS|14|**GND**|power|
|BANK 3|15|third LED digit cathode|output|
|BANK 4|16|fourth LED digit cathode|output|
|BANK 5|17|fifth LED digit cathode|output|
|DATA OUT|18|serial data output (for cascading)|output|
|h|19|h LED segments|output|
|g|20|g LED segments|output|

Communication uses a 3-wire interface:
- <span style="text-decoration: overline;">ENABLE</span> (active low)
- CLOCK
- DATA IN

These pins should be connected to Arduino digital pins defined in the code (see [section 3.1](#31-basic-setup)).

## 3. Usage

### 3.1 Basic setup

Include this library `<MC14489.h>`.

Before using the library methods you need to create an instance of the `MC14489` class e.g. `MC14489 ledDisplay(2, 3, 4);` where the parameters denote pins: DATA, CLOCK, <span style="text-decoration: overline;">ENABLE</span>. For readability you can define pins in advance using `#define`.

To operate the display correctly, you must initialize the transmission by calling the `begin()` method.

Example:
```cpp
#include <MC14489.h> // include the library

#define ledDataPin 2 // define the Arduino pin number
#define ledClockPin 3 // define the Arduino pin number
#define ledEnablePin 4 // define the Arduino pin number

MC14489 ledDisplay(ledDataPin, ledClockPin, ledEnablePin); // create an ledDisplay object using Arduino pins for communication with the MC14489

void setup()
{
  ledDisplay.begin(); // initialize communication
}
```

### 3.2 Use library methods

All available methods and their syntax are described in  [paragraph 4](#4-methods).

#### Simple example of use:
This program alternately displays the number *12345* and the text *HELLO*.
```cpp
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
  ledDisplay.display(); // display
  delay(1000); // wait 1 second

  ledDisplay.clear(0); // clear the display
  ledDisplay.set(1,"HELLO"); // set the text "HELLO" starting from position 1
  ledDisplay.display(); // display
  delay(1000); // wait 1 second
}
```
> [!TIP]
> More examples are in the *examples* folder.

## 4. Methods

> [!IMPORTANT]
> All methods provided by this library are member functions of the `MC14489` class.  
> Therefore they must be called using the created object, for example `ledDisplay`.

### 4.1 Display refreshing

The `display()` method is used to refresh information on the display.

After calling this method, all changes made using `set()`, `clear()`, `setDotPoint()`, and `setBrightness()` are applied to the display.

### 4.2 Setting the number or characters on the display

The `set(position, value, direction)` method is used to set numbers and characters on the display.

This method is overloaded (there are four variants) and allows sending numbers or text, with optional left or right alignment.

This method takes two or three arguments:

|No.|Argument name|Allowed values| Description |
| :-: | --- | --- | --- |
|1|*position*|`uint8_t` - from 1 to 5|position from which characters or numbers will be written|
|2|*value*|`int` - a number that is in the range of the int type<br><br>`const char*` - text (C-style `string`)|characters or numbers to be written<br><br>(if a number or text has more characters than can fit on the display, it will be cut off)|
|3*|*direction*|`bool` - 0 or 1|Set text alignment to left (0 value - default) or right (1 value) relative to *position*<br><br>* - you can omit this argument when calling the function - by default *direction = 0*|

<br>
Specific prototypes of the set() function and examples of their use in practice (e.g. in the loop() function):

|`set()` method prototypes|Example of use in practice|Example description|
| --- | --- | --- |
|`set(uint8_t position, int value)`|`set(2,123)`|From the second position set the number *123* (left alignment from the second position)|
|`set(uint8_t position, int value, bool direction)`|`set(5,840,1)`|Set the number to *840*, but the last character must be at position five (right alignment from the fifth position)|
|`set(uint8_t position, const char* str)`|`set(3,"OFF")`|From the third position set the text *OFF* (left alignment from the third position)|
|`set(uint8_t position, const char* str, bool direction)`|`set(2,"o7",1)`|Set the text to *o7*, but the last character must be at position two (right alignment from the second position)|

>[!NOTE]
>If the value exceeds the available display space, it will be truncated.

### 4.3 Clear display

The `clear(bool value)` method is used to clear the display.

Depending on the parameter, this method can clean the screen in two ways:

|value| Function |
| :-: | --- |
|0|blank digits|
|1|all digits set to 0|

### 4.4 Setting dots

The `setDotPoint(uint8_t value)` method is used to set a dot on the display.

The MC14489 chip allows you to set the displayed dots in 8 ways.

The `value` parameter controls which decimal points are enabled:

|value|Function |
| :-: | --- |
|0|no dot points|
|1|dot point in the **first digit**|
|2|dot point in the **second digit**|
|3|dot point in the **third digit**|
|4|dot point in the **fourth digit**|
|5|dot point in the **fifth digit**|
|6|dot points in **first digit** and **second digit**|
|7|dot points in **all digits**|

Values greater than 7 are ignored.

### 4.5 Setting brightness

The `setBrightness(bool value)` method is used to set the display brightness.

The MC14489 chip supports two brightness levels: dim and bright.

The `value` parameter selects the brightness level:

|value| Function |
| :-: | --- |
|0|dim display|
|1|bright display|
