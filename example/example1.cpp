#include <Arduino.h>

//
// include library header files
//
#include <gspflash.h>
#include <gspswitch.h>

// pre-declare 'switch function'
// the type of function used will depend on what we want the switch to do.
void doSwitch1(uint8_t);


//
// Instantiate the gspFlash/LED instance.
//
// Params:
//  1. Pin number of the LED.
gspFlash led1(13);

// Instantiate the gspSwitch
// which is a multimode pushbutton.
//
// Each time you press the pushbutton the 'switch state' will change.
// If you leave the switch alone, it will 'autoreset' back to mode zero.
//
// If you use this switch/pushbutton to allow operation in another area,
// you can hold-off the autoreset by calling the 'counterAutoResetHoldoff()' function on the switch instance.
gspSwitch switch1(12,4,doSwitch1,0);


// this function is called when the pushbutton is activated
// 
// the switch state is passed in as a parameter.
void doSwitch1(uint8_t state) {
    
    switch(state){
        case 0:
            led1.turnOff(); // <- turn off the LED
        break;
        case 1:
            led1.flashSlow(); // <- flash the LED slow
        break;
        case 2:
            led1.flashFast(); // <- flash the LED fast
        break;
        case 3:
            led1.turnOn(); // <- turn on the LED
        break;
    }
}


// Setup function
void setup() {
    Serial.begin(115200);

    // 
    // Do this for every gsp class instance 
    //
    gspGrouped::register_instance(& led1    );
    gspGrouped::register_instance(& switch1 );

    // we "check" the flash instances using interrupts,
    // so start the checking process in the setup function.
    gspFlash::startCheckAll();

}

void loop() {

    //
    // Switch instances get checked in the loop.
    //
    // do them all with one command.
    gspSwitch::checkAll();
}
