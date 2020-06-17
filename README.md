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


## Requirements
1. Include header file <gspflash.h>
2. setup code
3. Loop code

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

## Advanced usage: Integration with gspstreamresponse and gspswitch

I have created some utility macros which allow you to connect your LED instances directly to input classes such as gspstreamresponse and gspswitch:

For instance:

```
gspFlash myLED(LED_BUILTIN);
gspStreamResponse mysr("=b",1,GSPFLASH_ONOFF_PARSER(myLED));
```

is all the aditional code you need to get your onboard LED turning on and off when the gspstreamresponse instance receicves a "0" or "1"

### other integration macros:

Use these in place of callback function definitions:

#### gspstreamresponse:
- GSPFLASH_ONOFF_PARSER(<gspFlash>)
- GSPFLASH_OFFON_PARSER(<gspFlash>)
  
#### gspswitch:
- GSPFLASH_TURNON(<gspFlash>)
- GSPFLASH_TURNOFF(<gspFlash>)
- GSPFLASH_FLASHSLOW(<gspFlash>)
- GSPFLASH_FLASHFAST(<gspFlash>)
  
## Integration example
This code expects a simple momentary pushbutton switch on pin 12 and a built-in LED on pin 13.
Repeatedly pushing the button will turn the LED on and off.

```
#include <Arduino.h>
#include <gspflash.h>
#include <gspswitch.h>

gspFlash myLED(LED_BUILTIN);

//the last parameter is the "mode" which puts the switch instance into a latching pushbutton mode (mode 1)
//mode 0 is non-latching.
gspSwitch mySwitch(12,GSPFLASH_TURNOFF(myLED),GSPFLASH_TURNON(myLED),1 /*mode*/);

void setup() {
  gspGrouped::register_instance(& myLED);
  gspGrouped::register_instance(& mySwitch);
}
void loop () {
  gspFlash::checkAll();
  gspSwitch::checkAll();
}
```
