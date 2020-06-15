#include "gspflash.h"

uint16_t gspFlash::_flashCnt=0;

gspGrouped * gspFlash::firstInstance=nullptr;

gspFlash::gspFlash(int pin):gspGrouped() {
    _pin=pin;
}

void gspFlash::turnOff(){
    digitalWrite(_pin,LOW);
    bFlashing=false;
}

void gspFlash::turnOn() {
    digitalWrite(_pin,HIGH);
    bFlashing=false;
}

void gspFlash::flashFast() {
    bFlashing=true;
    _flashSpd=FAST_COUNT;

}

void gspFlash::flashSlow() {
    bFlashing=true;
    _flashSpd=SLOW_COUNT;

}

bool gspFlash::check() {
    if (_flashCnt++>_flashSpd) {
        _flashCnt=0;
        _flashToggle=!_flashToggle;
    }

    if (bFlashing) {
        if (_flashToggle) {
            digitalWrite(_pin,HIGH);   
        } else {
            digitalWrite(_pin,LOW);
        }
    }

    return true;

}