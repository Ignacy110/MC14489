# MC14489

Arduino library for communicating with the MC14489 Multi-Character LED Display/Lamp Driver.

## Work In Progress

## 1. Installation

1. Download the repository as .ZIP file.
2. In Arduino IDE select:
*Sketch → Include Library → Add .ZIP Library*
3. Select the downloaded .ZIP file.

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