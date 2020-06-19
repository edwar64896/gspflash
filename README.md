# gspflash

## Introduction
gspFlash is a utility class for managing LED instances.

## How to use
Declare an instance of gspFlash with the pin to which your LED is connected.

For instance:

```
gspFlash myLED(LED_BUILTIN);
```
Then you can do stuff like:
```
myLED.turnOn();
myLED.turnOff();
myLED.flashSlow();
myLED.flashFast();
```

## Requirements
1. Include header file <gspflash.h>
2. setup code
3. Loop code
4. Include library dependencies into project: gspflash, gspgrouped, functional-avr

## Example

```
#include <Arduino.h>
#include <gspflash.h>

gspFlash myLED(LED_BUILTIN);
gslFlash myOtherLED(12);

void setup() {
  gspGrouped::register_instance(&myLED);
  gspGrouped::register_instance(&myOtherLED);
  
  myLED.flashFast();
  myOtherLED.turnOn();
}

void loop () {
  gspFlash::checkAll();
}
```
## Advanced usage: Integration with gspstreamresponse and gspswitch

I have created some utility macros which allow you to connect your LED instances directly to input classes such as gspstreamresponse and gspswitch:

For instance:

```
gspFlash myLED(LED_BUILTIN);
gspStreamResponse mysr("=b",1,GSPFLASH_ONOFF_PARSER(myLED));
```

is all the aditional code you need to get your onboard LED turning on and off when the gspstreamresponse instance receicves a "0" or "1"

### other integration macros:

Use these in place of callback function definitions. Where I have written 'myLED' you will use your own instance of gspFlash that you have declared.

#### gspstreamresponse:
- GSPFLASH_ONOFF_PARSER(myLED)
- GSPFLASH_OFFON_PARSER(myLED)
  
#### gspswitch:
- GSPFLASH_TURNON(myLED)
- GSPFLASH_TURNOFF(myLED)
- GSPFLASH_FLASHSLOW(myLED)
- GSPFLASH_FLASHFAST(myLED)
  
## Integration example
This code expects a simple momentary pushbutton switch on pin 12 and a built-in LED on pin 13.
Repeatedly pushing the button will turn the LED on and off. Also, sending =a0 and =a1 via the serial port will turn the LED off and on.

```
#include <Arduino.h>
#include <gspflash.h>
#include <gspstreamresponse.h>
#include <gspswitch.h>

gspFlash myLED(LED_BUILTIN);

//the last parameter is the "mode" which puts the switch instance into a latching pushbutton mode (mode 1)
//mode 0 is non-latching.
gspSwitch mySwitch(12,GSPFLASH_TURNOFF(myLED),GSPFLASH_TURNON(myLED),1 /*mode*/);

//This integration allows the LED to be controlled from the serial port.
//=a0 to turn off, =a1 to turn on.
gspStreamResponse mySerial("=a",1,GSPFLASH_ONOFF_PARSER(myLED));

void setup() {
  Serial.begin(115200);
  gspGrouped::register_instance(& myLED);
  gspGrouped::register_instance(& mySwitch);
  gspGrouped::register_instance(& mySerial);
  gspStreamResponse::setup(Serial);
}

void loop () {
  gspFlash::checkAll();
  gspSwitch::checkAll();
  gspStreamResponse::checkAll();
}
```
